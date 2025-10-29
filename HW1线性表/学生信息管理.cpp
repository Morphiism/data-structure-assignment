#include<iostream>
#include<string>

#define INCREMENT 10

using namespace std;

struct Student
{
	string no;
	string name;

	Student(string n = "", string s = "") : no(n), name(s) {}
};

class SeqList
{
public:
	Student* data;
	int maxSize;
	int length;

	SeqList(int size)
	{
		data = new Student[size + INCREMENT];
		maxSize = size + INCREMENT;
		length = size;
	}
	~SeqList()
	{
		delete[] data;
	}

	int getLength() const
	{
		return length;
	}

	void insert(int i, const Student& x)
	{
		if (i<0 || i>length)
		{
			cout << -1 << endl;
			return;
		}

		if (length == maxSize)
		{
			int newSize = maxSize + INCREMENT;
			Student* newData = new Student[newSize];
			for (int j = 0; j < length; j++)
				newData[j] = data[j];
			delete[] data;
			data = newData;
			maxSize = newSize;
		}

		for (int j = length - 1; j >= i; j--)
			data[j + 1] = data[j];

		data[i] = x;
		length++;

		cout << 0 << endl;
		return;
	}

	void remove(int i)
	{
		if (i < 0 || i >= length)
		{
			cout << -1 << endl;
			return;
		}

		for (int j = i; j < length - 1; j++)
			data[j] = data[j + 1];

		length--;
		
		cout << 0 << endl;
		return;
	}

	void checkName(const string& name) const
	{
		for (int i = 0; i < length; i++)
		{
			if (data[i].name == name)
			{
				cout << i + 1 << " " << data[i].no << " " << data[i].name << endl;
				return;
			}
		}
		cout << -1 << endl;
		return;
	}

	void checkNo(const string& no) const
	{
		for (int i = 0; i < length; i++)
		{
			if (data[i].no == no)
			{
				cout << i + 1 << " " << data[i].no << " " << data[i].name << endl;
				return;
			}
		}
		cout << -1 << endl;
		return;
	}
};

int main()
{
	int n;
	cin >> n;

	SeqList list(n);

	for (int i = 0; i < n; i++)
	{
		string no, name;
		cin >> no >> name;
		list.data[i] = Student(no, name);
	}

	string cmd;
	cin >> cmd;

	while (cmd != "end")
	{
		if (cmd == "insert")
		{
			int i;
			string no, name;
			cin >> i >> no >> name;
			list.insert(i - 1, Student(no, name));
		}
		else if (cmd == "remove")
		{
			int i;
			cin >> i;
			list.remove(i - 1);
		}
		else if (cmd == "check")
		{
			cin >> cmd;
			if (cmd == "name")
			{
				string name;
				cin >> name;
				list.checkName(name);
			}
			else if (cmd == "no")
			{
				string no;
				cin >> no;
				list.checkNo(no);
			}
		}

		cin >> cmd;
	}

	cout << list.getLength() << endl;

	return 0;
}