#ifndef SCRIPT_H
#define SCRIPT_H

#define PRINT(x) cout<<x<<""; log->Msg(x);


#define Error(x) cout<<"Error: "<<x<<"\n"; numErrors++; \
		log->Msg("Error : %s\n", x); return -1;

struct BASM_Header
{
	char id[4];
	
	int numInstr;
	int numFunc;
	int numStrings;
	int numAPICalls;
	int numSymbols;
	int numLineLable;
	int stackSize;
	int main;
	int mainIndex;
	int globalSize;

};

struct Script
{
	

	std::vector<Instr *> instrStream;

	CFuncTable   funcTable;
	CSymbolTable symbolTable;
	CStringTable stringTable;
	CStringTable apiFuncTable;
	CLabelTable  labelTable;
	int stackSize;
	int mainIndex;
	int globalSize;
	
};

class CScriptLoader
{
public:

	CScriptLoader(){numScripts = scriptIndex =0 ;}
	~CScriptLoader(){}
	InitLogFile(char *f);
	InitLogFile(CLog *l);
	
	int ReadASMFile(char *);

	int ReadFuncTable();
	int ReadSymbolTable();
	int ReadStringTable();
	int ReadAPITable();
	int ReadLabelTable();
	int ReadInstructions();
	int ReadHeader();
	
	CLog *log;
	BASM_Header header;
	
	Script *script;
	
	Script *GetScript(){return script;}

	void PrintStats();

	
	bool inFunction;
	bool isMainDefined;

	
	int mainIndex;
	int instrIndex;
	int stackSize;
	
	int globalSize;
	int funcIndex;
	
	int	numErrors;
	
	int numAPICalls;
	int numFunc;
    int numLineLable;
	int numSymbols;
	int numStrings;
	int numInstr;
	

	int numScripts;
	int scriptIndex;


	FILE *f;
	
};

#endif