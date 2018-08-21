#include <stdarg.h>
#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <iostream.h>

//#include "file.h"
#include "log.h"


void CLog::Init(char *f)
{

	fp = fopen(f,"w");
	
	if(fp!=NULL)
		writeEnable = true;
	

}

void CLog::Msg(char *m,...)
{

	char buffer[80]; // working buffer

	va_list arglist; 

	va_start(arglist,m);
	vsprintf(buffer,m,arglist);
	va_end(arglist);

	if(writeEnable)
		fputs(buffer,fp);

}