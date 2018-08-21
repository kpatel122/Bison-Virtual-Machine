

#ifndef hostApi_H
#define hostApi_H

typedef void (__cdecl *fptralias)(void); 

struct HOST_API
{
	char name[64];
	fptralias func;
	int numArg;
};




#endif