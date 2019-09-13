//
//  operation.hpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#ifndef operation_hpp
#define operation_hpp

#include <stdio.h>
#include "node.hpp"
#include "symbol.hpp"

#endif /* operation_hpp */

void initialize();
int getHashValue(string s);
void clear();
void tokenizer(string data);
string getNextToken();
int alloc();
int read();
void print(int root, string data);
void printSymbol(string data);
void dealloc(int root);
