//
//  symbol.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include "symbol.hpp"

symbol::symbol(){
    sym = "";
    link = 0;
}

symbol::symbol(string s, int l){
    sym = s;
    link = l;
    originallink = 0;
    avail = true;
    linked = false;
}

void symbol::setsymbol(string s){
    sym = s;
}

void symbol::setlink(int l){
    link = l;
    linked = false;
}

void symbol::setoriginallink(int l){
    originallink = l;
}

void symbol::setavail(bool a){
    avail = a;
}

string symbol::getsymbol(){
    return sym;
}

void symbol::setlinked(bool l){
    linked = l;
}

int symbol::getlink(){
    return link;
}

int symbol::getoriginallink(){
    return originallink;
}

bool symbol::getavail(){
    return avail;
}

bool symbol::getlinked(){
    return linked;
}
