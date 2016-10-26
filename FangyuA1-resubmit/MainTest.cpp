/********************************************************************
 ***  NAME  :Fangyu Zhang                                         ***
 ***  CLASS  :  CSc 446                                          ***
 ***  ASSIGNMENT : Assignment #1                                  ***
 ***  DUE DATE :  02/11/2014                                      ***
 ***  INSTRUCTOR :  Hammer                                       ***
 ********************************************************************
 ***  DESCRIPTION : This program test the the lexical Analyzer by ***
 ***  reading a file,using the lex function will nanlysis and then***
 **   output the tokens encounted and the associated attributes with*
 ***  Display function               ********************************
 *******************************************************************/
#include<iostream>
#include<string>
#include <cstdlib>
#include <fstream> //  file input and output
#include"LexicalAnalyzer.cpp"
#include"LexicalAnalyzer.h"
#include <queue>
#include <iomanip>
using namespace std;

void getFilename(const int argc,const char*argv[],OneString filename);
void init(OneString a);
string convertToken(int t);
queue<LexicalAnalyzer> myqueue;
queue<int> line;
queue<bool>miss;

int main(const int argc,const char*argv[])
{
    cout<<"**********Testing lexical analyzer********"<<endl<<endl;
    OneString filename;
    OneString largeString;//for each line
    OneString smallString;//for each attribution
    int tokenNum=0;
    int next=0;
    int lineNum=1;
    int plNum=0;
    int prNum=0;
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
            //LexicalAnalyzer LA(largeString);
            int token=LA.lex(largeString,next,smallString,plNum,prNum);
            strcpy(LA.lexeme,smallString);
            if((LA.charClass!=lbracet&&LA.charClass!=rbracet)&&plNum<=prNum)
            {
                myqueue.push(LA);
                line.push(lineNum);
            }

           // tokenNum++;
            init(smallString);
            }
            lineNum++;
            next=0;
        }
        LA.charClass=eoft;
        myqueue.push(LA);
        cout<<left<<setw(12)<<"token"<<setw(15)<<"lexeme"<<setw(10)<<"line number"<<endl<<endl;
        while(myqueue.front().charClass!=eoft)
        {
            cout<<convertToken(myqueue.front().charClass)<<"  "<<left<<setw(10)<<myqueue.front().lexeme<<right<<setw(10)<<line.front()<<endl;
            myqueue.pop();
            line.pop();
        }

        cout<<convertToken(eoft)<<endl;
        if(plNum==prNum+1)
        {
            cout<<"missing '}' in this line."<<endl;
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
***     tokens                                                     ***
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
***     tokens                                                     ***
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
string convertToken(int t)
{
    string s;
    switch(t)
    {
        case programt:         s="programt  ";break;
        case proceduret:       s="proceduret";break;
        case functiont:        s="functiont ";break;
        case vart:             s="vart      ";break;
        case begint:           s="begint    ";break;
        case endt:             s="endt      ";break;
        case ift:              s="ift       ";break;
        case thent:            s="thent     ";break;
        case elset:            s="elset     ";break;
        case whilet:           s="whilet    ";break;
        case dot:              s="dot       ";break;
        case realt:            s="realt     ";break;
        case integert:         s="integert  ";break;
        case chart:            s="chart     ";break;
		case addopt:           s="addopt    ";break;
		case mulopt:           s="mulopt    ";break;
		case idt:              s="idt       ";break;
        case numt:             s="numt      ";break;
        case literalt  :       s="literalt  ";break;
		case relopt    :       s="relopt    ";break;
		case assigopt  :       s="assigopt  ";break;
		case lparent   :       s="lparent   ";break;
		case rparent   :       s="rparent   ";break;
		case lbrackett :       s="lbrackett ";break;
		case rbrackett :       s="rbrackett ";break;
		case lbracet   :       s="lbracet   ";break;
		case rbracet   :       s="rbracet   ";break;
		case colont    :       s="colont    ";break;
		case commat    :       s="commat    ";break;
		case semicolont:       s="semicolont";break;
		case tildet    :       s="tildet    ";break;
		case periodt   :       s="periodt   ";break;
		case eoft      :       s="eoft      ";break;
		case unknownt  :       s="unknownt  ";break;
    }
    return s;
}


