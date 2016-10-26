/********************************************************************
 ***  NAME  :Fangyu Zhang                                         ***
 ***  CLASS  :  CSc 446                                           ***
 ***  ASSIGNMENT : Assignment #7                                  ***
 ***  DUE DATE :  04/08/2015                                      ***
 ***  INSTRUCTOR :  Hammer                                       ***
 ********************************************************************
 ***  DESCRIPTION : This program test the the parser  by reading  ***
 ***  a file,using the lex to get the tokens and analysis those   ***
 **  tokens and grammer rules to determine the program is error   ***
 ***  parser or nor also check the variable is declared or not    ***
 ***  And show the TAC for this parser.                           ***
 *******************************************************************/
#include<iostream>
#include<string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <string>
#include <fstream> //  file input and output
#include"LexicalAnalyzer.cpp"
#include"LexicalAnalyzer.h"
#include "Parser.h"
#include "TableEntry.cpp"
#include <queue>
#include <iomanip>
#include <stack>
using namespace std;

void getFilename(const int argc,const char*argv[],OneString filename);
void init(OneString a);
string convertToken(int t);

bool error=true;
queue<LexicalAnalyzer> myqueue;//using queue to store all of those tokens and values.
queue<int> line;
queue<enum tokenType> token;
SymbolTable T;
int Depth=1;
queue<EntryPtr> myentry;
queue<int> myoff;//offset value
int offset=0;
stack<string>tac;

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
            LA.lex(largeString,next,smallString);
            strcpy(LA.lexeme,smallString);
            if(strlen(LA.lexeme)>=1) //important to get rid of comment!!!
             {

                myqueue.push(LA);
                line.push(lineNum);
                token.push(LA.charClass);
             }

            init(smallString);
            }
            lineNum++;
            next=0;
        }
        LA.charClass=eoft;
        myqueue.push(LA);
        token.push(eoft);

        Parser myParser;
        if(error==true)
        {
            cout<<endl<<endl;
            cout<<"successfull compilation!!!"<<endl;
        }
        else
        {
            cout<<endl<<endl;
            cout<<"compile fail!!!"<<endl;
        }

        T.WriteTable(1);
	    T.WriteTable(2);
	    T.WriteTable(3);
	    cout<<"**************show the TAC************"<<endl;
        ofstream outfile;
        outfile.open("test7.pas.tac");
	    while(!tac.empty())
        {
            cout<<tac.top()<<endl;
            outfile<<tac.top()<<endl;
            tac.pop();
            myoff.pop();
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
       if(token.size()==myqueue.size())
       {
           token.pop();
       }
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
        cout<<"token:"<<left<<setw(15)<<convertToken(myqueue.front().charClass)<<right<<setw(20)<<"lexeme:"<<myqueue.front().lexeme<<setw(15)<<setw(10)<<"line"<<line.front()<<endl;
        GetNextToken();
        return true;
    }
    else
    {
        cout<<"Parser Error,expexted:"<<convertToken(expected)<<" in line number :"<<line.front()<<endl<<endl;
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
    string code;
    code.append("endp  ");
    string s=myqueue.front().lexeme;
    EntryPtr p;
    //string s1(s);
    T.Insert(myqueue.front().lexeme,idt,Depth);
    p=T.Lookup(myqueue.front().lexeme);
    p->TypeOfEntry=functionEntry;
    code.append(s);
    tac.push(code);
    myoff.push(offset);

    match(idt);
    match(semicolont);
    DECLS();
    SubProgs();
    CompStat(s);
    match(periodt);
   // free(p);
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
           EntryPtr p;
           T.Insert(myqueue.front().lexeme,idt,Depth);
           p=T.Lookup(myqueue.front().lexeme);
           p->TypeOfEntry=constEntry;
           p->Type.constant.Offset+=2;
           myentry.push(p);
           offset=offset+2;
           //myoff.push(offset);



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
    EntryPtr p;
    T.Insert(myqueue.front().lexeme,idt,Depth);
    p=T.Lookup(myqueue.front().lexeme);
    p->TypeOfEntry=varEntry;

    match(idt);
    while(token.front()!=integert&&token.front()!=realt)
    {
        token.pop();
    }
    if(token.front()==integert)
    {
        p->Type.var.TypeOfVariable=intType;
        p->Type.var.Offset+=2;
        offset+=2;
    }
    else if(token.front()==realt)
    {
        p->Type.var.TypeOfVariable=floatType;
        p->Type.var.Offset+=4;
        offset+=4;
    }
    else
    {
        p->Type.var.TypeOfVariable=charType;
        p->Type.var.Offset+=1;
        offset+=1;
    }
    myentry.push(p);
   // myoff.push(offset);
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
        EntryPtr p;
        T.Insert(myqueue.front().lexeme,idt,Depth);
        p=T.Lookup(myqueue.front().lexeme);
        p->TypeOfEntry=varEntry;

        match(idt);
        while(token.front()!=integert&&token.front()!=realt)
        {
        token.pop();
        }
        if(token.front()==integert)
        {
        p->Type.var.TypeOfVariable=intType;
        p->Type.var.Offset+=2;
        offset+=2;
        }
        else if(token.front()==realt)
        {
        p->Type.var.TypeOfVariable=floatType;
        p->Type.var.Offset+=4;
        offset+=4;
        }
        else
        {
        p->Type.var.TypeOfVariable=charType;
        p->Type.var.Offset+=1;
        offset+=1;
        }
        myentry.push(p);
     //   myoff.push(offset);
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
    string code;
    EntryPtr p;
    string s=myqueue.front().lexeme;
    T.Insert(myqueue.front().lexeme,idt,Depth);
    p=T.Lookup(myqueue.front().lexeme);
    p->TypeOfEntry=functionEntry;
    code.append("endp ");
    code.append(s);
    tac.push(code);

    match(idt);
    ARGS();
    match(semicolont);
    DECLS();
    CompStat(s);
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
   // bool isPush=false;
    if(myqueue.front().charClass==lbrackett)
    {
        match(lbrackett);
        Depth++;
     //   isPush=true;
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
void Parser::CompStat(string lexeme)
{
    string code;
    code.append("Proc ");
    code.append(lexeme);
    match(begint);
    StatList();
    match(endt);
    Depth--;
    tac.push(code);
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

/*********************************************************************
***                                                                ***
***      FUNCTION:    StatList                                     ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  StatList ->Statement   Stat_Tail |e         ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::StatList()
{
    if(myqueue.front().charClass==idt)
    {
        Statement();
        StatTail();
    }
    else if(myqueue.front().charClass==semicolont)
    {
        Statement();
    }
    else {}
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:   StatTail                                      ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  StatTail->; Statement Stat_Tail |e          ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::StatTail()
{
    if(myqueue.front().charClass==semicolont)
    {
        match(semicolont);
        Statement();
        StatTail();
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:    Statement                                     ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION :  Statement -> 	AssignStat	|IOStat        ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::Statement()
{
    if(myqueue.front().charClass==idt)
    {
        AssignStat();
    }
    return;
}

/*********************************************************************
***                                                                ***
***      FUNCTION:   AssignStat                                    ***
***                                                                ***
**********************************************************************
***                                                                ***
***     DESCRIPTION : AssignStat	->	idt  :=  Expr |  ProCall   ***
***                                                                ***
***     INPUT ARGS  :  none                                        ***
***     OUTPUT ARGS :  none                                        ***
***     IN/OUT ARGS :  none                                        ***
***                                                                ***
*********************************************************************/
void Parser::AssignStat()
{
    EntryPtr p;
	p=T.Lookup(myqueue.front().lexeme);
    int m1=p->Type.var.Offset;
    int i=0;
	if(p!=NULL)
    {
        while(p->TypeOfEntry!=varEntry&&!p)
        {
            p=p->next;
        }
    }

    if(p==NULL)
    {
        cout<<"the lexeme "<<myqueue.front().lexeme<<" in line "<<line.front()<<" is undeclared!"<<endl<<endl;
    }
    else
    {
        cout<<"the lexeme "<<myqueue.front().lexeme<<" in line "<<line.front()<<" is declared!"<<endl<<endl;
    }
  //  free(p);
    if(myqueue.front().charClass==idt)
    {
         token.pop();
         if(token.front()==assigopt)
         {
             string code;
             code.append(myqueue.front().lexeme);
             code.append(" := ");
             code.append("_Bp + ");
             int m=offset;
             string s;
             ostringstream convert;
             convert << m;
             s = convert.str();
             code.append(s);
             tac.push(code);
             code="";
             code.append("_Bp+ ");
             offset=offset+2;
             string s1;
             ostringstream convert1;
             convert1<< m;
             s1= convert1.str();
             code.append(s1);
             code.append(":=");
             match(idt);
             match(assigopt);
             Expr(code);
         }
         else if(token.front()==lbrackett)
         {
             ProCall();

         }
        /* match(idt);
         if(myqueue.front().charClass==assigopt)
         {
             match(assigopt);
             Expr();
         }
         if(myqueue.front().charClass==lbrackett)
         {
             match(lbrackett);
             Params();
             match(rbrackett);
         }*/
     }
    return;
}

 void Parser::IOStat()
 {
     return;
 }

 void Parser::Expr(string &code)
 {
     Relation(code);
     code.append(code);
   //tac.push(code);
 }

 void Parser::Relation(string &code)
 {
     SimpleExpr(code);
  // tac.push(code);
 }

 void Parser::SimpleExpr(string &code)
 {
     Term(code);
     MoreTerm(code);
   //tac.push(code);
 }

 void Parser::Term(string &code)
 {
     Factor(code);
     MoreFactor(code);
  // tac.push(code);
 }

 void Parser::MoreTerm(string&code)
 {
     if(myqueue.front().charClass==addopt)
     {
         Addop(code);
         Term(code);
         MoreTerm(code);
      // tac.push(code);
     }
     return;
 }

 void Parser::MoreFactor(string&code)
 {
     if(myqueue.front().charClass==mulopt)
     {
         Mulop(code);
         Factor(code);
         MoreFactor(code);
      // tac.push(code);
     }
     return;
 }


 void Parser::Factor(string &code)
 {
     if(myqueue.front().charClass==idt)
     {
          EntryPtr p;
          p=T.Lookup(myqueue.front().lexeme);
          int m1=p->Type.var.Offset;
          int i=0;
          if(p!=NULL)
          {
              while(p->TypeOfEntry!=varEntry&&!p)
              {
                  p=p->next;
              }
          }

          if(p==NULL)
          {
              cout<<"the lexeme "<<myqueue.front().lexeme<<" in line "<<line.front()<<" is undeclared!"<<endl<<endl;
          }
          else
            cout<<"the lexeme "<<myqueue.front().lexeme<<" in line "<<line.front()<<" is declared!"<<endl<<endl;

             code.append("_Bp + ");
             int m=offset;
             //int m1=p->Type.var.Offset;
             string s;
             ostringstream convert;
             convert << m;
             s = convert.str();
             code.append(s);
         //  tac.push(code);
          match(idt);
     }
     if(myqueue.front().charClass==numt)
     {
         code.append(myqueue.front().lexeme);
         match(numt);
      // tac.push(code);
     }
     if(myqueue.front().charClass==lbrackett)
     {
         code.append(myqueue.front().lexeme);
         match(lbrackett);
         Expr(code);
         match(rbrackett);
         code.append(myqueue.front().lexeme);
      // tac.push(code);

     }
     if(myqueue.front().lexeme=="not")
     {
         code.append(myqueue.front().lexeme);
         myqueue.pop();
         Factor(code);
      // tac.push(code);
     }
     if(myqueue.front().lexeme=="-")
     {
         SignOp(code);
         Factor(code);
     //  tac.push(code);
     }
 }

 void Parser::Addop(string&code)
{
    code.append(myqueue.front().lexeme);
    match(addopt);
  //tac.push(code);
}

void Parser::Mulop(string&code)
{
    code.append(myqueue.front().lexeme);
    match(mulopt);
  //tac.push(code);
}

void Parser::SignOp(string&code)
{
    if(myqueue.front().lexeme=="-")
     {
         code.append(myqueue.front().lexeme);
         myqueue.pop();
      // tac.push(code);
     }
     else
     {
         cout<<"parser error!! Expected -"<<endl;
     }
}

void Parser::ProCall()
{
    string code;
    code.append("Call Proc ");
    code.append(myqueue.front().lexeme);
    tac.push(code);
    EntryPtr p;
    p=T.Lookup(myqueue.front().lexeme);
    int i=0;
    if(p!=NULL)
    {
        while(p->TypeOfEntry!=varEntry&&!p)
        {
            p=p->next;
            i++;
        }
    }
    if(p==NULL)
    {
        cout<<"the lexeme "<<myqueue.front().lexeme<<" in line "<<line.front()<<" is undeclared!"<<endl<<endl;
    }
    else
        cout<<"the lexeme "<<myqueue.front().lexeme<<" in line "<<line.front()<<" is declared!"<<endl<<endl;

    match(idt);
    match(lbrackett);
    Params();
    match(rbrackett);
}

void Parser::Params()// ->idt ParamsTail |  num ParamsTail| e
{
    if(myqueue.front().charClass==idt)
    {
        string code;
        code.append("push ");
        code.append(myqueue.front().lexeme);
        tac.push(code);

        match(idt);
        ParamsTail();
    }
    else if(myqueue.front().charClass==numt)
    {
        match(numt);
        ParamsTail();
    }
    return;
}

void Parser::ParamsTail()//ParamsTail		->	, idt ParamsTail |, num ParamsTail |e
{
    if(token.front()==commat)
    {
        token.pop();
        if(token.front()==idt)
        {
            match(commat);
            string code;
            code.append("push ");
            code.append(myqueue.front().lexeme);
            tac.push(code);

            match(idt);
            ParamsTail();
        }
        else if(token.front()==numt)
        {
            match(commat);
            match(numt);
            ParamsTail();
        }
        else
            cout<<"parser error!"<<endl;
    }
    return;
}

