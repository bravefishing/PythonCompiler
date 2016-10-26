#ifndef TABLEENTRY_H_INCLUDED
#define TABLEENTRY_H_INCLUDED
#include <string>
const int TableSize = 211; //use a prime number
typedef char OneString[81];
#define PRIME 211

enum VarType {charType, intType, floatType };

enum EntryType {constEntry, varEntry, functionEntry};

struct ParamNode;

typedef ParamNode * ParamPtr;

struct ParamNode {
  VarType typeOfParameter;
  ParamPtr Next;
};

struct TableEntry;

typedef TableEntry * EntryPtr; //pointer to actual table entry

struct TableEntry {
  tokenType Token;
  string Lexeme;
  int depth;
  EntryType TypeOfEntry; // tag field for the union
  union {
    struct {
      VarType TypeOfVariable;
      int Offset;
      int size;
    } var;
    struct {
      VarType TypeOfConstant; //int or float constant
      int Offset;
      union {
        int Value;
        float ValueR;
      };
    } constant;
    struct { //this is the entry for a function
      int SizeOfLocal;
      int NumberOfParameters;
      VarType ReturnType;
      ParamPtr ParamList; //linked list of paramter types
    } function;
  }Type; //end of union
 EntryPtr next; //points to next list item
};


class SymbolTable{
private:
	int hash(OneString str);
public:
	EntryPtr Table [PRIME];//declare an array with 211 EntryPtr pointers
	SymbolTable();//construction function
	int Insert(OneString lexeme, tokenType token, int depth);
	EntryPtr Lookup(OneString lexeme);
	int DeleteDepth(int depth);
	int WriteTable(int depth);
};

#endif // TABLEENTRY_H_INCLUDED
