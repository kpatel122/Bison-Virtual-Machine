#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <vector>
#include "functions.h"

CFuncTable::CFuncTable()
{
	funcCounter= 0;
	
}

CFuncTable::~CFuncTable()
{
	
}



Func * CFuncTable::GetFuncByName(char *name)
{
	for(int i=0;i<funcCounter;i++)
	{
		if(strcmp(func[i]->name,name) == 0)
			return func[i];
	}

	return NULL;
}

Func *CFuncTable::GetFuncByIndex(int index)
{
	if(index>=func.size())
	{
		return NULL;
	}
	return func[index];
}

int CFuncTable::AddFunc(char *name)
{
	if((strlen(name)) >= MAX_FUNCTION_NAME)
		return -1;
	
	if(GetFuncByName(name)!=NULL)
		return -1;

	Func *f = (Func*)malloc(sizeof(Func));

	if(!f)
		return -1;

	strcpy(f->name,name);
	
	f->entryIndex = -1;
	f->numLocalVar = f->numParams = f->stackSize = 0;

	func.push_back(f);

	return funcCounter++;

}

void CFuncTable::SetEntryPoint(int funcIndex,int entryPoint)
{
	Func *f = func[funcIndex];
	f->entryIndex = entryPoint;
}

void CFuncTable::SetFuncInfo(int funcIndex,int numLocal, int numParams)
{
	Func *f = func[funcIndex];
	f->numLocalVar = numLocal;
	f->numParams = numParams;
	f->stackSize = numLocal * numParams;

}