#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

class MaxQueue
{
private:
	Node* front;
	Node* rear;
	size_t size;
	size_t maxSize;
	vector<int> deque;

public:
	MaxQueue(size_t maxSize) : front(nullptr), rear(nullptr), size(0), maxSize(maxSize) {}

	~MaxQueue()
	{
		while (front != nullptr)
		{
			Node* temp = front;
			front = front->next;
			delete temp;
		}
	}

	void enqueue(int value)
	{
		if (size == maxSize)
		{
			cout << "Queue is Full" << endl;
			return;
		}
		Node* newNode = new Node{ value, nullptr };
		if (rear == nullptr)
		{
			front = rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
		size++;

		while (!deque.empty() && deque.back() < value)
			deque.pop_back();
		deque.push_back(value);
	}

	void dequeue()
	{
		if (size == 0)
		{
			cout << "Queue is Empty" << endl;
			return;
		}
		int removedValue = front->value;
		Node* temp = front;
		front = front->next;
		if (front == nullptr)
			rear = nullptr;
		delete temp;
		size--;

		if (!deque.empty() && deque.front() == removedValue)
			deque.erase(deque.begin());

		cout << removedValue << endl;
	}

	void getMax() const
	{
		if (size == 0)
		{
			cout << "Queue is Empty" << endl;
			return;
		}
		cout << deque.front() << endl;
	}

	void print() const
	{
		Node* current = front;
		while (current != nullptr)
		{
			cout << current->value << " ";
			current = current->next;
		}
		cout << endl;
	}
};

int main()
{
	size_t maxSize;
	cin >> maxSize;

	MaxQueue mq(maxSize);

	string command;
	cin >> command;

	while (command != "quit")
	{
		if (command == "enqueue")
		{
			int value;
			cin >> value;
			mq.enqueue(value);
		}
		else if (command == "dequeue")
		{
			mq.dequeue();
		}
		else if (command == "max")
		{
			mq.getMax();
		}

		cin >> command;
	}

	mq.print();

	return 0;
}