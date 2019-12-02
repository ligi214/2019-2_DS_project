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
    void setoriginallink(int l);
    void setavail(bool a);
    void setlinked(bool l);
    string getsymbol();
    int getlink();
    int getoriginallink();
    bool getavail();
    bool getlinked();
private:
    string sym;
    int link;
    int originallink;
    bool avail;
    bool linked;
};

#endif /* symbol_hpp */
