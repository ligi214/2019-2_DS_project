//
//  evaluation.hpp
//  Scheme_ass1
//
//  Created by SeongminLee on 25/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#ifndef evaluation_hpp
#define evaluation_hpp

extern const int LEFTPAREN;
extern const int RIGHTPAREN;
extern const int PLUS;
extern const int MINUS;
extern const int TIMES;
extern const int isNUMBER;
extern const int isSYMBOL;
extern const int isNULL;
extern const int CONS;
extern const int COND;
extern const int CAR;
extern const int CDR;
extern const int DEFINE;
extern const int LAMBDA;
extern const int QUOTE;
extern const int SCHEME_TRUE;
extern const int SCHEME_FALSE;


#include <stdio.h>
#include <iostream>
#include "node.hpp"
#include "symbol.hpp"
#include "operation.hpp"
#include "stack.hpp"

int eval(int root);

#endif /* evaluation_hpp */
