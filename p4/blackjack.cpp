//
//  main.cpp
//  p4
//
//  Created by Cheng on 2017/7/17.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>

#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"


using namespace std;
/*
int main()
{
    Deck deck;
    deck=Deck();
    int i;
    deck.shuffle(23);
    deck.shuffle(23);
    deck.shuffle(22);
    deck.shuffle(39);
    deck.shuffle(33);
    deck.shuffle(19);
    deck.shuffle(25);
    deck.reset();
    for(i=0;i<DeckSize;i++)
    {
        Card c=deck.deal();
        cout << SuitNames[c.suit]<<" "<< SpotNames[c.spot]<< endl;
    }

    return 0;
}


*/
int main(int argc, char *argv[])
{
    int bankroll, minBet,maxHand;
    bankroll=atoi(argv[1]);
    minBet=atoi(argv[2]);
    maxHand=atoi(argv[3]);
    string sc;
    sc=argv[4];
    
    
    int i;
    Deck deck;
    
    Player *player;
    Hand handP;
    Hand handD;
    if(sc=="simple")
        player=get_Simple();
    else if(sc=="counting")
        player=get_Counting();
    
/////////////////////////////
    //shuffle
    cout << "# Shuffling the deck\n";
    if(argc==6)
    {
        ifstream iFile;
        iFile.open(argv[5]);
        
        string cuts;
        getline(iFile, cuts);
        istringstream cutStream;
        cutStream.str(cuts);
        string cut;
        while (cutStream >> cut)
        {
            deck.shuffle(atoi(cut.c_str()));
            cout<<"cut at "<<cut<<endl;
        }
        
        iFile.close();
    }
    
    
    else
    {
        for(i=1;i<=7;i++)
        {
            int cut;
            cut=get_cut();
            deck.shuffle(cut);
            cout<<"cut at "<<cut<<endl;
        }
    }
/////////////////////////////////
    
    int thishand=1;
    int wager;
    Card currCard, cardD;
//    if (bankroll>=minBet){
    while (thishand<=maxHand && bankroll>=minBet)
    {

        handP.discardAll();
        handD.discardAll();
        thishand++;
        cout << "# Hand " << thishand-1 << " bankroll " << bankroll << endl;
        if(deck.cardsLeft()<20)
        {
            //deck.reset();
            cout << "# Shuffling the deck\n";
            for(i=1;i<=7;i++)
            {
                int cut;
                cut=get_cut();
                deck.shuffle(cut);
                cout<<"cut at "<<cut<<endl;
            }
            player->shuffled();
        }
        
        wager=player->bet(bankroll, minBet);
        cout << "# Player bets " << wager << endl;
        for(i=0;i<3;i++)
        {
            currCard=deck.deal();
            player->expose(currCard);
            if(i==0 || i== 2)
            {
                cout << "Player dealt "<<SpotNames[currCard.spot]<<" of " <<SuitNames[currCard.suit]<< endl;
                handP.addCard(currCard);
            }
            else
            {
                cardD=currCard;
                cout << "Dealer dealt "<<SpotNames[currCard.spot]<<" of " <<SuitNames[currCard.suit]<< endl;
                handD.addCard(currCard);
            }
        }
        Card hole=deck.deal();
        if (handP.handValue().count==21)
        {
            cout << "# Player dealt natural 21\n";
            bankroll=bankroll+(3*wager)/2;
            continue;
        }
        while(player->draw(cardD,handP) && handP.handValue().count<21)
        {
            Card currCard2=deck.deal();
            handP.addCard(currCard2);
            player->expose(currCard2);
            cout<<"Player dealt "<<SpotNames[currCard2.spot]<<" of "<<SuitNames[currCard2.suit]<<endl;
        }
        cout << "Player's total is " << handP.handValue().count << endl;

        if (handP.handValue().count>21)
        {
            cout << "# Player busts\n";
            bankroll=bankroll-wager;
            continue;
        }
        if (handP.handValue().count<=21)
        {
            
            player->expose(hole);
            handD.addCard(hole);
            cout<<"Dealer's hole card is "<<SpotNames[hole.spot]<<" of "<<SuitNames[hole.suit]<<endl;
        }
        while(handD.handValue().count<17)
        {
            currCard = deck.deal();
            player->expose(currCard);
            handD.addCard(currCard);
            cout<<"Dealer dealt "<<SpotNames[currCard.spot]<<" of "<<SuitNames[currCard.suit]<<endl;
        }
        cout<<"Dealer's total is "<<handD.handValue().count<<endl;
        if(handD.handValue().count>21)
        {
            bankroll=bankroll+wager;
            cout<<"# Dealer busts\n";
            continue;
        }
        
        
        if(handD.handValue().count>handP.handValue().count)
            {
                cout<<"# Dealer wins\n";
                bankroll=bankroll-wager;
            }
        else if(handD.handValue().count<handP.handValue().count)
            {
                cout<<"# Player wins\n";
                bankroll=bankroll+wager;
            }
        if(handD.handValue().count==handP.handValue().count)
                cout<<"# Push\n";
        
        
        
    }
    
cout<<"# Player has "<<bankroll<<" after "<<thishand-1<<" hands\n";
    


    
}
