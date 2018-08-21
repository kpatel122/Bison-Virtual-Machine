#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "token.h"
#include "instructions.h"

CInstrTable::CInstrTable()
{
	currInstr = 0;

}
CInstrTable::~CInstrTable()
{
}

int CInstrTable::AddInstr(char *name,int token,int numParams)
{
	if(strlen(name) >= MAX_INSTR_NAME)
		return -1;

	InstrLookup *func = (InstrLookup*)malloc(sizeof(InstrLookup));
	
	strcpy(func->name,name);
	func->token = token;
	func->numParam = numParams;
	func->opList = (Operand*)malloc((sizeof(Operand)) * numParams);

	instr.push_back(func);


	return currInstr++;

}

void CInstrTable::SetInstrOp(int instrIndex,int opIndex,int values)
{
	InstrLookup* f = instr[instrIndex];
	f->opList[opIndex].type = values;
}

InstrLookup*  CInstrTable::GetInstrByIndex(int index)
{
	
	for (int i=0; i<currInstr;i++)
	{
		if (i == index)
			return instr[i];
	}
	return NULL;
}

InstrLookup*  CInstrTable::GetInstrByName(char *name)
{

	for (int i=0; i<currInstr;i++)
	{
		if (strcmp(instr[i]->name, name) == 0)
			return instr[i];
	}
	return NULL;
}

bool CInstrTable::IsValidInstr(char *name)
{
	char *t;
	for (int i=0; i<currInstr;i++)
	{
		t = instr[i]->name;
		if (strcmp(t, name) == 0)
			return true;
	}
	
	return false;
}