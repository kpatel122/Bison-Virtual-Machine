#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <vector>
#include "symbol.h"

CSymbolTable::CSymbolTable()
{
	numSymbols = 0;
}
CSymbolTable::~CSymbolTable()
{
}

Symbol *CSymbolTable::GetSymbolByIndex(int i)
{
	if ((i<0) || (i>= symbols.size() ) )
		return NULL;

	return symbols[i];
}

Symbol *CSymbolTable::GetSymbolByName(char *name, int func)
{
	for (int i=0; i<numSymbols;i++)
	{
		if(strcmp(symbols[i]->name,name) == 0)
		{
			if((func == symbols[i]->funcIndex) || (symbols[i]->funcIndex ==-1))
			{
				return symbols[i];
			}
		}
	}

	return NULL;
}

int CSymbolTable::AddSymbol(char *name,int funcIndex,int stackIndex,int size)
{
	
	Symbol *t;
	 t = GetSymbolByName(name,funcIndex);
	
	
	if(t!=NULL)
	{
		if(funcIndex == t->funcIndex)
			return -1;
	}
	

		Symbol *s = (Symbol*)malloc(sizeof(Symbol));
		
		if(!s)
			return -1;

		s->funcIndex = funcIndex;
		s->size = size;
		s->stackIndex = stackIndex;
		strcpy(s->name,name);

		symbols.push_back(s);
	

		numSymbols++;

		return 1;

}