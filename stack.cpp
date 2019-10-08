//
//  stack.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 29/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include "stack.hpp"
#include <iostream>
#define STACKSIZE 20
using namespace std;

symbol stack[STACKSIZE];
int top_ptr=-1;
int size=0;

void push(symbol s){
    if(++top_ptr >= STACKSIZE) return;
    stack[top_ptr].setlink(s.getlink());
    stack[top_ptr].setoriginallink(s.getoriginallink());
    stack[top_ptr].setavail(s.getavail());
    stack[top_ptr].setsymbol(s.getsymbol());
    stack[top_ptr].setlinked(s.getlinked());
    size++;
}

void pop(){
    symbol s;
    if(top_ptr < 0){
        cout << "The stack is now empty!" << endl;
        return;
    }
    top_ptr--;
    size--;
}

symbol top(){
    return stack[top_ptr];
}

int getSize(){
    return size;
}
