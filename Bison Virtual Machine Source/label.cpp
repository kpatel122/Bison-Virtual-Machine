#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <vector>
#include "label.h"

int CLabelTable::DoesLabelExist(char *l,int f)
{
	if(!l)
	{
		return -1;
	}

	for(int i=0; i<numLabels; i++)
	{
		if(strcmp(labels[i]->name,l) == 0)
		{
			if (f == labels[i]->funcIndex)
			{
				return i;
			}
		}
	}

	return -1;
}


Label *CLabelTable::GetLabelByIndex(int s)
{
	if ((s<0) || (s>= labels.size() ) )
	{
		return NULL;
	}

	return labels[s];
}

Label *CLabelTable::GetLabelByName(char * s,int f)
{
	int i = DoesLabelExist(s,f);

	if(i == -1)
	{
		return NULL;
	}

	return labels[i];
}



int CLabelTable::AddLabel(char *s,int func, int instr )
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
	
	int i = DoesLabelExist(s,func);
	if(i!=-1)
	{
		return -1;
	}


	Label *t = (Label*)malloc(sizeof(Label));
	


	strcpy(t->name,s);
	t->funcIndex = func;
	t->instrIndex = instr;
	
	labels.push_back(t);

	return numLabels++;

}


