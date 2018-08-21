#ifndef STRING_H
#define STRING_H

/*String info*/
class CStringInfo
{

public:

	static	bool IsCharNumeric(char &);
	static	bool IsCharIdent(char &);
	static	bool IsCharNewLine(char &);
	static	bool IsCharWhiteSpace(char &);
	static	bool IsCharDelimiter(char &);

	static	bool IsStringIdent(char *);
	static	bool IsStringInt(char *);
	static	bool IsStringFloat(char *);
	static	bool IsStringWhiteSpace(char *);
	static	bool IsStringQuote(char *);
	static  void MakeStringLowerCase(char *);
	static  void RemoveStringQuotes(char *);



private:
	
	static	bool VerifyNumeric(char *,bool &);
	
	/*Make a singleton class*/
	CStringInfo();
	~CStringInfo();
	
};

#endif