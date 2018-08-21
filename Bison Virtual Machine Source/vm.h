#ifndef VM_H
#define VM_H


#include <vector>
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
#include  "hostApi.h"



struct Value
{
	
int type;
	union
	{
     int  Int;                        // Integer literal
     float Float;                    // Float literal
     char *string;                  // String table index
     char *host;
	 int stackIndex;                        // Stack index
     int instrIndex;                        // Instruction index
     int funcIndex;                         // Function index
     int hostAPICallIndex;                  // Host API Call index
     int Reg;                               // Register code
    };
        
};

class CVM
{
public:
	CVM(){numInstr = numErrors = instrIndex =0;}
	~CVM(){}
	CLog *log;
	void InitLogFile(CLog *l){log =l;}
	int instrIndex;
	Instr *currInstr;
	int GetNextInstr();
	Script *script;
	Value ResolveOP(int index);
	CStack<Value> stack;

	std::vector<HOST_API *> host;
	HOST_API * GetHost(int i);
	int RegisterHost(char*name, void *func,int);
	void AssignScript(Script *s){script = s; numInstr = script->instrStream.size();}
	int RunScript();
	int numInstr;
	int numErrors;
	void SetUpStack(int);
	void ClearStack(int);
	int GetStackIndex(int index);
	
	Func* currFunc;

	/*i figure it would be faster saving this in a variable
	rather than dereferencing the currFunf pointer everytime
	an instruction manipulates a stack based var*/
	int varOffset;

	
	
	int ExecPush();
	int ExecPop();
	int ExecMOV();
	int ExecADD();
	int ExecCALL();
	int ExecRET();
	int ExecCALLHOST();
};

#endif