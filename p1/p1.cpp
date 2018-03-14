//
//  main.cpp
//  Proj1
//
//  Created by Cheng on 2017/5/27.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;


//  This function is to test whether the input number is a Fibonacci number
int fib (long n)
{
    int r=0; // Result of test
    long a=1, b=2;
    int i;
    long t;
    if (n==1 || n==2||n==0)
        r=1;
    for (i=1; i<40; i++)
    {
        t=a+b;
        a=b;
        b=t;
        if (n==b)
            r=1;
    }
    return r;
}




//  This function is to test whether the input number is a sum of consecutive squares
int scq (long n)
{
    int r=0; // Result of test
    int i,j;
    int s;
    int k=sqrt(n);
    if (n==0)
        r=1;
    if (n>0)
    {
        for (i=1; i<= k; i++)
        {
            s=0;
            for (j=0; j<=k-i; j++ )
            {
                s=s+(i+j)*(i+j);
                if (n==s)
                    r=1;
            }
        }
    }
    return r;
}



//  This function is to test whether the input number is a repeated number
int rep (long n)
{
    int r=0; // Result of test
    
    if (n>=11 && n<=99)
    {
        if (n%11==0)
            r=1;
    }
    
    if (n>=100 && n<=999)
    {
        if (n%111==0)
            r=1;
    }
    
    if (n>=1000 && n<=9999)
    {
        if(n%1111==0 || n%101==0)
            r=1;
    }
    
    if (n>=10000 && n<=99999)
    {
        if (n%11111==0)
            r=1;
    }
    
    if (n>=100000 && n<=999999)
    {
        if (n%111111==0||n%10101==0 ||n%1001==0)
            r=1;
    }
    
    if (n>=1000000 && n<=9999999)
    {
        if (n%1111111==0)
            r=1;
    }
    return r;
}



//  This function is to test whether the input number is a divisor-sum number
int ds (long n)
{
    int r=0; // Result of test
    if (n>0)
    {
        int i;
        int s=0;
        for(i=1; i<n; i++)
        {
            if (n%i==0)
                s=s+i;
        }
        if (s==n)
            r=1;
    }
    return r;
}



int main()
{
//input
    int tc; // test chioce
    long n; // number for test
    int r; // result of test
    cout << "Please enter the test choice: ";
    cin >> tc ;
    while (tc<1 || tc>4)
    {
        cout << "Please enter the test choice: ";
        cin >> tc;
    }
    cout << "Please enter the number for test: ";
    cin >> n;
    while (n<0 || n>10000000)
    {
        cout << "Please enter the number for test: ";
        cin >> n;
    }
    
//carry out the test
    switch (tc)
    {
        case 1:
            r=fib(n);
            break;
        case 2:
            r=scq(n);
            break;
        case 3:
            r=rep(n);
            break;
        case 4:
            r=ds(n);
            break;
        default:
            break;
    }
    
//output the result
    if (r==1)
        cout << "Pass" << endl;
    if (r==0)
        cout << "Fail" << endl;
    return 0;
}
