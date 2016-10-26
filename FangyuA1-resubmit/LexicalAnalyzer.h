/********************************************************************
 ***  NAME  :Fangyu Zhang                                         ***
 ***  CLASS  :  CSc 446                                          ***
 ***  ASSIGNMENT : Assignment #1                                  ***
 ***  DUE DATE :  02/11/2014                                      ***
 ***  INSTRUCTOR :  Hammer                                       ***
 ********************************************************************
 ***  DESCRIPTION : This head file define the the members of     ***
 ***  lexical Analyzer , it defines all the allowed symbols and ****
 ***  reserved word and legal and other legal tokens which will  **
 **** be recognized and counted by the lex function   **************
 *******************************************************************/


#ifndef LEXICALANALYZER_H_INCLUDED
#define LEXICALANALYZER_H_INCLUDED

#include<iostream>
using namespace std;

const int LINE_SIZE=80;
typedef char OneString[LINE_SIZE+1];
int LParent=0;
int RParent=0;
int litNum=0;

//enum Token{RW,LETTER,DIGIT,ID,RELOP,ADDOP,MULOP,ASSIGNOP,NUM,LP,RP,LB,RB,SM,COLON,COMMA,P,UNKNOWN,ERROR,SPACE,COMM};
enum tokenType
{
	    programt,
	    proceduret,
        functiont,
        vart,
        begint,
        endt,
        ift,
        thent,
        elset,
        whilet,
        dot,
        realt,
        integert,
        chart,
		addopt,
		mulopt,
		idt,
		numt,
		literalt,
		relopt,
		assigopt,
		lparent,
		rparent,
		lbrackett,
		rbrackett,
		lbracet,
		rbracet,
		colont,
		commat,//30
		semicolont,
		tildet,
		periodt,
		eoft,
		unknownt,
};
enum RW {PROGRAM,PROCEDURE,FUNCTION,VAR,BEGIN,END,IF,THEN,ELSE,WHILE,DO,REAL,INTEGER,CHAR,OR,DIV,MOD,AND};

class LexicalAnalyzer
{
public:
    int charClass;
    OneString lexeme;//smallString
    OneString input;//largeString

public:
/*********************************************************************
***                                                                ***
***      FUNCTION:    lex ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  organize a large string divide into several ***
***     tokens                                                     ***
***     INPUT ARGS  :  OneString,int&,OneString                    ***
***     OUTPUT ARGS :  int                                          ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
    int lex(OneString largeString,int&next,OneString smallString,int&plNum,int&prNum);
/*********************************************************************
***                                                                ***
***      FUNCTION:    LexicalAnalyzer ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  constructor                                 ***
***     tokens                                                     ***
***     INPUT ARGS  :  Onestring                                   ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
    LexicalAnalyzer(OneString in="");
    /*********************************************************************
***                                                                ***
***      FUNCTION:    ~LexicalAnalyzer ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  destructor                                  ***
***     tokens                                                     ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
    virtual~LexicalAnalyzer();
/*********************************************************************
***                                                                ***
***      FUNCTION:    Display ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  show each token's information               ***
***     tokens                                                     ***
***     INPUT ARGS  :  int                                         ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
};



#endif // LEXICALANALYZER_H_INCLUDED
