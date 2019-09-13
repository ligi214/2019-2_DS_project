//
//  symbol.hpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#ifndef symbol_hpp
#define symbol_hpp

#include <stdio.h>
#include <string>
using namespace std;

class symbol{
public:
    symbol();
    symbol(string s, int l);
    void setsymbol(string s);
    void setlink(int l);
    void setavail(bool a);
    string getsymbol();
    int getlink();
    bool getavail();
private:
    string sym;
    int link;
    bool avail;
};

#endif /* symbol_hpp */
