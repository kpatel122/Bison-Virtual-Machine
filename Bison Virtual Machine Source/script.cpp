#include <iostream.h>
#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>


#include "token.h"
#include "instructions.h"

#include "log.h"
#include "String.h"

#include "functions.h"
#include "symbol.h"
#include "strings.h"
#include "label.h"
#include "script.h"




int CScriptLoader::InitLogFile(CLog *l)
{
	log = l;
	return 1;
}

int CScriptLoader::InitLogFile(char *f)
{
	log = new CLog;
	log->Init(f);

	if(!log)
		return -1;

	return 1;
}


void CScriptLoader::PrintStats()
{
	

	
char buffer[80];
//	sprintf(buffer,"\nnumber strings : %d\n",numStrings);
//	PRINT(buffer);

	sprintf(buffer,"number api callsd : %d\n",numAPICalls);
	PRINT(buffer);
	
	sprintf(buffer,"number functions : %d\n",numFunc);
	PRINT(buffer);
	
	sprintf(buffer,"number line lables : %d\n",numLineLable);
	PRINT(buffer);

	sprintf(buffer,"number symbols : %d\n",numSymbols);
	PRINT(buffer);
	
	sprintf(buffer,"number instruction : %d\n",numInstr);
	PRINT(buffer);
		
	/*
	sprintf(buffer,"number Global vars : %d\n",globalSize);
	PRINT(buffer);
	
	sprintf(buffer,"is main present : %d\n",isMainDefined);
	PRINT(buffer);
	*/
}

int CScriptLoader::ReadStringTable()
{
	char *str;
	std::vector<char*> vstr = script->stringTable.GetStringStream();

	for(int i=0;i<numStrings;i++)
	{
		

		
		int len;
		fread(&len,sizeof(int),1,f);
		str = (char*)malloc(len * sizeof(char));
		fread(str,sizeof(char),len,f);
		
	
		str[len] = '\0';
		script->stringTable.AddString(str);
	}

	return 1;

}

int CScriptLoader::ReadAPITable()
{
	char *apiFunc;
	std::vector<char*> vapi = script->apiFuncTable.GetStringStream();

	for(int i=0;i<numAPICalls;i++)
	{
		

		if(!apiFunc)
		{
			Error("Invalid function index")
		}
		int len;
		fread(&len,sizeof(int),1,f);
		apiFunc = (char*)malloc(len * sizeof(char));
		fread(apiFunc,sizeof(char),len,f);
		
		apiFunc[len] ='\0';
		script->apiFuncTable.AddString(apiFunc);
	}

	return 1;
}
int CScriptLoader::ReadFuncTable()
{
	Func *pf = (Func*)malloc(sizeof(Func) * numFunc);
	
 
	std::vector<Func*> &func = script->funcTable.GetFuncStream();
	for(int i=0;i<numFunc;i++)
	{
	
		fread(&pf[i].entryIndex,sizeof(int),1,f);
		fread(&pf[i].numLocalVar,sizeof(int),1,f);
		fread(&pf[i].numParams,sizeof(int),1,f);
		fread(&pf[i].stackSize,sizeof(int),1,f);
		
		func.push_back(&pf[i]);
	}

	return 1;
}
int CScriptLoader::ReadHeader()
{
	BASM_Header header;
	
	fread(&header,sizeof(BASM_Header),1,f);

	numAPICalls = header.numAPICalls;
	numStrings =  header.numStrings;
	numFunc = header.numFunc;
	numLineLable= header.numLineLable;
	numSymbols = header.numSymbols;
	numInstr = header.numInstr;
	script->mainIndex =header.main;;
	script->globalSize = header.globalSize;
	script->stackSize = header.stackSize;

	return 1;
}
int CScriptLoader::ReadInstructions()
{
	Instr *pinstr =new Instr[numInstr];

	for(int i=0;i<numInstr;i++)
	{
			


	fread(&pinstr[i].opCode,sizeof(int),1,f);
	fread(&pinstr[i].numberParams,sizeof(int),1,f);
	

	pinstr[i].opList = (Operand*)malloc(sizeof(Operand) * pinstr->numberParams);
	
		


		for(int j=0; j<pinstr[i].numberParams;j++)
		{
			
			fread(&pinstr[i].opList[j].type,sizeof(int),1,f);
			int t;
			t = pinstr[i].opList[j].type;
		
			switch(t)
			{
			case OP_TYPE_INT:
				{
					fread(&pinstr[i].opList[j].Int,sizeof(int),1,f);
				}break;
			case OP_TYPE_FLOAT:
				{
					fread(&pinstr[i].opList[j].Float,sizeof(float),1,f);
				}break;
			case OP_TYPE_STRING_INDEX:
				{
					fread(&pinstr[i].opList[j].stringTableIndex,sizeof(int),1,f);
				}break;
			case OP_TYPE_REL_STACK_INDEX:
				{
					fread(&pinstr[i].opList[j].stackIndex,sizeof(int),1,f);
					fread(&pinstr[i].opList[j].OffsetIndex,sizeof(int),1,f);
				}break;
			case OP_TYPE_ABS_STACK_INDEX:
				{
					fread(&pinstr[i].opList[j].stackIndex,sizeof(int),1,f);
				}break;
			case OP_TYPE_FUNC_INDEX:
				{
					fread(&pinstr[i].opList[j].funcIndex,sizeof(int),1,f);
				}break;
			case OP_TYPE_HOST_API_CALL_INDEX:
				{
					fread(&pinstr[i].opList[j].hostAPICallIndex,sizeof(int),1,f);
				}break;
			case OP_TYPE_REG :
				{
					fread(&pinstr[i].opList[j].Reg,sizeof(int),1,f);
				}break;
			
			default:
				{
					int c = pinstr[i].opList[j].type;
						cout<<"Unkown op type: "<<c<<endl;
						Error(c);
				//	cout<<"Unkown op type: "<<pinstr->opList[j].type<<endl;
				//		Error(pinstr[i].opList[j].type);
				}break;

			}
		}
		
	script->instrStream.push_back(&pinstr[i]);	
		
	}
	return 1;
}
int CScriptLoader::ReadLabelTable()
{
	Label *label;
	label = (Label*)malloc(numLineLable * sizeof(Label));
	std::vector <Label*> &vlabel = script->labelTable.GetLabelStream(); 

	for(int i=0;i<numLineLable;i++)
	{
	
		fread(&label[i].funcIndex,sizeof(int),1,f);
		fread(&label[i].instrIndex,sizeof(int),1,f);
		
		vlabel.push_back(&label[i]);
	}
	return 1;
	
}

int CScriptLoader::ReadSymbolTable()
{
	Symbol  *symbol = (Symbol*)malloc(numSymbols * sizeof(Symbol));
	std::vector<Symbol*>&vsymbol = script->symbolTable.GetSymbolStream();
	
	for(int i=0;i<numSymbols;i++)
	{
		fread(&symbol[i].funcIndex,sizeof(int),1,f);
		fread(&symbol[i].size,sizeof(int),1,f);
		fread(&symbol[i].stackIndex,sizeof(int),1,f);

		vsymbol.push_back(&symbol[i]);
	}
	return 1;
}


int CScriptLoader::ReadASMFile(char *filename)
{

	
	f = fopen(filename,"rb");

	if(!f)
	{
		Error("Could not open file");
	}


	script = new Script;
	

ReadHeader();
ReadInstructions();
ReadFuncTable();
ReadLabelTable();
ReadSymbolTable();
ReadStringTable();
ReadAPITable();
	
	//int t;
	//fread(&t,sizeof(int),1,f);
	
	//std::vector<Func*>& funcVec = script->funcTable.GetFuncStream();



	
	
	
	

	/*

	Symbol * symbol;
	
	for(i=0;i<script.symbolTable.GetNumSymbols();i++)
	{
		symbol = script.symbolTable.GetSymbolByIndex(i);

		if(!func)
		{
			Error("Invalid function index")
		}

		fread(&symbol,sizeof(Symbol),1,f);
	}
	
	Label *label;
	
	for(i=0;i<script.labelTable.GetNumberLabels();i++)
	{
		label = script.labelTable.GetLabelByIndex(i);

		if(!label)
		{
			Error("Invalid function index")
		}

		fwrite(&label,sizeof(Label),1,f);
	}
	
	char *str;

	for(i=0;i<script.stringTable.GetNumberStrings();i++)
	{
		str = script.stringTable.GetStringByIndex(i);

		if(!str)
		{
			Error("Invalid function index")
		}

		fwrite(&str,sizeof(char),strlen(str),f);
	}

	char *apiFunc;

	for(i=0;i<script.apiFuncTable.GetNumberStrings();i++)
	{
		apiFunc = script.apiFuncTable.GetStringByIndex(i);

		if(!apiFunc)
		{
			Error("Invalid function index")
		}

		fwrite(&apiFunc,sizeof(char),strlen(apiFunc),f);
	}


	PRINT("File Read suceesfuly!\n");
	*/
	return 1;
}