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
#include <string>
#include "node.hpp"
#include "symbol.hpp"

int getHashValue_keyword(string s);
void initialize();
int getHashValue(string s);
void clearTokens();
string preprocessing();
void tokenizer(string data);
string getNextToken();
int alloc();
int read();
void memArrayPrint_alloc_only_from_root(int root);
void print(int root, string data);
void printSymbol(string data);
void dealloc(int root);

#endif /* operation_hpp */
