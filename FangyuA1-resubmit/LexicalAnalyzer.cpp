/********************************************************************
 ***  NAME  :Fangyu Zhang                                         ***
 ***  CLASS  :  CSc 446                                          ***
 ***  ASSIGNMENT : Assignment #1                                  ***
 ***  DUE DATE :  02/11/2014                                      ***
 ***  INSTRUCTOR :  Hammer                                       ***
 ********************************************************************
 ***  DESCRIPTION : This program implemente all the the members   ***
 ***  the lexical Analyzer need include constructor,destructor ,and *
****  lex funxtion to get all the tokens  **************************
 ****  **********************************
 *******************************************************************/


#include"LexicalAnalyzer.h"
#include <cstdlib>
#include<cstring>//  C style strings
#include<string>
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
LexicalAnalyzer::LexicalAnalyzer(OneString in):charClass(unknownt)
{
    strcpy(lexeme,"");
    strcpy(input,in);
}

LexicalAnalyzer::~LexicalAnalyzer(){}
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
int LexicalAnalyzer::lex(OneString largeString,int&next,OneString smallString,int&plNum,int&prNum)//smallString will be such as name, wins, OTL
{
    int pos=0;//next for large string and pos for small string
    while(largeString[next]==' ')
    {
        next++;//p is the position for the large string
    }

    if(largeString[next]=='=')
    {
        smallString[pos]=largeString[next];
        charClass=relopt;
        next++;
        smallString[pos+1]='\0';
        return charClass;
    }
    else if(largeString[next]=='(')
    {
        smallString[pos]=largeString[next];
        charClass=lparent;
        next++;
        return charClass;
    }

    else if(largeString[next]==')')
    {
        smallString[pos]=largeString[next];
        charClass=rparent;
        next++;
        return charClass;
    }

    else if(largeString[next]==';')
    {
        smallString[pos]=largeString[next];
        charClass=semicolont;
        next++;
        return charClass;
    }

    else if(largeString[next]=='.')
    {
        smallString[pos]=largeString[next];
        charClass=periodt;
        next++;
        return charClass;
    }

    else if(largeString[next]==',')
    {
        smallString[pos]=largeString[next];
        charClass=commat;
        next++;
        return charClass;
    }


    else if(largeString[next]=='+'||largeString[next]=='-')
    {
        smallString[pos]=largeString[next];
        next++;
        charClass=addopt;
        return charClass;
    }

    else if(largeString[next]=='*'||largeString[next]=='/')
    {
        smallString[pos]=largeString[next];
        charClass=mulopt;
        next++;
        return charClass;
    }

    else if(largeString[next]=='{')
        {
            smallString[pos]=largeString[next];
            charClass=lbracet;
            next++;
            plNum++;
            return charClass;
        }
    else if(largeString[next]=='}')
    {
        smallString[pos]=largeString[next];
        charClass=rbracet;
        next++;
        prNum++;
        smallString[pos+1]='\0';
        return charClass;
    }
    else if(largeString[next]=='~')
    {
        smallString[pos]=largeString[next];
        charClass=tildet;
        next++;
        smallString[pos+1]='\0';
        return charClass;
    }
    else if(largeString[next]=='\'')
    {
            do{
                smallString[pos]=largeString[next];
                pos++;
                next++;
            }while(largeString[next]!='\''&&pos<LINE_SIZE+1);


           /* smallString[pos]='\'';
            pos++;
            next++;
            if(largeString[next]!='\'')
            {
               do{
                smallString[pos]=largeString[next];
                next++;
                }while(largeString[next]!='\''&&pos<LINE_SIZE+1);
            }*/

            if(largeString[next]=='\'')
            {
                smallString[pos]=largeString[next];
                next++;
                smallString[pos+1]='\0';
                charClass=literalt;
            }
            else
            {
                smallString[LINE_SIZE+1]='\0';
                charClass=unknownt;
            }

            return charClass;
    }

    else if(largeString[next]==':')
    {
        smallString[pos]=largeString[next];
        next++;
        if(largeString[next]=='=')
        {
            pos++;
            smallString[pos]=largeString[next];
            charClass=assigopt;
            next++;
            return charClass;
        }
        else
        {//next--;
            charClass=colont;
            return charClass;
        }
    }

    else if(largeString[next]=='<')
    {
        smallString[pos]=largeString[next];
        next++;
        if(largeString[next]=='='||largeString[next]=='>')
        {
            pos++;
            smallString[pos]=largeString[next];
            charClass=relopt;
            return charClass;
        }
        else
        {
            charClass=relopt;
            return charClass;
        }
    }

    else if(largeString[next]=='>')
    {
        smallString[pos]=largeString[next];
        next++;
        if(largeString[next]=='=')
        {
            pos++;
            smallString[pos]=largeString[next];
            charClass=relopt;
            return charClass;
        }
        else
        {
            //next--;
            charClass=relopt;
            return charClass;
        }
    }

    else if(isalpha(largeString[next]))
    {
        do{
            smallString[pos]=largeString[next];
            next++;
            pos++;
        }while(isdigit(largeString[next])||isalpha(largeString[next]));

        smallString[pos] = '\0';
        //cout<<"smallString:"<<smallString<<"size"<<strlen(smallString)<<endl;
        if(strlen(smallString)>15)
        {
            charClass=unknownt;
            cout<<"this token is oversized!!! the length should be at most 15 characters."<<endl;
        }
        else
           charClass=idt;

        //the following is to check if the string is reserved or not.
        int m=0;
        OneString a[18]={"PROGRAM","PROCEDURE","FUNCTION","VAR","BEGIN","END","IF","THEN","ELSE","WHILE","DO","REAL","INTEGER","CHAR","OR","DIV","MOD","AND"};
        for(int i=0;i<18;i++)
        {
         //   if(isEqual(smallString,a[i])==1)
            if(strlen(smallString)==strlen(a[i]))
            {
                int j=0;
                while((smallString[j]==a[i][j]||smallString[j]==char((int)a[i][j]+32))&&j<strlen(a[i]))
                {
                    j++;
                }
                if(j==strlen(a[i]))
                {
                    //for reserved word
                    if(i==0)
                    {
                        charClass=programt;
                        return charClass;
                    }
                    if(i==1)
                    {
                        charClass=proceduret;
                        return charClass;
                    }
                    if(i==2)
                    {
                        charClass=functiont;
                        return charClass;
                    }
                    if(i==3)
                    {
                        charClass=vart;
                        return charClass;
                    }
                     if(i==4)
                    {
                        charClass=begint;
                        return charClass;
                    }
                     if(i==5)
                    {
                        charClass=endt;
                        return charClass;
                    }
                     if(i==6)
                    {
                        charClass=ift;
                        return charClass;
                    }
                     if(i==7)
                    {
                        charClass=thent;
                        return charClass;
                    }
                     if(i==8)
                    {
                        charClass=elset;
                        return charClass;
                    }
                     if(i==9)
                    {
                        charClass=whilet;
                        return charClass;
                    }
                     if(i==10)
                    {
                        charClass=dot;
                        return charClass;
                    }
                     if(i==11)
                    {
                        charClass=realt;
                        return charClass;
                    }
                     if(i==12)
                    {
                        charClass=integert;
                        return charClass;
                    }
                     if(i==13)
                    {
                        charClass=chart;
                        return charClass;
                    }// //OR,DIV,MOD,AND
                     if(i==14)
                    {
                        charClass=addopt;
                        return charClass;
                    }
                     if(i==15||i==16||i==17)
                    {
                        charClass=relopt;
                        return charClass;
                    }
                }
            }
        }
        return charClass;
    }

    else if(isdigit(largeString[next]))
    {
        do{
            smallString[pos]=largeString[next];
            next++;
            pos++;
        }while(isdigit(largeString[next]));

        if(largeString[next]=='.'&&isdigit(largeString[next+1]))
        {
            smallString[pos]=largeString[next];
            next++;
            pos++;
            do{
                smallString[pos]=largeString[next];
                next++;
                pos++;
            }while(isdigit(largeString[next]));

            charClass=numt;//REAL
            smallString[pos] = '\0';
            return charClass;
        }
        else
        {
            charClass=numt;//INTEGER
            smallString[pos] = '\0';
            return charClass;
        }
    }
    else
    {
        while(largeString[next]!=' '&&largeString[next]!='\0')
        {
           smallString[pos] = largeString[next];//add the current character in the large string to the small string
           next++;
           pos++;
        }
      //  charClass=unknownt;
        smallString[pos] = '\0';
        return charClass;
    }
    smallString[pos] = '\0';//to avoid of useless value À¬»øÊý¾Ý need a terminat

    if(strlen(smallString)==0)
    {
        smallString[pos] = '\0';
        charClass=eoft;
    }
}
