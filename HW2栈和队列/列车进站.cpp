#include <iostream>
#include <string>

using namespace std;

class Stack
{
private:
	char* base;
	char* top;
	size_t size;

public:
	Stack(size_t size)
	{
		this->size = size;
		base = new char[size];
		top = base;
	}

	~Stack()
	{
		delete[] base;
	}

	void push(char c)
	{
		if (top - base == size)
		{
			cout << "Overflow" << endl;
			return;
		}
		*top = c;
		top++;
	}

	char pop()
	{
		if (top == base)
		{
			cout << "Underflow" << endl;
			return '\0';
		}
		top--;
		return *top;
	}

	char getTop()
	{
		if (top == base)
		{
			cout << "Empty" << endl;
			return '\0';
		}
		return *(top - 1);
	}

	bool isEmpty()
	{
		return top == base;
	}
};

int main()
{
	string input;
	cin >> input;

	string str;

	while (cin >> str)
	{
		int i = 0;
		int j = 0;
		Stack stack(input.length());

		while (i < input.length() && j < str.length())
		{
			stack.push(input[i]);
			i++;
			
			while (j < str.length() && !stack.isEmpty() && stack.getTop() == str[j])
			{
				stack.pop();
				j++;
			}
		}

		if (i == input.length() && j == str.length() && stack.isEmpty())
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}

	return 0;
}