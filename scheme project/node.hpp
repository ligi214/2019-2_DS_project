//
//  node.hpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <stdio.h>

class node{
public:
    node();
    node(int l, int r);
    void setlchild(int l);
    void setrchild(int r);
    void setfree(bool f);
    void setflag(bool f);
    int getlchild();
    int getrchild();
    bool getfree();
    bool getflag();
    
private:
    bool free;
    bool flag;
    int lchild;
    int rchild;
};

#endif /* node_hpp */


