//
//  player.cpp
//  p4
//
//  Created by Cheng on 2017/7/18.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <stdio.h>

#include "player.h"



using namespace std;


class simplePlayer: public Player{
public:
    virtual int bet(unsigned int bankroll,unsigned int minimum);
    virtual bool draw(Card dealer, const Hand &player);
    virtual void expose(Card C);
    virtual void shuffled();
};

class countingPlayer: public simplePlayer{
private:
    int count;
public:
    virtual int bet(unsigned int bankroll,unsigned int minimum);
    virtual void expose(Card C);
    virtual void shuffled();
};

int simplePlayer::bet(unsigned int bankroll, unsigned int minimum)
{
     return minimum;
}

bool simplePlayer::draw(Card dealer, const Hand &player)
{
    HandValue currHandvalue=player.handValue();
    bool soft=currHandvalue.soft;
    int currHand=currHandvalue.count;
    if (soft==0)
    {
        if(currHand<=11)
            return 1;
        else if(currHand==12)
        {
            if(dealer.spot>=2&&dealer.spot<=4)
                return 0;
            else
                return 1;
        }
        else if(currHand>=13 && currHand <=16)
        {
            if (dealer.spot>=0 && dealer.spot<=4)
                return 0;
            else
                return 1;
        }
        else
           return 0;
     }
    else
     {
         if (currHand<=17)
             return 1;
         else if(currHand==18)
         {
             if (dealer.spot==0||dealer.spot==5||dealer.spot==6)
                 return 0;
             else
                 return 1;
        }
        else
            return 0;
     }
}
void simplePlayer::expose(Card c)
{
    
}

void simplePlayer::shuffled()
{
    
}

int countingPlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    if(count>=2&& bankroll>=2*minimum)
            return 2*minimum;
    else
            return minimum;
}

void countingPlayer::expose(Card c)
{
    
    if (c.spot>=8)
            count--;
    else if (c.spot<=4)
            count++;
}
///////////////////////
//////////////////


void countingPlayer::shuffled()
{
    count=0;
}

static simplePlayer sp;
static countingPlayer cp;



extern Player *get_Simple()
{
    return &sp;
}

extern Player *get_Counting()
{
    return &cp;
}


















