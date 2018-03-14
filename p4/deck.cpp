//
//  deck.cpp
//  p4
//
//  Created by Cheng on 2017/7/17.
//  Copyright © 2017年 Cheng. All rights reserved.
//


#include "deck.h"


#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <stdio.h>





using namespace std;

Deck::Deck()
{
    next=0;
    int i,j,k;
        for (j=0;j<4;j++)
        {
            for (k=0;k<13;k++)
            {
                switch (k)
                {
                    case 0: deck[13*j+k].spot=TWO;
                        break;
                    case 1: deck[13*j+k].spot=THREE;
                        break;
                    case 2: deck[13*j+k].spot=FOUR;
                        break;
                    case 3: deck[13*j+k].spot=FIVE;
                        break;
                    case 4: deck[13*j+k].spot=SIX;
                        break;
                    case 5: deck[13*j+k].spot=SEVEN;
                        break;
                    case 6: deck[13*j+k].spot=EIGHT;
                        break;
                    case 7: deck[13*j+k].spot=NINE;
                        break;
                    case 8: deck[13*j+k].spot=TEN;
                        break;
                    case 9: deck[13*j+k].spot=JACK;
                        break;
                    case 10: deck[13*j+k].spot=QUEEN;
                        break;
                    case 11: deck[13*j+k].spot=KING;
                        break;
                    case 12: deck[13*j+k].spot=ACE;
                        break;
                    default: break;
                }
                switch (j)
                {
                    case 0: deck[13*j+k].suit=SPADES;
                        break;
                    case 1: deck[13*j+k].suit=HEARTS;
                        break;
                    case 2: deck[13*j+k].suit=CLUBS;
                        break;
                    case 3: deck[13*j+k].suit=DIAMONDS;
                        break;
                    default: break;
                }
            
        }
    }
}

void Deck::reset()
{
    int i;
    next=0;
    for(i=0; i<DeckSize; i++)
    {
        deck[i].spot=Spot(i%13);
        deck[i].suit=Suit((i-i%13)/13);
    }
 
}

void Deck::shuffle(int n)
{
    int i;
    Deck decktemp;
    
    if (n<=26)
    {////the "left" has fewer cards
        if (n!=0)
        {
        for (i=0; i<n; i++)
        {
            decktemp.deck[2*i]=deck[n+i];
            decktemp.deck[2*i+1]=deck[i];
            
        }
        for (i=n*2; i<DeckSize;i++)
            decktemp.deck[i]=deck[i];
        }
        else
        {
            for (i=n; i<DeckSize;i++)
                decktemp.deck[i]=deck[n+i];
        }        
    }
    else
    {////the "right" has fewer cards
        if (n!=DeckSize)
        {
        for (i=0; i<DeckSize-n; i++)
        {
            decktemp.deck[2*i]=deck[n+i];
            decktemp.deck[2*i+1]=deck[i];
        }
        for (i=2*DeckSize-2*n; i<DeckSize;i++)
            decktemp.deck[i]=deck[DeckSize-n+i-(2*DeckSize-2*n)];
        }
        else
        {
            for (i=n; i<DeckSize;i++)
                decktemp.deck[i]=deck[i];
        }
        

    }
    for (i=0;i<DeckSize;i++)
        deck[i]=decktemp.deck[i];
    next=0;
}

Card Deck::deal()
{
    DeckEmpty deal_error;
    if (next!=DeckSize)
    {
        next=next+1;
        return deck[next-1];
    }
    else throw deal_error;
}

int Deck::cardsLeft()
{
    return DeckSize-next;
}




















