//
//  hand.cpp
//  p4
//
//  Created by Cheng on 2017/7/18.
//  Copyright © 2017年 Cheng. All rights reserved.
//
#include "hand.h"


#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <stdio.h>





using namespace std;

Hand::Hand()
{
    HandValue emptyHand;
    emptyHand.count=0;
    emptyHand.soft=0;
    curValue=emptyHand;
}

void Hand::discardAll()
{
    HandValue emptyHand;
    emptyHand.count=0;
    emptyHand.soft=0;
    curValue=emptyHand;
}

void Hand::addCard(Card c)
{
    if (c.spot<=8)
        curValue.count=curValue.count+c.spot+2;
    else if (c.spot<12&&c.spot>8)
        curValue.count=curValue.count+10;
    else if (c.spot==12 && curValue.count+11<=21)
    {
        curValue.count=curValue.count+11;
        curValue.soft=1;
    }
    else if (c.spot==12 && curValue.count+11>=21)
        curValue.count=curValue.count+1;
    if(curValue.soft==1&&curValue.count>21)
    {
        curValue.count=curValue.count-10;
        curValue.soft=0;
    }
}

HandValue Hand::handValue() const
{
    return curValue;
}









