/********************************************************************
 ***  NAME  :Fangyu Zhang                                         ***
 ***  CLASS  :  CSc 446                                           ***
 ***  ASSIGNMENT : Assignment #3                                  ***
 ***  DUE DATE :  02/20/2015                                      ***
 ***  INSTRUCTOR :  Hammer                                       ***
 ********************************************************************
 ***  DESCRIPTION : This program test the the parser  by reading  ***
 ***  a file,using the lex to get the tokens and analysis those   ***
 **  tokens and grammer rules to determine the program is error   ***
 ***  parser or nor                  ********************************
 *******************************************************************/
#include<iostream>
#include<string>
#include <cstdlib>
#include <fstream> //  file input and output
#include"LexicalAnalyzer.cpp"
#include"LexicalAnalyzer.h"
#include "Parser.h"
#include <queue>//IMPORTSNT!!!!
using namespace std;

void getFilename(const int argc,const char*argv[],OneString filename);
void init(OneString a);
string convertToken(int t);

bool error=true;
queue<LexicalAnalyzer> myqueue;//using queue to store all of those tokens and values.
queue<int> line;
int main(const int argc,const char*argv[])
{
    cout<<"**********Testing parser********"<<endl;
    OneString filename;
    OneString largeString;//for each line
    OneString smallString;//for each attribution
    int next=0;
    int lineNum=1;
    LexicalAnalyzer LA(largeString);
    ifstream inFile(filename);
    getFilename(argc, argv, filename);//call function to get filename
    inFile.open(filename);//open file
    if(!inFile)
    {
        cerr<<"file not found: "<<filename<<endl;
    }
    else
    {
        while(!inFile.getline(largeString,LINE_SIZE,'\n').eof())
        {
            while(largeString[next]!='\0'){
        //   int cClass=LA.lex(largeString,next,smallString);//return charClass which is the token type
            LA.lex(largeString,next,smallString);//改动了这行从上一行
            strcpy(LA.lexeme,smallString);
            if(strlen(LA.lexeme)>=1) //important to get rid of comment!!!
                myqueue.push(LA);
                line.push(lineNum);

            init(smallString);
            }
            lineNum++;
            next=0;
        }
        // LA.Display(eoft,line);
        LA.charClass=eoft;
        myqueue.push(LA);

/*
  while(!myqueue.empty())
  {
    cout << ' ' << myqueue.front().lexeme<<"   "<<convertToken(myqueue.front().charClass)<<"  "<<myqueue.front().charClass<<"   L "<<line.front()<<endl;
    myqueue.pop();
    line.pop();
  }*/

        Parser myParser;
        if(error==true)
        {
            cout<<"successfull compilation!!!"<<endl;
        }
        else
        {
            cout<<"compile fail!!!"<<endl;
        }

    }
    inFile.close();
    return 0;
}
/*********************************************************************
***                                                                ***
***      FUNCTION:    init ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  initialize the string which stored tokens   ***
***                                                                ***
***     INPUT ARGS  :  Onestring                                   ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void init(OneString a)
{
    int length=strlen(a);
    for(int i=0;i<length;i++)
    {
        a[i]=NULL;
    }
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    getFilename ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  get the file name as the read file          ***
***                                                                ***
***     INPUT ARGS  : const int,const char*,OneString              ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void getFilename(const int argc,const char*argv[],OneString filename)
{
    if(argc==1)
    {
        cout<<"Please enter the file name:";
        cin>>filename;
        cin.get();
    }
    else
    {
        strncpy(filename,argv[1],strlen(argv[1])+1);// +1 because of the NULL character
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    Parser ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  construction to auto call PROG function     ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
Parser::Parser()
{
    PROG();
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    GetNextToken                                 ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  get the next token from the stored queue    ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::GetNextToken()
{
   if(myqueue.front().charClass!=eoft)
   {
       myqueue.pop();
       line.pop();
   }
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    match                                        ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  to check whether the current token is       ***
***     matched with the expected token or not                     ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
bool Parser::match(enum tokenType expected)
{
    if(myqueue.front().charClass==expected)
    {
        GetNextToken();
        return true;
    }
    else
    {
        cout<<"Parser Error,expexted:"<<convertToken(expected)<<" in line number :"<<line.front()<<endl;
        error=false;
        return false;
    }
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    PROG                                         ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  the initial variable for this CFG           ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/

    //PROG->programt idt ; DECLS SUB_PROGS COMP_STAT .
void Parser::PROG()
{
    match(programt);
    match(idt);
    match(semicolont);
    DECLS();
    SubProgs();
    CompStat();
    match(periodt);
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    DECLS                                        ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  DECLS ->	CONSTS VARS                        ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::DECLS()
{
    CONSTS();
    VARS();
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    CONSTS                                        ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  DECLS ->	CONSTS VARS                        ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::CONSTS()
{
    if(myqueue.front().charClass==constt)
    {
        match(constt);
        ConstDecl();
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    ConstDecl                                    ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION : CONST_DECL-> 	idt relop numt ; CONST_DECL|e  ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::ConstDecl()
{
    if(myqueue.front().charClass==idt)
       {
          match(idt);
          match(relopt);
          match(numt);
          match(semicolont);
          ConstDecl();
       }
    return;
}


/*********************************************************************
***                                                                ***
***      FUNCTION:    VARS                                         ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  VARS	-> 	vart VAR_DECL | e                ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::VARS()
{
    if(myqueue.front().charClass==vart)
    {
        match(vart);
        VarDecl();
    }
    return;
}


/*********************************************************************
***                                                                ***
***      FUNCTION:    VarDecl                                      ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  VAR_DECL	-> ID_LIST : TYPE ; VAR_DECL |e    ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::VarDecl()
{
    if(myqueue.front().charClass==idt)
    {
        IdList();
        match(colont);
        TYPE();
        match(semicolont);
        VarDecl();
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:   Idlist                                        ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  IdList	-> 	idt IdListTail                 ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/

/*
IdList	-> 	idt |IdList , idt
convert to: IdList	-> 	idt IdListTail
			IdListTail -> , idt IdListTail |E
*/


void Parser::IdList()
{
    match(idt);
    IdListTail();
    return;
}


/*********************************************************************
***                                                                ***
***      FUNCTION:    IdListTail                                   ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  IdListTail -> , idt IdListTail |E           ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::IdListTail()
{
    if(myqueue.front().charClass==commat)
    {
        match(commat);
        match(idt);
        IdListTail();
    }
    return;
}


/*********************************************************************
***                                                                ***
***      FUNCTION:    TYPE                                         ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  TYPE	->	integer | real                     ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::TYPE()
{
    if(myqueue.front().charClass==integert)
    {
        match(integert);
    }
    else if(myqueue.front().charClass==realt)
    {
        match(realt);
    }
    else
    {
        cout<<"Parse error, wrong type!"<<endl;
    }
    return;
}


/*********************************************************************
***                                                                ***
***      FUNCTION:    SunProgs                                     ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  SUB_PROGS ->	SUB_PROGSTail                  ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
//SUB_PROGS		->	SUB_PROGS SUB_DECL | E
//vovert to: SUB_PROGS		->	SUB_PROGSTail
//          SUB_PROGSTail	->	SUB_DECL SUB_PROGSTail |e
void Parser::SubProgs()
{
    SubProgsTail();
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    SubProgsTail                                 ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  SUB_PROGSTail ->	SUB_DECL SUB_PROGSTail |e  ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/

void Parser::SubProgsTail()
{
    if(myqueue.front().charClass==proceduret)
    {
        SubDecl();
        SubProgsTail();
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    SubDecl                                      ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  SUB_DECL->proceduret  idt ARGS;DECLS COMP_STAT;
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::SubDecl()
{
    match(proceduret);
    match(idt);
    ARGS();
    match(semicolont);
    DECLS();
    CompStat();
    match(semicolont);
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    ARGS                                         ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  ARGS	->	( ARG_LIST ) |e                    ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/

void Parser::ARGS()
{
    if(myqueue.front().charClass==lbrackett)
    {
        match(lbrackett);
        ArgList();
        match(rbrackett);
    }
    return;
}
/*********************************************************************
***                                                                ***
***      FUNCTION:    ArgList                                      ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  ARG_LIST	-> 	MODE ID_LIST : TYPE MORE_ARGS  ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::ArgList()
{
    MODE();
    IdList();
    match(colont);
    TYPE();
    MoreArgs();
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    :MoreArgs                                    ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  MORE_ARGs-> 	; ARG_LIST |e                 ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::MoreArgs()
{
    if(myqueue.front().charClass==semicolont)
    {
        match(semicolont);
        ArgList();
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    MODE                                         ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  MODE		->	vart |e                       ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::MODE()
{
    if(myqueue.front().charClass==vart)
    {
        match(vart);
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    CompStat                                     ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  COMP_STAT->	begint  STAT_LIST	endt       ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::CompStat()
{
    match(begint);
    StatList();
    match(endt);
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    StatList                                     ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  STAT_LIST	->	e                          ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::StatList()
{
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:   convertToken                                  ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  to convert the type of the lexeme and return***
                    the name of token type
***                                                                ***
***     INPUT ARGS  :  int                                         ***
***     OUTPUT ARGS :  string                                      ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
string convertToken(int t)
{
    string s;
    switch(t)
    {
        case programt:
            s="programt";
            break;
        case proceduret:
            s="proceduret";
            break;
        case functiont:
            s="functiont";
            break;
        case vart:
            s="vart";
            break;
        case begint:
            s="begint";
            break;
        case endt:
            s="endt";
            break;
        case ift:
            s="ift";
            break;
        case thent:
            s="thent";
            break;
        case elset:
            s="elset";
            break;
        case whilet:
            s="whilet";
            break;
        case dot:
            s="dot";
            break;
        case realt:
            s="realt";
            break;
        case integert:
            s="integert";
            break;
        case constt:
            s="constt";
            break;
        case chart:
            s="chart";
            break;
		case addopt:
		    s="addopt";
		    break;
		case mulopt:
		    s="mulopt";
		    break;
		case idt:
		    s="idt";
		    break;
        case numt:
            s="numt";
            break;

        case literalt:
            s="literalt";
            break;
		case relopt:
		    s="relopt";
		    break;
		case assigopt  :
		    s="assigopt";
		    break;
		case lparent  :
		    s="lparent";
		    break;
		case rparent  :
		    s="rparent";
		    break;
		case lbrackett:
		    s="lbrackett";
		    break;
		case rbrackett:
		    s="rbrackett";
		    break;
		case lbracet  :
		    s="lbracet";
		    break;
		case rbracet  :
		    s="rbracet";
		    break;
		case colont   :
		    s="colont";
		    break;
		case commat   :
		    s="commat";
		    break;
		case semicolont:
		    s="semicolont";
		    break;
		case tildet    :
		    s="tildet";
		    break;
		case periodt   :
		    s="periodt";
            break;
		case eoft      :
		    s="eoft";
		    break;
		case unknownt  :
		    s="unknownt";
		    break;
    }
    return s;
}


