
#ifndef STACK_H
#define STACK_H


#define MAX_STACK_SIZE 2000

template <class T>
class CStack
{
public:
	CStack(){;index = size = 0;}
	~CStack(){}
	void push(T);
	T pop();
	T GetAtIndex(signed int);
	void SetAtIndex(signed int,T);
	int GetSize(){return size;}
	T* GetStack(){return stack;}
	int* sizep(){return &size;}
private:

int index;
int size;
T stack[MAX_STACK_SIZE];
};


template <class T>
void CStack<T>::push(T val)
{
	if (size > MAX_STACK_SIZE)
		return;

    stack[size] = val;
	size++;
	index++;
}


template <class T>
T CStack<T>::pop()
{
	//if (! size > 0)
		//return;

	T val;
	val = stack[(size-1)];
	size--;
	index--;

	return val;
};

template <class T>
void CStack<T>::SetAtIndex(signed int index, T val)
{

	if(index <0)
	{
		index+=1;
		int temp = (size-1);
		temp +=index;
		stack[temp] = val;
		return;
	}

	stack[index] = val;
}

template <class T>
T CStack<T>::GetAtIndex(signed int index)
{

	if(index <0)
	{
		index+=1;
		int temp = (size-1);
		temp +=index;
		return stack[temp];
	}

	return stack[index];
}

#endif