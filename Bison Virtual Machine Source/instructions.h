
#ifndef instructions_h
#define instructions_h



#include <vector>



#define MAX_INSTR_NAME 64


           #define INSTR_MOV               0

            #define INSTR_ADD               1
            #define INSTR_SUB               2
            #define INSTR_MUL               3
            #define INSTR_DIV               4
            #define INSTR_MOD               5
            #define INSTR_EXP               6
            #define INSTR_NEG               7
            #define INSTR_INC               8
            #define INSTR_DEC               9

            #define INSTR_AND               10
            #define INSTR_OR                11
            #define INSTR_XOR               12
            #define INSTR_NOT               13
            #define INSTR_SHL               14
            #define INSTR_SHR               15

            #define INSTR_CONCAT            16
            #define INSTR_GETCHAR           17
            #define INSTR_SETCHAR           18

            #define INSTR_JMP               19
            #define INSTR_JE                20
            #define INSTR_JNE               21
            #define INSTR_JG                22
            #define INSTR_JL                23
            #define INSTR_JGE               24
            #define INSTR_JLE               25

            #define INSTR_PUSH              26
            #define INSTR_POP               27

            #define INSTR_CALL              28
            #define INSTR_RET               29
            #define INSTR_CALLHOST          30

            #define INSTR_PAUSE             31
            #define INSTR_EXIT              32


#define OP_FLAG_TYPE_INT        1           // Integer literal value
#define OP_FLAG_TYPE_FLOAT      2           // Floating-point literal value
#define OP_FLAG_TYPE_STRING     4           // Integer literal value
#define OP_FLAG_TYPE_MEM_REF    8           // Memory reference (variable or array
                                                        // index, both absolute and relative)
#define OP_FLAG_TYPE_LINE_LABEL 16          // Line label (used for jumps)
#define OP_FLAG_TYPE_FUNC_NAME  32          // Function table index (used for Call)
#define OP_FLAG_TYPE_HOST_API_CALL  64      // Host API Call table index (used for
                                                        // CallHost)
#define OP_FLAG_TYPE_REG        128         // Register



        #define OP_TYPE_INT                 0           // Integer literal value
        #define OP_TYPE_FLOAT               1           // Floating-point literal value
        #define OP_TYPE_STRING_INDEX        2           // String literal value
        #define OP_TYPE_ABS_STACK_INDEX     3           // Absolute array index
        #define OP_TYPE_REL_STACK_INDEX     4           // Relative array index
        #define OP_TYPE_INSTR_INDEX         5           // Instruction index
        #define OP_TYPE_FUNC_INDEX          6           // Function index
        #define OP_TYPE_HOST_API_CALL_INDEX 7           // Host API call index
        #define OP_TYPE_REG                 8           // Register


struct Operand
{
	int type;
	union
	{
     int  Int;                        // Integer literal
     float Float;                    // Float literal
     int stringTableIndex;                  // String table index
     int stackIndex;                        // Stack index
     int instrIndex;                        // Instruction index
     int funcIndex;                         // Function index
     int hostAPICallIndex;                  // Host API Call index
     int Reg;                               // Register code
    };
    
	int OffsetIndex;    
};

struct Instr
{
	int opCode;
	int numberParams;
	Operand *opList;
};

struct InstrLookup
{
	char name[MAX_INSTR_NAME];
	int token;
	int numParam;
	Operand *opList;
};

class CInstrTable
{
public:
	CInstrTable();
	~CInstrTable();
	int  AddInstr(char*,int,int);
	void SetInstrOp(int,int,int);
	InstrLookup *GetInstrByIndex(int);
	InstrLookup *GetInstrByName(char *);
	bool IsValidInstr(char *);
	int AddIntrStream(int);
	std::vector<InstrLookup*> instr;
private:
	int numInstr;

	int currInstr;
};

#endif