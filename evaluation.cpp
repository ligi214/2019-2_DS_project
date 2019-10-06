//
//  evaluation.cpp
//  Scheme_ass1
//
//  Created by SeongminLee on 25/09/2019.
//  Copyright © 2019 SeongminLee. All rights reserved.
//
//  Newly created for project 2
//

#include "evaluation.hpp"
#include <iostream>
#include <string>
using namespace std;

const int hashtablesize = 3000;
const int memArraySize = 100;
extern node memArray[memArraySize+1];
extern symbol symbolTable[hashtablesize];

extern int getHashValue_keyword(string s);
extern int getHashValue(string s);

const int LEFTPAREN = getHashValue_keyword("(");
const int RIGHTPAREN = getHashValue_keyword(")");
const int PLUS = getHashValue_keyword("+");
const int MINUS = getHashValue_keyword("-");
const int TIMES = getHashValue_keyword("*");
const int isNUMBER = getHashValue_keyword("number?");
const int isSYMBOL = getHashValue_keyword("symbol?");
const int isNULL = getHashValue_keyword("null?");
const int CONS = getHashValue_keyword("cons");
const int COND = getHashValue_keyword("cond");
const int ELSE = getHashValue_keyword("else");
const int CAR = getHashValue_keyword("car");
const int CDR = getHashValue_keyword("cdr");
const int DEFINE = getHashValue_keyword("define");
const int LAMBDA = getHashValue_keyword("lambda");
const int QUOTE = getHashValue_keyword("quote");
const int SCHEME_TRUE = getHashValue_keyword("#t");
const int SCHEME_FALSE = getHashValue_keyword("#f");
const int NIL = getHashValue_keyword("()");
const int ERROR = -10000;
const int NULL_RESULT = -5000;

float getVal(int hashval){
    // Input param : hashval < 0
    // return integer value that the node with given hash value holds
    if(hashval<0) hashval *= (-1);
    if(symbolTable[hashval].getlink()==0){
        string s = symbolTable[hashval].getsymbol();
        return atof(s.c_str());
    }
    return getVal(symbolTable[hashval].getlink());
}

bool isFunction(int root){
    // Input param : root > 0
    // return true if list with the given root represents function
    int indicator = memArray[memArray[memArray[memArray[root].getrchild()].getrchild()].getlchild()].getlchild();
    // if list with the given root holds function, indicator's lchild must be lambda
    indicator = indicator * (-1);
    if(indicator == LAMBDA) return true;
    return false;
}

bool isNumber(int hashval){
    // Input param : hashval
    // return true if symbol with the hash value is numeric (both integer and float)
    if(hashval == ERROR) return false;
    if(hashval<0 && hashval>-hashtablesize) hashval=-hashval;
    else return false;
    int dot = 0;
    string s = symbolTable[hashval].getsymbol();
    for(int i=0;i<s.length();i++){
        if(s[i]>=48 && s[i]<=57) continue;
        else if(dot==0 && s[i]==46){
            dot++;
            continue;
        }
        else return false;
    }
    return true;
}

int eval(int root){
    /*
     * return hash value of the node which involves answer
     *
     * negative if the answer is symbol,
     * positive if the answer is a node of memArray
     * return 0 if error case
     */
    if(root<0 && isNumber(root)) return root;
    if(root<0 && !symbolTable[-root].getlinked()) return ERROR;
    else if(root<0) return symbolTable[-root].getlink();
    else if(root==0) return root;
    
    int token_index = -memArray[root].getlchild();
    if(token_index==0) return 0;
    else if(token_index == PLUS){
        if(memArray[root].getfree()) return 0;
        else if(memArray[memArray[root].getrchild()].getfree()) return 0;
        else if(memArray[memArray[memArray[root].getrchild()].getrchild()].getfree()) return 0;
        
        int hashVal1 = memArray[memArray[root].getrchild()].getlchild();
        int hashVal2 = memArray[memArray[memArray[root].getrchild()].getrchild()].getlchild();
        if(hashVal1 > 0) hashVal1 = eval(hashVal1);
        if(hashVal2 > 0) hashVal2 = eval(hashVal2);
        float ans = getVal(hashVal1) + getVal(hashVal2);
        string s = to_string(ans);
        return getHashValue(s)*(-1);
    }
    else if(token_index == MINUS){
        if(memArray[root].getfree()) return 0;
        else if(memArray[memArray[root].getrchild()].getfree()) return 0;
        else if(memArray[memArray[memArray[root].getrchild()].getrchild()].getfree()) return 0;
        
        int hashVal1 = memArray[memArray[root].getrchild()].getlchild();
        int hashVal2 = memArray[memArray[memArray[root].getrchild()].getrchild()].getlchild();
        if(hashVal1 > 0) hashVal1 = eval(hashVal1);
        if(hashVal2 > 0) hashVal2 = eval(hashVal2);
        float ans = getVal(hashVal1) - getVal(hashVal2);
        string s = to_string(ans);
        return getHashValue(s)*(-1);
    }
    else if(token_index == TIMES){
        if(memArray[root].getfree()) return 0;
        else if(memArray[memArray[root].getrchild()].getfree()) return 0;
        else if(memArray[memArray[memArray[root].getrchild()].getrchild()].getfree()) return 0;
        
        int hashVal1 = memArray[memArray[root].getrchild()].getlchild();
        int hashVal2 = memArray[memArray[memArray[root].getrchild()].getrchild()].getlchild();
        if(hashVal1 > 0) hashVal1 = eval(hashVal1);
        if(hashVal2 > 0) hashVal2 = eval(hashVal2);
        float ans = getVal(hashVal1) * getVal(hashVal2);
        string s = to_string(ans);
        return getHashValue(s) * (-1);
    }
    else if(token_index == isNUMBER){
        // if(memArray[root].getrchild()<0) return ERROR;
        if(isNumber(eval(memArray[memArray[root].getrchild()].getlchild()))) return -SCHEME_TRUE;
        return -SCHEME_FALSE;
    }
    else if(token_index == isSYMBOL){
        // if(memArray[root].getrchild()<0) return ERROR;
        int result = eval(memArray[memArray[root].getrchild()].getlchild());
        if(result!=0 && !isNumber(result)) return -SCHEME_TRUE;
        return -SCHEME_FALSE;
    }
    else if(token_index == isNULL){
        if(memArray[root].getrchild()==0 || eval(memArray[memArray[root].getrchild()].getlchild())==0) return -SCHEME_TRUE;
        return -SCHEME_FALSE;
    }
    else if(token_index == CONS){
        int temp = alloc();
        memArray[temp].setfree(false);
        memArray[temp].setlchild(eval(memArray[memArray[root].getrchild()].getlchild()));
        memArray[temp].setrchild(eval(memArray[memArray[memArray[root].getrchild()].getrchild()].getlchild()));
        
        return temp;
    }
    else if(token_index == COND){
        while(memArray[memArray[root].getrchild()].getrchild()!=0){
            root = memArray[root].getrchild();
            if(eval(memArray[memArray[root].getlchild()].getlchild())==-SCHEME_TRUE){
                return eval(memArray[memArray[memArray[root].getlchild()].getrchild()].getlchild());
            }
        }
        if(memArray[memArray[memArray[root].getrchild()].getlchild()].getlchild() != -ELSE){
            cout << "ERROR in COND statement " << endl;
            return ERROR;
        }
        return eval(memArray[memArray[memArray[memArray[root].getrchild()].getlchild()].getrchild()].getlchild());
        }
    else if(token_index == CAR){
        // return node number or hash value of car value of the given list
        // can be both positive or negative since car value can be both symbol or list
        if(memArray[root].getfree()) return 0;
        int hashVal = memArray[eval(memArray[memArray[root].getrchild()].getlchild())].getlchild();
        return hashVal;
    }
    else if(token_index == CDR){
        // return node number of cdr value of the given list
        // positive since cdr value's type is always list
        if(memArray[root].getfree()) return 0;
        int nodeVal = memArray[eval(memArray[memArray[root].getrchild()].getlchild())].getrchild();
        // if(nodeVal==0) return 0;
        // cout << "nodeval is " << nodeVal << endl;
        return nodeVal;
    }
    else if(token_index == DEFINE){
        int defTermHashVal = memArray[memArray[root].getrchild()].getlchild()*(-1);
        int defContent = memArray[memArray[memArray[root].getrchild()].getrchild()].getlchild();
        if(isFunction(root)){
            symbolTable[defTermHashVal].setlink(defContent);
            symbolTable[defTermHashVal].setlinked(true);
        }
        else{
            symbolTable[defTermHashVal].setlink(eval(defContent));
            symbolTable[defTermHashVal].setlinked(true);
        }
        return NULL_RESULT;
    }
    else if(token_index == QUOTE){
        return memArray[memArray[root].getrchild()].getlchild();
    }
    else{
        // User function call or symbol call
        int lambdaNode = symbolTable[token_index].getlink();
        int stack_depth = 0;
        if(lambdaNode>0 && memArray[lambdaNode].getlchild()==LAMBDA*(-1)){
            // User defined function call
            int varNode = memArray[memArray[lambdaNode].getrchild()].getlchild();
            int newValNode = memArray[root].getrchild();
            do {
                // funcVarHashVal : node which statement regarding function variables starts
                // newVal : new values which will be substituted to function variable symbols
                // sorry to future myself for using nasty naming system
                int funcVarHashVal = memArray[varNode].getlchild();
                int newVal = eval(memArray[newValNode].getlchild());
                if(funcVarHashVal != newVal){
                    funcVarHashVal *= (-1);
                    // funcVarHashVal에 원래 들어있던 값이랑 이런 거 스택에다가 push
                    push(symbolTable[funcVarHashVal]);
                    symbolTable[funcVarHashVal].setlink(newVal);
                    symbolTable[funcVarHashVal].setlinked(true);
                    stack_depth++;
                }
                varNode = memArray[varNode].getrchild();
                newValNode = memArray[newValNode].getrchild();
            } while(varNode>0 && newValNode>0);
            
            int ans = eval(memArray[memArray[memArray[lambdaNode].getrchild()].getrchild()].getlchild());
            
            while(true){
                if(getSize()<=0) break;
                if(stack_depth<=0) break;
                symbol s = top();
                pop();
                stack_depth--;
                int hashVal = getHashValue(s.getsymbol());
                symbolTable[hashVal].setlink(s.getlink());
                symbolTable[hashVal].setlinked(s.getlinked());
            }
            return ans;
        }
        else if(lambdaNode==0 && !symbolTable[token_index].getlinked() && !isNumber(-token_index)) return ERROR;  // not allocated
        else if(lambdaNode==0 && symbolTable[token_index].getlinked()) return 0;
        else if(lambdaNode==0) return root;
        return lambdaNode;
    }
    return NULL_RESULT;
}

