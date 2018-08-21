#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <vector>
#include "strings.h"

int CStringTable::DoesStringExist(char *s)
{


	if(!s)
	{
		return -1;
	}

	for(int i=0; i<numStrings; i++)
	{
		if(strcmp(strings[i],s) == 0)
			return i;
	}

	return -1;
}

char *CStringTable::GetStringByIndex(int s)
{
	if ((s<0) || (s>= numStrings ) )
		return NULL;

	return strings[s];
}

char *CStringTable::GetStringByName(char * s)
{
	int i = DoesStringExist(s);

	if(i == -1)
		return NULL;

	return strings[i];
}



int CStringTable::AddString(char *s)
{
	if(!s)
	{
		return -1;
	}
	
	int len = strlen(s);
	if(!len)
	{
		return -1;
	}
	
	int i = DoesStringExist(s);
	if(i!=-1)
	{
		return i;
	}
	

	
	char *t = (char *)malloc(sizeof(char) * len);
			
	strcpy(t,s);
	
	strings.push_back(t);

	return numStrings++;

}
