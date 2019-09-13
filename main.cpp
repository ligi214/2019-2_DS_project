//
//  main.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 11/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include <iostream>
#include "node.hpp"
#include "symbol.hpp"
// #include <vector>
const int hashtablesize = 3000;
node memArray[31];  // Have size 31 in order to start with index 1 not 0
symbol symbolTable[hashtablesize];
// vector<string> tokens;
string tokens[31];
int current = -1;
#include "operation.hpp"

int main(int argc, const char * argv[]) {
    
    initialize();
    
    string data; // input string
    
    while(true){
        cout << ">";
        getline(cin, data);
        if(data.compare("exit") == 0) break;
        tokenizer(data);
        if(tokens[0].compare("(") != 0){
            printSymbol(data);
            clear();
            continue;
        }
        int root = read();
        cout << "]";
        print(root, data);
        dealloc(root);
        clear();
    }
    return 0;
}
