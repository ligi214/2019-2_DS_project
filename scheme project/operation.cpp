//
//  operation.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 12/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//

#include "operation.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

extern const int hashtablesize = 1031;
extern int memArraySize;
extern const int tokensSize = 200;
extern node* memArray;
extern symbol symbolTable[hashtablesize];
extern string tokens[tokensSize+1];
extern int current;  // deal with token index while building parse tree
extern int token_current;  // to pushback into tokens array
int freeroot = 1;

/*
int getHashValue_keyword(string s){
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
    return hashval;
}
 */

const int LEFTPAREN = 1;
const int RIGHTPAREN = 2;
const int SCHEME_TRUE = 3;
const int SCHEME_FALSE = 4;
const int PLUS = 5;
const int MINUS = 6;
const int TIMES = 7;
const int isNUMBER = 8;
const int isSYMBOL = 9;
const int isNULL = 10;
const int CONS = 11;
const int COND = 12;
const int ELSE = 13;
const int CAR = 14;
const int CDR = 15;
const int DEFINE = 16;
const int QUOTE = 17;
const int LAMBDA = 18;

const int ERROR = -10000;

int getHashValue(string s){
    int hashval = 0;
    for(int i = 0; i<s.length(); i++){
        // Change uppercase to lowercase
        if(s[i]>=65 && s[i]<=90){
            tokens[current][i] += 32;
            s[i] += 32;
        }
    }
    if(s.compare("(")==0) hashval = LEFTPAREN;
    else if(s.compare(")")==0) hashval = RIGHTPAREN;
    else if(s.compare("#t")==0) hashval = SCHEME_TRUE;
    else if(s.compare("#f")==0) hashval = SCHEME_FALSE;
    else if(s.compare("+")==0) hashval = PLUS;
    else if(s.compare("-")==0) hashval = MINUS;
    else if(s.compare("*")==0) hashval = TIMES;
    else if(s.compare("number?")==0) hashval = isNUMBER;
    else if(s.compare("symbol?")==0) hashval = isSYMBOL;
    else if(s.compare("null?")==0) hashval = isNULL;
    else if(s.compare("cons")==0) hashval = CONS;
    else if(s.compare("cond")==0) hashval = COND;
    else if(s.compare("else")==0) hashval = ELSE;
    else if(s.compare("car")==0) hashval = CAR;
    else if(s.compare("cdr")==0) hashval = CDR;
    else if(s.compare("define")==0) hashval = DEFINE;
    else if(s.compare("quote")==0) hashval = QUOTE;
    else if(s.compare("lambda")==0) hashval = LAMBDA;
    else{
        for(int i=0;i<s.length();i++){
            hashval += (s[i]*s[i]);
            hashval = hashval % hashtablesize;
        }
        while(!symbolTable[hashval].getavail() && s.compare(symbolTable[hashval].getsymbol())!=0){
            hashval ++;
        }
        hashval = hashval%hashtablesize;
    }
    if(symbolTable[hashval].getavail()){ // New symbol node
        symbolTable[hashval].setavail(false);
        symbolTable[hashval].setsymbol(s);
    }
    return hashval;
}

void initialize(){
    token_current = 0;
    current = -1;
    for(int i=0;i<=memArraySize;i++){
        memArray[i].setfree(true);
        memArray[i].setrchild(i+1);
        memArray[i].setlchild(0);
    }
    memArray[memArraySize].setrchild(0);  // Point to NULL in freelist
    for(int i=0;i<hashtablesize;i++){
        symbolTable[i].setlink(0);
        symbolTable[i].setoriginallink(0);
        symbolTable[i].setsymbol("");
        symbolTable[i].setavail(true);
        symbolTable[i].setlinked(false);
    }
    getHashValue("(");
    getHashValue(")");
    getHashValue("+");
    getHashValue("-");
    getHashValue("*");
    getHashValue("number?");
    getHashValue("symbol?");
    getHashValue("null?");
    getHashValue("cons");
    getHashValue("cond");
    getHashValue("else");
    getHashValue("car");
    getHashValue("cdr");
    getHashValue("define");
    getHashValue("lambda");
    getHashValue("quote");
    getHashValue("#t");
    getHashValue("#f");
}

void new_memArray_initialize(int old_memArraySize, int new_memArraySize){
    current = -1;
    for(int i=new_memArraySize;i>old_memArraySize;i--){
        memArray[i].setfree(true);
        memArray[i].setflag(0);
        memArray[i].setrchild(freeroot);
        memArray[i].setlchild(0);
        freeroot = i;
    }
}

// const int NIL = getHashValue("()");

void pushback(string s){
    tokens[token_current++] = s;
}

void clearTokens(){
    token_current = 0;
    for(int i = 0 ; i <= tokensSize; i++){
        tokens[i] = "";
    }
}

string preprocessing(){
    string newcommand = "";
    string token;
    int num_of_left_paren = 0;
    // Have used redundant white spaces since those blanks will be eventually ignored by tokenizer
    while(((token=getNextToken()).compare(""))!=0){
        if(token.compare("define")==0){
            newcommand = newcommand + "define ";
            token = getNextToken();
            if(token.compare("(")==0){  // define function
                token = getNextToken();
                newcommand = newcommand + token + "(lambda(" + preprocessing() + ")";
            }
            else newcommand = newcommand + token + " ";
        }
        else if(token.compare("'")==0 || token.compare("`")==0){
            newcommand = newcommand + "(quote ";
            num_of_left_paren = 0;
            do {
                token = getNextToken();
                newcommand = newcommand + token + " ";
                if(token.compare("(")==0) num_of_left_paren++;
                else if(token.compare(")")==0) num_of_left_paren--;
            } while (num_of_left_paren>0);
            newcommand = newcommand + ")";
        }
        else newcommand = newcommand + token + " ";
    }
    return newcommand;
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
        else if(token[0] == '\''){ // Tokenize quotation
            pushback("'");
            tokenizer(token.substr(1));
        }
        else if(token[0] == '`'){ // Tokenize quotation
            pushback("`");
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
    if(temp<=0 || temp>memArraySize){
        // cout << "Have allocated all memory array spaces" << endl;
        return ERROR;
    }
    freeroot = memArray[temp].getrchild();
    memArray[temp].setfree(false);
    return temp;
}

int read(){
    int root = 0;
    int temp = 0;
    int t = 0;
    bool first = true;
    int tokenhashval = getHashValue(getNextToken());
    if(tokenhashval==LEFTPAREN){
        while((tokenhashval = getHashValue(getNextToken())) != RIGHTPAREN){
            if(first){
                first = false;
                temp = alloc();
                if(temp==ERROR) return ERROR;
                memArray[temp].setfree(false);
                root = temp;
            }
            else{
                t = alloc();
                if(t==ERROR) return ERROR;
                memArray[temp].setrchild(t);
                temp = memArray[temp].getrchild();
                memArray[temp].setfree(false);
            }
            
            if(tokenhashval==LEFTPAREN){
                current--;
                t = read();
                if(t==ERROR) return ERROR;
                memArray[temp].setlchild(t);
                memArray[temp].setrchild(0);
            }
            else{
                memArray[temp].setlchild(tokenhashval * (-1));
                memArray[temp].setrchild(0);
            }
        }
        return root;
    }
    else return tokenhashval * (-1);
}

void flagNodes(int root){
    memArray[root].setflag(1);
    int lchild = memArray[root].getlchild();
    int rchild = memArray[root].getrchild();
    if(lchild>0) flagNodes(lchild);
    if(rchild>0) flagNodes(rchild);
}

void unflagNodes(int root){
    memArray[root].setflag(0);
    int lchild = memArray[root].getlchild();
    int rchild = memArray[root].getrchild();
    if(lchild>0) flagNodes(lchild);
    if(rchild>0) flagNodes(rchild);
}

void garbagecollector(){
    for(int i = memArraySize ; i >= 1 ; i--){
        memArray[i].setflag(0);
    }
    cout << "----- Garbage Collection -----" << endl;
    for(int i=0;i<hashtablesize;i++){
        if(symbolTable[i].getavail() == false && symbolTable[i].getlink() > 0){
            flagNodes(symbolTable[i].getlink());
        }
    }
    for(int i = memArraySize ; i >= 1 ; i--){
        if(!memArray[i].getflag()){
            memArray[i].setfree(true);
            memArray[i].setlchild(0);
            memArray[i].setrchild(freeroot);
            freeroot = i;
        }
    }
}

void memArrayPrint_alloc_only_from_root(int root){
    if(root==0) return;
    if(memArray[root].getfree()) return;
    int lchild = memArray[root].getlchild();
    int rchild = memArray[root].getrchild();
    cout << "[Node #" << root << "] ";
    cout << "Left child : " << lchild << ", ";
    cout << "Right child : " << rchild << ", ";
    if(memArray[root].getfree()) cout << "FREE" << endl;
    else cout << "ALLOCATED" << endl;
    if(lchild > 0) memArrayPrint_alloc_only_from_root(lchild);
    if(rchild > 0) memArrayPrint_alloc_only_from_root(rchild);
}

void memArrayPrint_alloc_only(int root){
    for(int i = 1 ; i <= memArraySize ; i++){
        if(memArray[i].getfree()) continue;
        cout << "[Node #" << i << "] ";
        cout << "Left child : " << memArray[i].getlchild() << ", ";
        cout << "Right child : " << memArray[i].getrchild() << ", ";
        if(memArray[i].getfree()) cout << "FREE" << endl;
        else cout << "ALLOCATED" << endl;
    }
    cout << endl;
}

void memArrayPrint(int root){
    cout << "Free list's root = " << freeroot << endl;
    cout << "List's root = " << root << endl << endl;
    string s = "";
    cout.flags(ios::left);
    for(int i = 1 ; i <= memArraySize ; i++){
        cout << "[Node #";
        if(i<10) cout << "0" << i << "] ";
        else cout << i << "] ";
        s = "Left child : " + to_string(memArray[i].getlchild()) + ", ";
        cout.width(20);
        cout << s;
        cout.width(20);
        s = "Right child : " + to_string(memArray[i].getrchild()) + ", ";
        cout << s;
        cout.width(15);
        if(memArray[i].getfree()) cout << "FREE";
        else cout << "ALLOCATED";
        cout << "Flag : ";
        if(memArray[i].getflag()) cout << "1" << endl;
        else cout << "0" << endl;
    }
    cout << endl;
}

void symbolTablePrint(){
    string s = "";
    for(int i=0;i<hashtablesize;i++){
        if(symbolTable[i].getavail() == false){
            s = "Symbol Table #" + to_string(i) + " : " + symbolTable[i].getsymbol();
            cout.flags(ios::left);
            cout.width(30);
            cout << s;
            cout << "\t\t";
            s = "Pointing : " + to_string(symbolTable[i].getlink());
            cout << s << endl;
        }
    }
    cout << endl;
}

void print(int root, bool first, bool afterparenthesis){
    // cout << "Free list's root node index : " << freeroot << endl;
    // cout << "root : " << root << endl;
    // memArrayPrint(root);
    // symbolTablePrint();
    if(root==0){
        // cout << "Memory Array's root node index : " << root << endl << endl;
        cout << "()";
    }
    /*
    else if(root<0 && !symbolTable[-root].getlinked()){
        if(first) cout << symbolTable[-root].getsymbol();
        else cout << " " << symbolTable[-root].getsymbol();
    }
     
    else if(root<0 && (symbolTable[-root].getlink()==0 || symbolTable[-root].getlink()==-NIL)){
        cout << "()";
    }
     */
    else if(root<0){
        if(afterparenthesis) cout << symbolTable[-root].getsymbol();
        else cout << " " << symbolTable[-root].getsymbol();
    }
    else{
        // cout << "Memory Array's root node index : " << root << endl;
        if(first){
            cout << "(";
            print(memArray[root].getlchild(), true, true);
        }
        else print(memArray[root].getlchild(), true, false);
        
        if(memArray[root].getrchild()!=0) print(memArray[root].getrchild(), false, false);
        else cout << ")";
    }
}
/*
void printSymbol(string data){
    int hashvalue = 0;
    current = 0;
    for(int i=0 ; i<token_current; i++){
        hashvalue = getHashValue(tokens[i]);
        current++;
        int link = symbolTable[hashvalue].getlink();
        if(link==0){
            cout << "Input symbol : " << tokens[i] << ", Hash value : " << hashvalue << "(" << -hashvalue << " in negative)" << endl;
        }
        else if(link<0){
            cout << "Input symbol, " << tokens[i] << ", contains a value : " << symbolTable[-link].getsymbol() << endl;
        }
        else{
            cout << "Input symbol, " << tokens[i] << ", contains a list : " << endl;
        }
    }
    cout << endl;
    cout << "Free list's root node index : " << freeroot << endl;
    cout << "Does not occupy any space in Memory Array (No root defined)" << endl << endl;
    memArrayPrint(0);
    symbolTablePrint();
}
 */

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
