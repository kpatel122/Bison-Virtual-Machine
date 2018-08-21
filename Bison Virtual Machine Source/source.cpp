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
#include "stack.h"
#include "vm.h"


/*
void main()
{
	CStack<int> istack;
	
	CVM vm;
	CLog log;
	CScriptLoader scriptLoader;
	
	log.Init("info.txt");

	scriptLoader.InitLogFile(&log);
	vm.InitLogFile(&log);
	scriptLoader.ReadASMFile("kunal.basm");
	scriptLoader.PrintStats();
	
	vm.AssignScript(scriptLoader.GetScript());
	vm.RunScript();

	int g;
	istack.push(5);
	istack.push(10);
	istack.push(33);
	g = istack.GetAtIndex(-2);

//	cout<<"g is"<<g<<endl;

	//g = istack.pop();
	//cout<<"g is"<<g<<endl;


}
*/