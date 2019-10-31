//
//  node.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include <iostream>
using namespace std;

#include "node.hpp"

node::node(){
    lchild = 0;
    rchild = 0;
    free = false;
    flag = false;
}

node::node(int l, int r){
    lchild = l;
    rchild = r;
    free = false;
    flag = false;
}

void node::setlchild(int l){
    lchild = l;
}

void node::setrchild(int r){
    rchild = r;
}

void node::setfree(bool f){
    free = f;
}

void node::setflag(bool f){
    flag = f;
}

int node::getlchild(){
    return lchild;
}

int node::getrchild(){
    return rchild;
}

bool node::getfree(){
    return free;
}

bool node::getflag(){
    return flag;
}
