#ifndef TOKEN_H
#define TOKEN_H



#define OPEN_BRACKET "["
#define CLOSE_BRACKET "]"
#define OPEN_BRACE "{"
#define CLOSE_BRACE "}"

#define COMMA ","
#define COLON ":"


enum TOKEN_TYPE1
{
	    TOKEN_TYPE_INT,              
        TOKEN_TYPE_FLOAT,                      
        TOKEN_TYPE_STRING,                   
        TOKEN_TYPE_QUOTE,                     
        TOKEN_TYPE_IDENT,                   
        TOKEN_TYPE_COLON,                       
        TOKEN_TYPE_OPEN_BRACKET,               
        TOKEN_TYPE_CLOSE_BRACKET,              // An closing bracket
        TOKEN_TYPE_COMMA,                      // A comma
        TOKEN_TYPE_OPEN_BRACE,                // An openening curly brace
        TOKEN_TYPE_CLOSE_BRACE,               // An closing curly brace
        TOKEN_TYPE_NEWLINE,                    // A newline

		TOKEN_TYPE_INSTR,						// An instruction

        TOKEN_TYPE_SETSTACKSIZE,              // The SetStackSize directive
        TOKEN_TYPE_VAR,                        // The Var/Var [] directives
        TOKEN_TYPE_FUNC,                       // The Func directives
        TOKEN_TYPE_PARAM,                      // The Param directives
        TOKEN_TYPE_REG_RETVAL,                 // The _RetVal directives

         TOKEN_TYPE_INVALID                 

};



#define KEYWORD_FUNCTION "func"
#define KEYWORD_VARIABLE "var"
#define KEYWORD_PARAM "param"
#define KEYWORD_REG "reg0"
#define KEYWORD_STACK_SIZE "stacksize"


#endif