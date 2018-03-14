//
//  dlist.cpp
//  p5
//
//  Created by Cheng on 2017/7/27.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#ifndef __DLIST___
#define __DLIST___



#include <iostream>
#include <cstdlib>
#include <cassert>

#include "dlist.h"

using namespace std;



template <class T>
bool Dlist<T>::isEmpty() const
{
    return !first;
}


template <class T>
void Dlist<T>::insertFront(T *op)
{
    node *np=new node;
    np->op=op;
    np->next=first;
    np->prev=NULL;
    if (first!=NULL)
        first->prev=np;
    else last=np;
    first=np;

}

template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *np=new node;
    np->op=op;
    np->prev=last;
    np->next=NULL;
    if(last!=NULL)
        last->next=np;
    else first=np;
    last=np;
}

template <class T>
T* Dlist<T>::removeFront()
{
    
    node *victim = first;
    T *result;
    if (isEmpty())
    {
        emptyList e;
        throw e;
    }
    first = victim->next;
    result = victim->op;
    if (first!=NULL)
        first->prev=NULL;
    else
        last=NULL;
    delete victim;
    return result;
}


template <class T>
T* Dlist<T>::removeBack()
{
    node *victim = last;
    T *result;
    if (isEmpty())
    {
        emptyList e;
        throw e;
    }
    last = victim->prev;
    result = victim->op;
    if (last!=NULL)
        last->next=NULL;
    else
        first=NULL;
    delete victim;
    return result;
}

template <class T>
Dlist<T>::Dlist():first(0), last(0)
{}


template <class T>
Dlist<T>::Dlist(const Dlist &l)
{
    first=NULL;
    last=NULL;
    copyAll(l);
}

template <class T>
void Dlist<T>::removeAll()
{
    while (!isEmpty())
    {
        T *d=removeFront();
        delete d;
    }
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    node *d =l.first;
    while(d!=NULL)
    {
        T* op=new T(*d->op);
        insertBack(op);
        d=d->next;
    }
}

template <class T>
Dlist<T> &Dlist<T>::operator=
(const Dlist &l)
{
    if(this!=&l)
    {
        removeAll();
        copyAll(l);
    }
    return *this;
}





#endif
















