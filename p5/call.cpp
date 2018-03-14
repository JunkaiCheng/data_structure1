//
//  call.cpp
//  p5
//
//  Created by Cheng on 2017/7/27.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <string>

#include "dlist.h"

using namespace std;

enum Status
{
    REGULAR, SILVER, GOLD, PLATINUM, STATUS_SIZE
};

const char *StatusNames[]=
{
    "regular", "silver", "gold", "platinum"
};


struct customer
{
    int timestamp;
    string name;
    Status status;
    int waiting;
    int duration;
};

struct agent
{
    bool isBusy;//ture if busy, false if not
    int timeLeft;
};

Status st2status(string s)
{
    if (s=="regular") return REGULAR;
    else if (s=="silver") return SILVER;
    else if (s=="gold") return GOLD;
    else return PLATINUM;
    
}

int main()
{
    int numL;//number of customers in the list
    cin >> numL;
    int numW=numL;//number of customers who are waiting/ being answered
    
    //list for customers waiting
    Dlist<customer> clr;
    Dlist<customer> cls;
    Dlist<customer> clg;
    Dlist<customer> clp;
    
    agent agent;
    agent.isBusy=0;
    agent.timeLeft=0;
    
    Dlist<customer> list;//List of all the customers
    
    int i;
    for(i=0; i< numL; i++)
    {
        int ts, wait, duration;
        string name, s;
        Status status;
        cin >> ts>> name >> s >> wait >> duration;
        status=st2status(s);
        
        customer *ctm=new customer;
        ctm->timestamp=ts;
        ctm->name=name;
        ctm->status=status;
        ctm->waiting=wait;
        ctm->duration=duration;
        list.insertBack(ctm);
        
    }
    
    int tick=0;
    while(numW!=0)
    {
        cout << "Starting tick #"<< tick<<endl;
        
        //------------------------------
        //agent finishes serving a call
        if(agent.isBusy==1)
        {
            agent.timeLeft--;
            if(agent.timeLeft==0)
            {
                agent.isBusy=0;
                numW--;
            }
        }
        
        //------------------------------
        //a caller hangs up
        Dlist <customer> temp;
        
        if(!clp.isEmpty())
        {
            while(!clp.isEmpty())
            {
                customer *waitCtm=clp.removeFront();
                if (waitCtm->waiting <= tick-waitCtm->timestamp)
                {
                    cout<<waitCtm->name<<" hangs up"<<endl;
                    numW--;
                    delete waitCtm;
                }
                else temp.insertFront(waitCtm);
            }
            while(!temp.isEmpty())
            {
                customer *waitCtm2=temp.removeFront();
                clp.insertFront(waitCtm2);
            }
            
        }
        if(!clg.isEmpty())
        {
            while(!clg.isEmpty())
            {
                customer *waitCtm=clg.removeFront();
                if (waitCtm->waiting <= tick-waitCtm->timestamp)
                {
                    cout<<waitCtm->name<<" hangs up"<<endl;
                    numW--;
                    delete waitCtm;
                }
                else temp.insertFront(waitCtm);
            }
            while(!temp.isEmpty())
            {
                customer *waitCtm2=temp.removeFront();
                clg.insertFront(waitCtm2);
            }
            
        }
        if(!cls.isEmpty())
        {
            while(!cls.isEmpty())
            {
                customer *waitCtm=cls.removeFront();
                if (waitCtm->waiting <= tick-waitCtm->timestamp)
                {
                    cout<<waitCtm->name<<" hangs up"<<endl;
                    numW--;
                    delete waitCtm;
                }
                else temp.insertFront(waitCtm);
            }
            while(!temp.isEmpty())
            {
                customer *waitCtm2=temp.removeFront();
                cls.insertFront(waitCtm2);
            }
            
            
        }
        if(!clr.isEmpty())
        {
            while(!clr.isEmpty())
            {
                customer *waitCtm=clr.removeFront();
                if (waitCtm->waiting <= tick-waitCtm->timestamp)
                {
                    cout<<waitCtm->name<<" hangs up"<<endl;
                    numW--;
                    delete waitCtm;
                }
                else temp.insertFront(waitCtm);
            }
            while(!temp.isEmpty())
            {
                customer *waitCtm2=temp.removeFront();
                clr.insertFront(waitCtm2);
            }
            

            
        }
        
        
        
        //--------------------------------
        //a caller enters into the queue
        if(numL!=0)
        {
            for(i=0;i<numL;i++)
            {
                customer *currCtm=list.removeFront();
                if(currCtm->timestamp!=tick)
                    list.insertFront(currCtm);
                else
                {
                    cout << "Call from "<< currCtm->name<<" a "<< StatusNames[currCtm->status]<<" member"<<endl;
                    numL--;
                    if(currCtm->status==0)
                        clr.insertBack(currCtm);
                    else if(currCtm->status==1)
                        cls.insertBack(currCtm);
                    else if(currCtm->status==2)
                        clg.insertBack(currCtm);
                    else if(currCtm->status==3)
                        clp.insertBack(currCtm);
                }
            }
        }
        
        
        //------------------------------------
        //the agent begins to serve a new call
        if(agent.isBusy==0)
        {
            if(!clp.isEmpty())
            {
                customer *answerCtm=clp.removeFront();
                agent.isBusy=1;
                agent.timeLeft=answerCtm->duration;
                cout<< "Answering call from "<< answerCtm->name<<endl;
                delete answerCtm;
            }
            else if (!clg.isEmpty())
            {
                customer *answerCtm=clg.removeFront();
                agent.isBusy=1;
                agent.timeLeft=answerCtm->duration;
                cout<< "Answering call from "<< answerCtm->name<<endl;
                delete answerCtm;
            }
            else if (!cls.isEmpty())
            {
                customer *answerCtm=cls.removeFront();
                agent.isBusy=1;
                agent.timeLeft=answerCtm->duration;
                cout<< "Answering call from "<< answerCtm->name<<endl;
                delete answerCtm;
            }
            else if (!clr.isEmpty())
            {
                customer *answerCtm=clr.removeFront();
                agent.isBusy=1;
                agent.timeLeft=answerCtm->duration;
                cout<< "Answering call from "<< answerCtm->name<<endl;
                delete answerCtm;
            }
        }
        tick++;
    }
    
}








