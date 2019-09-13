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
    link = NULL;
}

symbol::symbol(string s, int l){
    sym = s;
    link = l;
    avail = true;
}

void symbol::setsymbol(string s){
    sym = s;
}

void symbol::setlink(int l){
    link = l;
}

void symbol::setavail(bool a){
    avail = a;
}

string symbol::getsymbol(){
    return sym;
}

int symbol::getlink(){
    return link;
}

bool symbol::getavail(){
    return avail;
}
