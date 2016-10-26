#include "LexicalAnalyzer.h"
#include "TableEntry.h"
#include <string>
#include <streambuf>
#include <iostream>
#include <stdlib.h>
#include <cstring>

//using namespace std;

SymbolTable::SymbolTable()
{//initialzation empty Table
	int i=0;//used to loop the table
	while (i<PRIME){
		Table[i]=NULL;
		i++;
	}
}

int SymbolTable::hash(OneString str)
{
	    int sum=0;
	    int m=strlen(str);
	    for(int i=0;i<m;i++)
        {
            sum+=(int)str[i];
        }
		return sum % PRIME;
}

int SymbolTable::Insert(OneString lexeme, tokenType token, int depth)
{

	int addr = hash(lexeme);
	EntryPtr p=new TableEntry;
	p->Lexeme=lexeme;
	p->Token=token;
	p->depth=depth;
	p->next=Table[addr];//point entry to the address Table[location] previously pointed
	Table[addr]=p;
	return 0;
}

EntryPtr SymbolTable::Lookup(OneString lexeme)
{
	int addr = hash(lexeme);
	EntryPtr p;
	p=Table[addr];
	while (p!=NULL)
    {
		if(p->Lexeme==lexeme)
		{
			return p;//return the current pointer
		}
		p=p->next;
	}
	cout<<"after searching the whole symbol table,No such Lexeme: "<<lexeme<<endl;
	p=NULL;//return the pointer to NULL
	return p;//when the lexeme is not in the table
}

int SymbolTable::WriteTable(int depth)
{
	EntryPtr p;
	int i=0;
	bool found=false;
	while (i<PRIME)
    {
		p=Table[i];
		while (p!=NULL)//look through the chain
		{
			if (p->depth==depth)
			{
				found=true;//one entry is found and displayed
				cout<<"In depth "<<depth<<" have lexeme "<<p->Lexeme<<"  ";
				switch (p->TypeOfEntry)
				{
				    case constEntry:
                    {
                        cout<<" in constantEntry"<<endl;
                        break;
                    }
				    case varEntry:
                    {
                        cout<<" in variableEntry"<<endl;
					    //cout<<p->Type.var.Offset<<endl;
                        break;
                    }
                    case functionEntry:
                    {
                        cout<<" in functionEntry"<<endl;
                        break;
                    }
				}
			}
			p=p->next;
		}
		i++;
	}
	if (found==false)
    {//if no symbol is displayed until the end of the table
		cout<<"Error!!! No lexeme in depth "<<depth<<endl;
		return 1;
	}
	return 0;
}

int SymbolTable::DeleteDepth(int depth)
{
	bool chain=false;//whether location of the entry to be deleted in the chain
	bool dele=false;//whether at least one entry deleted
	bool last=false;//whether reach the end of the chain
	EntryPtr p;
	EntryPtr pre;
    int i=0;
	while (i<PRIME)
    {
		if (Table[i]!=NULL)
		{
			p=Table[i];
			chain=false;//reset after loop each time
			last=false;
			while ((p->depth!=depth))
			{
				pre=p;	//pre is pointed the previous node
				p=p->next;
				if (p==NULL)
                {
					last=true;
					break;
				}
				chain=true;//have entered lexeme in the chain
			}

			if (last){}//check the next chain
			else if (!chain)
            {//if this is the first entry in the chain
				Table[i]=p->next;
				free(p);
				dele=true;//one entry is deleted
			}
			else if (chain)
            {//the entry is in the middle of the chain
				pre->next=p->next;// delete the entry
				delete p;
				dele=1;//one entry is deleted
			}
		}
		i++;
	}
	if (!dele)
    {//if no entry is deleted until the end of the table
		cout<<"Error!!!No lexeme in depth: "<<depth<<endl;
		return 1;
	}
	return 0;
}
/*
int main(int argc, char *argv[])
{
	//test
	SymbolTable T;
	//inset
	OneString text1="adsdadffdafa";
	OneString text2="ad";
	T.Insert(text1,idt,1);
	T.Insert(text1,idt,2);
	T.Insert(text2,constt,2);
	T.Insert(text2,constt,3);
	//look up
	EntryPtr p;
	EntryPtr p2;
	p=T.Lookup(text1);
	p2=T.Lookup(text2);
	p->TypeOfEntry=varEntry;
	p->Type.var.TypeOfVariable=charType;
	p2->TypeOfEntry=functionEntry;
	p2->Type.function.ParamList=new ParamNode;
	p2->Type.function.ParamList->typeOfParameter=floatType;
	//write
	T.WriteTable(1);
	T.WriteTable(2);
	T.WriteTable(3);
	//delete
	//T.DeleteDepth(1);
	T.DeleteDepth(2);
	T.DeleteDepth(3);
	//look up after delete
	p=T.Lookup(text1);
	p2=T.Lookup(text2);
	//write after delete
	T.WriteTable(1);
	T.WriteTable(2);
	T.WriteTable(3);
	//system("pause");
	return 0;
}
*/
