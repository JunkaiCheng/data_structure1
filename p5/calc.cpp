//
//  calc.cpp
//  p5
//
//  Created by Cheng on 2017/7/27.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <stdio.h>
#include <sstream>
#include <string>

#include "dlist.h"

using namespace std;

struct comN
{
    int real;
    int imaginary;
};

int main()
{
    
    Dlist<comN> inP;
    string s="";
    
    while(s!="q")
    {
        cin >> s;
        if (s=="q") return 0;
        else if(s=="+")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                if(inP.isEmpty())
                {
                    cout << "Not enough operands\n";
                    inP.insertFront(op1);
                    continue;
                }
                else
                {
                    comN *op2=inP.removeFront();
                    //comN *result;
                    //comN *result= new comN;
                    op1->real=op1->real+op2->real;
                    op1->imaginary=op1->imaginary+op2->imaginary;
                    inP.insertFront(op1);
                    delete op2;
                }

            }
        }
        
        else if (s=="-")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                if(inP.isEmpty())
                {
                    cout << "Not enough operands\n";
                    inP.insertFront(op1);
                    continue;
                }
                else
                {
                    comN *op2=inP.removeFront();
                    op1->real=op2->real-op1->real;
                    op1->imaginary=op2->imaginary-op1->imaginary;
                    inP.insertFront(op1);
                    delete op2;
                   // delete result1;
                }
                
            }

        }
        
        else if (s=="*")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                if(inP.isEmpty())
                {
                    cout << "Not enough operands\n";
                    inP.insertFront(op1);
                    continue;
                }
                else
                {
                    comN *op2=inP.removeFront();
                    //comN *result;
                    //comN *result= new comN;
                    comN *op3=new comN;
                    op3->real=(op1->real*op2->real)-(op1->imaginary*op2->imaginary);
                    op3->imaginary=(op1->real*op2->imaginary)+(op1->imaginary*op2->real);
                    inP.insertFront(op3);
                    delete op1;
                    delete op2;
                  //  delete result1;
                }
                
            }

        }
        else if (s=="n")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                //comN *result;
                //comN *result= new comN;
                op1->real=-op1->real;
                op1->imaginary=-op1->imaginary;
                inP.insertFront(op1);
               // delete result1;
            }
        }
        else if (s=="d")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                comN *result1= new comN;
                comN *result2= new comN;
                result1->real=op1->real;
                result1->imaginary=op1->imaginary;
                result2->real=op1->real;
                result2->imaginary=op1->imaginary;
                inP.insertFront(result1);
                inP.insertFront(result2);
                delete op1;
            }
        }

        else if (s=="r")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                if(inP.isEmpty())
                {
                    cout << "Not enough operands\n";
                    inP.insertFront(op1);
                    continue;
                }
                else
                {
                    comN *op2=inP.removeFront();
                    //comN *result1;
                    //comN *result2;
                    comN *result1= new comN;
                    comN *result2= new comN;
                    result1->real=op1->real;
                    result1->imaginary=op1->imaginary;
                    result2->real=op2->real;
                    result2->imaginary=op2->imaginary;
                    inP.insertFront(result1);
                    inP.insertFront(result2);
                    delete op2;
                  //  delete result1;
                  //  delete result2;
                }
                delete op1;
                
            }

        }
        
        else if (s=="p")
        {
            if(inP.isEmpty())
            {
                cout << "Not enough operands\n";
                continue;
            }
            else
            {
                comN *op1=inP.removeFront();
                cout << op1->real;
                if (op1->imaginary>=0)
                    cout << "+";
                cout << op1->imaginary<<"i"<<endl;
                inP.insertFront(op1);
            }
        }
        
        else if (s=="c")
        {
            while(!inP.isEmpty())
            {
                comN *opp=inP.removeFront();
                delete opp;
            }
        }
        
        else if (s=="a")
        {
            Dlist<comN> temp;
            while(!inP.isEmpty())
            {
                comN *op1=inP.removeFront();
                cout << op1->real;
                if (op1->imaginary>=0)
                    cout << "+";
                cout << op1->imaginary<<"i"<<" ";
                temp.insertFront(op1);
            }
            while(!temp.isEmpty())
            {
                comN *op2=temp.removeFront();
                inP.insertFront(op2);
            }
            cout<< endl;
        }
        else
        {
            int real, imag;
            string  ij;
            istringstream ss;
            ss.str(s);
            if(s[0]=='+')
            {
                cout << "Bad input\n";
                continue;
            }

            
            ss >> real >> imag >> ij;
            if(ij!="i")
            {
                cout << "Bad input\n";
                continue;
            }
            else
            {
                comN *cn=new comN;
                cn->real=real;
                cn->imaginary=imag;
                inP.insertFront(cn);
            }
            
        }
    }

    
}
