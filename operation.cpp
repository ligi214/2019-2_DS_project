//
//  operation.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include "operation.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

extern node memArray[30];
extern symbol symbolTable[3000];
extern vector<string> tokens;
extern int current;
const char LEFTPAREN = '(';
const char RIGHTPAREN = ')';

int freeroot = 1;

void initialize(){
    for(int i=0;i<30;i++){
        memArray[i].setfree(true);
        memArray[i].setrchild(i+1);
        memArray[i].setlchild(NULL);
    }
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
        hashval += s[i];
    }
    // cout << "hash value is : " << hashval << endl;
    while(!symbolTable[hashval].getavail() && s.compare(symbolTable[hashval].getsymbol())!=0){
        hashval ++;
    }
    if(symbolTable[hashval].getavail()){ // New symbol node
        symbolTable[hashval].setavail(false);
        symbolTable[hashval].setsymbol(s);
    }
    return hashval;
}

void rightparentokenizer(string data){
    if(data[data.size()-1] == ')'){
        rightparentokenizer(data.substr(0, data.size()-1));
        tokens.push_back(")");
    }
    else tokens.push_back(data);
}

void tokenizer(string data){ // Tokenize input string
    string token;
    stringstream ss(data);
    
    int front = 0;
    current = -1;
    while(ss >> token){
        if(token[0] == '('){ // Tokenize left parenthesis
            tokens.push_back("(");
            tokens.push_back(token.substr(1));
        }
        else if(token[token.size()-1] == ')'){ // Tokenize right parenthesis
            rightparentokenizer(token);
        }
        else if(token.find('(') != string::npos || token.find(')') != string::npos){
            front = 0;
            for(int i = 0 ; i < token.size() ; i++){
                if(token[i] != '(' && token[i] != ')') continue;
                if(i > front) tokens.push_back(token.substr(front, i-front));
                front = i+1;
                if(token[i] == '(') tokens.push_back("(");
                else if(token[i] == ')') tokens.push_back(")");
            }
            if(front != token.size()) tokens.push_back(token.substr(front, token.size()-front));
        }
        else{
            tokens.push_back(token);
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
    int root = NULL;
    int temp = NULL;
    bool first = true;
    int tokenhashval = getHashValue(getNextToken());
    if(tokenhashval==LEFTPAREN){
        while((tokenhashval = getHashValue(getNextToken())) != RIGHTPAREN){
            if(first){
                first = false;
                temp = alloc();
                root = temp;
            }
            else{
                memArray[temp].setrchild(alloc());
                temp = memArray[temp].getrchild();
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
    int lchild = memArray[root].getlchild();
    int rchild = memArray[root].getrchild();
    cout << "[Node #" << root << "] ";
    cout << "Left child : " << lchild << ", ";
    cout << "Right child : " << rchild << endl;
    if(lchild > 0){
        memArrayPrint(lchild);
    }
    if(rchild > 0){
        memArrayPrint(rchild);
    }
}

void symbolTablePrint(){
    for(int i=0;i<3000;i++){
        if(symbolTable[i].getavail() == false){
            cout << "Symbol Table #" << i << " : " << symbolTable[i].getsymbol() << endl;
        }
    }
}

void print(int root, string data){
    cout << "Free list's root node index : " << freeroot << endl;
    cout << "Memory Array's root node index : " << root << endl << endl;
    memArrayPrint(root);
    cout << endl;
    symbolTablePrint();
    cout << endl;
    for(int i = 0; i<tokens.size(); i++){
        if(tokens[i].compare("(")==0) cout << tokens[i];
        else if(i+1 < tokens.size()){
            if(tokens[i+1].compare(")")==0) cout << tokens[i];
            else cout << tokens[i] << " ";
        }
        else cout << tokens[i] << " ";
    }
    cout << endl;
}

void printSymbol(string data){
    for(int i=0 ; i<tokens.size(); i++){
        getHashValue(tokens[i]);
        cout << "Input symbol : " << tokens[i] << endl;
    }
    cout << endl;
    symbolTablePrint();
}

void dealloc(int root){
    memArray[root].setfree(true);
    int lchild = memArray[root].getlchild();
    int rchild = memArray[root].getrchild();
    memArray[root].setrchild(freeroot);
    freeroot = root;
    if(lchild > 0) dealloc(lchild);
    if(rchild > 0) dealloc(rchild);
}
