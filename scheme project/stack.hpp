//
//  stack.hpp
//  Scheme_ass1
//
//  Created by SeongminLee on 29/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include "symbol.hpp"

void push(symbol s);
void pop();
symbol top();
int getSize();

#endif /* stack_hpp */
