/********************************************************************
 ***  NAME  :Fangyu Zhang                                         ***
 ***  CLASS  :  CSc 446                                          ***
 ***  ASSIGNMENT : Assignment #3                                  ***
 ***  DUE DATE :  02/20/2014                                      ***
 ***  INSTRUCTOR :  Hammer                                       ***
 ********************************************************************
 ***  DESCRIPTION : This head file define the the members of     ***
 ***  parser  , it defines all the allowed variables(or extented ***
 ***  functions) for the context free grammer, once it get parser ***
 ***  error with using the match function, then this parser will  ***
 **** feed back what the problem there  ****************************/

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include<string>
//#include "TableEntry.h"
using namespace std;

class Parser
{
public:
    Parser();
    bool match(enum tokenType);
    void GetNextToken();
    bool checkVar(int,OneString);//to check if the variable is declared ot not
    void PROG();
    void DECLS();
    void CONSTS();
    void ConstDecl();
    void VARS();
    void VarDecl();
    void IdList();
    void IdListTail();
    void TYPE();
    void SubProgs();
    void SubProgsTail();
    void SubDecl();
    void ARGS();
    void ArgList();
    void MoreArgs();
    void MODE();
    void CompStat();
    void StatList();
    void Statement();
    void StatTail();
    void AssignStat();
    void IOStat();
    void Expr();
    void Relation();
    void SimpleExpr();
    void MoreTerm();
    void Term();
    void MoreFactor();
    void Factor();
    void Addop();
    void Mulop();
    void SignOp();
};




#endif // PARSER_H_INCLUDED
