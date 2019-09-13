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
#include <vector>
node memArray[31];
symbol symbolTable[3000];
vector<string> tokens;
int current;
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
            tokens.clear();
            continue;
        }
        int root = read();
        cout << "]";
        print(root, data);
        dealloc(root);
        tokens.clear();
    }
    return 0;
}
