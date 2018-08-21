#include <iostream.h>
#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
#include "token.h"
#include "instructions.h"

#include "log.h"
#include "String.h"

#include "functions.h"
#include "symbol.h"
#include "strings.h"
#include "label.h"
#include "script.h"
#include "stack.h"
*/
#include "vm.h"

Value *gStack;
int *gStackSize;

int CVM::GetNextInstr()
{
	if(instrIndex>= (numInstr))
		return -1;
	currInstr = script->instrStream[instrIndex];

	return instrIndex++;

}

int CVM::GetStackIndex(int index)
{
	Operand *op = &currInstr->opList[index];
	
	
	switch(op->type)
	{
		
			case OP_TYPE_REL_STACK_INDEX:
				{
					
					Value tempVal;
					int sindex= op->OffsetIndex;
					tempVal = stack.GetAtIndex(sindex);
					
					if(tempVal.type!=OP_TYPE_INT)
					{
						//ConvertToInt(tempVal);
					}

					int offset = op->stackIndex + tempVal.Int;
					return offset;
				}break;
			case OP_TYPE_ABS_STACK_INDEX:
				{
					return op->stackIndex;
					
				}break;
			
			
	}
}

Value CVM::ResolveOP(int index)
{
	Operand *op = &currInstr->opList[index];
	
	Value val;
	val.type = op->type;

	switch(op->type)
	{
		   case OP_TYPE_INT:
				{
					val.Int = op->Int;
					
				}break;
			case OP_TYPE_FLOAT:
				{
					val.Float = op->Float;
				}break;
			case OP_TYPE_STRING_INDEX:
				{
					int sindex = op->stringTableIndex;
					val.string = script->stringTable.GetStringByIndex(sindex);

				}break;
			case OP_TYPE_REL_STACK_INDEX:
				{
					Value tempVal;
					int sindex= op->OffsetIndex;
					tempVal = stack.GetAtIndex(sindex);
					
					if(tempVal.type!=OP_TYPE_INT)
					{
						//ConvertToInt(tempVal);
					}

					int offset = op->stackIndex + tempVal.Int;

					val = stack.GetAtIndex(offset);

				}break;
			case OP_TYPE_ABS_STACK_INDEX:
				{
					int sindex= op->stackIndex;
					return stack.GetAtIndex(sindex);
				
				}break;
			case OP_TYPE_FUNC_INDEX:
				{
					val.funcIndex = op->funcIndex;
				}break;
			case OP_TYPE_HOST_API_CALL_INDEX:
				{
					int sindex = op->hostAPICallIndex;
					val.string = script->apiFuncTable.GetStringByIndex(sindex);

				}break;
			case OP_TYPE_REG :
				{
				//	fwrite(&instr->opList[j].Reg,sizeof(int),1,f);
				}break;
	}

	return val;
}

int CVM::ExecADD()
{
	gStack = stack.GetStack(); 
	Value val;
	int stackIndex;
	
	stackIndex = GetStackIndex(0);
	val = ResolveOP(1);
	Value source = stack.GetAtIndex(stackIndex);

	
		switch(source.type)
		{
			case OP_TYPE_INT:
				{
					if(val.type == OP_TYPE_FLOAT)
					{
						source.Int +=(int)val.Float;
					}
					else
					{
						source.Int +=(int)val.Int;
					}

					
				}break;
			case OP_TYPE_FLOAT:
				{
					if(val.type == OP_TYPE_INT)
					{
							source.Float +=(float)val.Int;
					}
					else
					{
						source.Float +=(int)val.Float;
					}

				}break;

		}
	


	stack.SetAtIndex(stackIndex,source);
	return 1;
}

int CVM::ExecPush()
{
	Value val;
	val = ResolveOP(0);
	stack.push(val);

	return 1;

}


int CVM::ExecPop()
{

	Value val;
	int stackIndex;
	stackIndex = GetStackIndex(0);
	val = stack.pop();
	stack.SetAtIndex(stackIndex,val);
	
	return 1 ;
}

int CVM::ExecRET()
{
	Value val;
	val= stack.pop();
	int funcIndex ;
	
	funcIndex = val.Int;

	currFunc = script->funcTable.GetFuncByIndex(funcIndex);

	ClearStack(currFunc->numLocalVar);
	
	val = stack.pop();
	instrIndex = val.Int;


	ClearStack(currFunc->numParams);

	



return 1;
}

int CVM::ExecCALL()
{
	Operand *op = &currInstr->opList[0];
	currFunc  = script->funcTable.GetFuncByIndex(op->funcIndex);
	


	Value ret;
	ret.Int = (instrIndex );
	stack.push(ret);
	SetUpStack(currFunc->numLocalVar);
	Value val;
	val.funcIndex = op->funcIndex;
	stack.push(val);
	

	
	instrIndex = currFunc->entryIndex;
	

	return 1;
}


int CVM::ExecMOV()
{
	Value val;
	int stackIndex;
	stackIndex = GetStackIndex(0);
	val = ResolveOP(1);
	stack.SetAtIndex(stackIndex,val);
	
	return 1;
}


void CVM::SetUpStack(int num)
{
	Value v;


	for(int i=0;i<num;i++)
	{
		
		
			stack.push(v);
		
	}
}

void CVM::ClearStack(int num)
{



	for(int i=0;i<num;i++)
	{
		
		
			stack.pop();
		
	}
}
int CVM::RegisterHost(char *name,void *func,int args)
{


	
	HOST_API *h = (HOST_API*)malloc(sizeof(HOST_API));
	 
	
	h->func = (fptralias)func;;
	strcpy(h->name,name);
	h->numArg= args;
	host.push_back(h);

	char *r;
	
	HOST_API*e;
	for(int i=0;i<host.size();i++)
	{
		e = host[i];
		r = e->name;
	}

	return 1;
}

int CVM::ExecCALLHOST()
{
	Value val;
	val = ResolveOP(0);

	bool found =0;
	int numArg =0;

	
	HOST_API* h;
char *test; 

	for(int j=0;j<host.size();j++)
	{
		h = host[j];
		if(strcmp(h->name,val.string)==0)
		{
			found = 1;
			break;
		}
	}

	if(!found)
		return -1;
	
	HOST_API* f;
	f = GetHost(j);
	
	fptralias pfunc = (fptralias)f->func;
	numArg = f->numArg;

	int psize = sizeof(val);
	int buff = numArg * psize;

	int i = numArg;

while(i>0)
{
	_asm{
		mov eax,buff
		sub eax,psize
		mov buff,eax
		push eax
		}
		
	
	

	val = stack.pop();
		
	switch(val.type)
	{
		   case OP_TYPE_INT:
				{
					_asm  pop eax
					_asm  mov ecx, val[eax].Int;
					
				}break;
			
			case OP_TYPE_STRING_INDEX:
				{
					_asm  pop eax	
					_asm  mov ecx, val[eax].string

				}break;
		
			
	}
	

	
	
		_asm
		{
			push ecx
			dec i
		}
	
}


_asm
{

call [pfunc]

mov eax, numArg
mov ebx, 4
mul ebx

add  esp,eax
}

	return 1;
}

HOST_API* CVM:: GetHost(int i)
{
	return host[i];
}


int CVM::RunScript()
{
    gStack = stack.GetStack();
	gStackSize = stack.sizep();
	if(script->mainIndex!=-1)
	{
		Func *main = script->funcTable.GetFuncByIndex(script->mainIndex);
		instrIndex = main->entryIndex;
		currFunc = script->funcTable.GetFuncByIndex(script->mainIndex);
		varOffset = currFunc->numLocalVar;
		
	}
  SetUpStack(script->globalSize);
  while(GetNextInstr()!=-1)
  {
	
	
	switch(currInstr->opCode)
	{
		case INSTR_MOV:
		{
			ExecMOV();
			PRINT("Instr: Mov");
		}break;

		case INSTR_ADD:
		{
			ExecADD();
			PRINT("Instr: Add");
		}break;

		case INSTR_JMP:
		{
			PRINT("Instr: JMP");
		}break;
		
		
		case INSTR_CALL:
		{
			PRINT("Instr: CALL");
			ExecCALL();
			
		}break;

		
		case INSTR_RET:
		{
			PRINT("Instr: RET");
			ExecRET();
			
		}break;

		case INSTR_CALLHOST:
		{
			ExecCALLHOST();
		//	PRINT("Instr: CALLHOST");
		}break;

	
		case INSTR_PUSH:
		{
			ExecPush();
			PRINT("Instr: PUSH");
		}break;

		case INSTR_POP:
		{
			ExecPop();
			PRINT("Instr: POP");
		}break;
		
		case INSTR_EXIT:
		{
			PRINT("Instr: RET");
			ExecRET();
		}break;

		default:
			{
				Error("Unkown Instr");
			}break;

     }

	PRINT("\n");
  }//end while
return 1;
}
