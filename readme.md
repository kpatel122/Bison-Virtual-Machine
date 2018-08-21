# Bison Virtual Machine
Bison Virtual Machine is a mini software implementation of the Von Neumann architecture similar to the Java Virtual Machine. This project was for my university dissertation on developing  Compilers, Virtual Machines & Graphic Engines.

# Description
The VM processes opcodes and their operators as created by the Bison Assembler. When an appliation function call is made, assembly language is used to implement the call.

```C++
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
```


# Documentation
Documentation I wrote for the project (doc files):

* [Bison Virtual Machine](https://github.com/kpatel122/Bison-Virtual-Machine/blob/master/Documents/Bison-Scripting-System.doc)

## Languages
C++/x86 Assembly
## Built With
Visual Studio 6

## Author
Kunal Patel

## License
This project is released under the [MIT License](https://opensource.org/licenses/MIT) 

