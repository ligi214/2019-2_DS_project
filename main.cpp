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
const int memArraySize = 30;
const int tokensSize = 30;
node memArray[memArraySize+1];  // Have size 31 in order to start with index 1 not 0
symbol symbolTable[hashtablesize];
string tokens[tokensSize+1];
int current = -1;
int token_current = 0;
#include "operation.hpp"
#include "evaluation.hpp"

int main(int argc, const char * argv[]) {
    
    cout << "          DS Scheme Project 1" << endl;
    cout << "        2016-18829 Seongmin Lee" << endl;
    // cout << "You can exit the program by typing \"exit\" " << endl;
    cout << endl;
    
    initialize();
    
    string data; // input string
    
    while(true){
        token_current = 0;
        cout << ">";
        getline(cin, data);
        // if(data.compare("exit") == 0) break;
        tokenizer(data);
        data = preprocessing();
        clearTokens();
        cout << data << endl;
        tokenizer(data);
        if(tokens[0].compare("(") != 0){
            printSymbol(data);
            clearTokens();
            continue;
        }
        int root = read();
        cout << "]";
        int ansHashVal = eval(root);
        if(ansHashVal > 0){
            // evaluation value is a node of memArray
            cout << "Evaluation value is a node of memArray as below :" << endl;
            memArrayPrint_alloc_only_from_root(ansHashVal);
        }
        else if(ansHashVal < 0){
            // evaluation value is symbol in symbolTable
            cout << "Evaluation value is a single value : ";
            cout << symbolTable[ansHashVal*(-1)].getsymbol() << endl;
        }
        else cout << "No evaluation value(Define etc.) or Error case" << endl;
        cout << endl;
        print(root, data);
        clearTokens();
    }
    return 0;
}
