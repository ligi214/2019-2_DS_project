//
//  stack.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 29/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include "stack.hpp"
#define STACKSIZE 10

symbol stack[STACKSIZE];
int top=-1;
int size=0;

void push(symbol s){
    if(++top >= STACKSIZE) return;
    stack[top].setlink(s.getlink());
    stack[top].setavail(s.getavail());
    stack[top].setsymbol(s.getsymbol());
    size++;
}

symbol pop(){
    symbol s;
    if(top < 0) return s;
    s.setlink(stack[top].getlink());
    s.setavail(stack[top].getavail());
    s.setsymbol(stack[top].getsymbol());
    top--;
    size--;
    return s;
}

int getSize(){
    return size;
}
