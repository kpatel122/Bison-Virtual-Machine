#ifndef STRINGS_H
#define STRINGS_H



class CStringTable
{
public:
	CStringTable(){numStrings = 0;}
	~CStringTable(){}
	int AddString(char*);
    char *GetStringByName(char *);
	char *GetStringByIndex(int);
	int DoesStringExist(char *);
	int GetNumberStrings(){return numStrings;}
    std::vector<char *>& GetStringStream() {return strings;} 
private:
	int numStrings;
	std::vector<char *>strings;
};

#endif