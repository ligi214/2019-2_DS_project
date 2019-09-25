//
//  operation.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include "operation.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

extern const int hashtablesize = 3000;
extern node memArray[31];
extern symbol symbolTable[hashtablesize];
extern string tokens[31];
extern int current;  // deal with token index while building parse tree
const char LEFTPAREN = '(';
const char RIGHTPAREN = ')';

extern int token_current;  // to pushback into tokens array
int freeroot = 1;

void initialize(){
    token_current = 0;
    for(int i=0;i<31;i++){
        memArray[i].setfree(true);
        memArray[i].setrchild(i+1);
        memArray[i].setlchild(NULL);
    }
    memArray[30].setrchild(0);  // Point to NULL in freelist
    for(int i=0;i<3000;i++){
        symbolTable[i].setlink(NULL);
        symbolTable[i].setsymbol("");
        symbolTable[i].setavail(true);
    }
    symbolTable[LEFTPAREN].setsymbol("(");
    symbolTable[RIGHTPAREN].setsymbol(")");
}

int getHashValue(string s){
    int hashval = 0;
    for(int i = 0; i<s.length(); i++){
        // Change uppercase to lowercase
        if(s[i]>=65 && s[i]<=90){
            tokens[current][i] += 32;
            s[i] += 32;
        }
        hashval = hashval * 128 + s[i];
        hashval = hashval % hashtablesize;
    }
    while(!symbolTable[hashval].getavail() && s.compare(symbolTable[hashval].getsymbol())!=0){
        hashval ++;
    }
    if(symbolTable[hashval].getavail()){ // New symbol node
        symbolTable[hashval].setavail(false);
        symbolTable[hashval].setsymbol(s);
    }
    return hashval;
}

void pushback(string s){
    tokens[token_current++] = s;
}

void clear(){
    for(int i = 0 ; i < 31; i++){
        tokens[i] = "";
    }
}

void tokenizer(string data){ // Tokenize input string
    string token;
    stringstream ss(data);
    int front = 0;
    current = -1;
    while(ss >> token){
        if(token[0] == '('){ // Tokenize left parenthesis
            pushback("(");
            tokenizer(token.substr(1));
        }
        else if(token[token.size()-1] == ')'){ // Tokenize right parenthesis
            tokenizer(token.substr(0, token.size()-1));
            pushback(")");
        }
        else if(token.find('(') != string::npos || token.find(')') != string::npos){
            front = 0;
            for(int i = 0 ; i < token.size() ; i++){
                if(token[i] != '(' && token[i] != ')') continue;
                if(i > front) pushback(token.substr(front, i-front));
                front = i+1;
                if(token[i] == '(') pushback("(");
                else if(token[i] == ')') pushback(")");
            }
            if(front != token.size()) pushback(token.substr(front, token.size()-front));
        }
        else{
            pushback(token);
        }
    }
}

string getNextToken(){
    current++;
    return tokens[current];
}

int alloc(){
    int temp = freeroot;
    freeroot = memArray[temp].getrchild();
    memArray[temp].setfree(false);
    return temp;
}

int read(){
    int root = 1;
    int temp = NULL;
    bool first = true;
    int tokenhashval = getHashValue(getNextToken());
    if(tokenhashval==LEFTPAREN){
        while((tokenhashval = getHashValue(getNextToken())) != RIGHTPAREN){
            if(first){
                first = false;
                temp = alloc();
                memArray[temp].setfree(false);
                root = temp;
            }
            else{
                memArray[temp].setrchild(alloc());
                temp = memArray[temp].getrchild();
                memArray[temp].setfree(false);
            }
            
            if(tokenhashval==LEFTPAREN){
                current--;
                memArray[temp].setlchild(read());
                memArray[temp].setrchild(NULL);
            }
            else{
                memArray[temp].setlchild(tokenhashval * (-1));
                memArray[temp].setrchild(NULL);
            }
        }
        return root;
    }
    else{
        return tokenhashval * (-1);
    }
}

void memArrayPrint(int root){
    for(int i = 1 ; i < 31 ; i++){
        cout << "[Node #" << i << "] ";
        cout << "Left child : " << memArray[i].getlchild() << ", ";
        cout << "Right child : " << memArray[i].getrchild() << ", ";
        if(memArray[i].getfree()) cout << "FREE" << endl;
        else cout << "ALLOCATED" << endl;
    }
    cout << endl;
}

void symbolTablePrint(){
    for(int i=0;i<3000;i++){
        if(symbolTable[i].getavail() == false){
            cout << "Symbol Table #" << i << " : " << symbolTable[i].getsymbol() << endl;
        }
    }
    cout << endl;
}

void print(int root, string data){
    cout << "Free list's root node index : " << freeroot << endl;
    cout << "Memory Array's root node index : " << root << endl << endl;
    memArrayPrint(root);
    symbolTablePrint();
    
    if(token_current==2 && tokens[0].compare("(")==0 && tokens[1].compare(")")==0){
        cout << "NULL" << endl << endl;
        return;
    }
    
    for(int i = 0; i<token_current; i++){
        if(tokens[i].compare("(")==0) cout << tokens[i];
        else if(i+1 < token_current){
            if(tokens[i+1].compare(")")==0) cout << tokens[i];
            else cout << tokens[i] << " ";
        }
        else cout << tokens[i] << " ";
    }
    cout << endl;
}

void printSymbol(string data){
    int hashvalue = 0;
    for(int i=0 ; i<token_current; i++){
        hashvalue = getHashValue(tokens[i]);
        cout << "Input symbol : " << tokens[i] << ", Hash value : " << hashvalue << "(" << -hashvalue << " in negative)" << endl;
    }
    cout << endl;
    cout << "Free list's root node index : " << freeroot << endl;
    cout << "Does not occupy any space in Memory Array (No root defined)" << endl << endl;
    memArrayPrint(0);
    symbolTablePrint();
}

void dealloc(int root){
    if(memArray[root].getfree()) return;
    memArray[root].setfree(true);
    int lchild = memArray[root].getlchild();
    int rchild = memArray[root].getrchild();
    memArray[root].setrchild(freeroot);  // add the node to frontmost position of free list
    memArray[root].setlchild(0);  // simply to initialize lchild to 0
    freeroot = root;
    if(lchild > 0) dealloc(lchild);
    if(rchild > 0) dealloc(rchild);
}
