
#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#define MAX_FUNCTION_NAME 64
#define FUNCTION_MAIN "Main"

struct Func
{
	int entryIndex;
	int numParams;
	int numLocalVar;
	int stackSize;

	char name[MAX_FUNCTION_NAME];


};

class CFuncTable
{
public:
	CFuncTable();
	~CFuncTable();
	int AddFunc(char*);
    void SetEntryPoint(int,int);
    void SetFuncInfo(int,int,int);
	Func * GetFuncByName(char *);
	Func * GetFuncByIndex(int);
	int GetNumFunc(){return funcCounter;}
	std::vector<Func *>& GetFuncStream() {return func;}
		
private:
	std::vector<Func *> func;
	int funcCounter;
	
};
#endif