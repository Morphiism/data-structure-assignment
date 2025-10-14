#include <iostream>

using namespace std;

struct Node
{
	int row;
	int col;
	Node* next;
};

class Queue
{
private:
	Node* front;
	Node* rear;

public:
	Queue() : front(nullptr), rear(nullptr) {}

	bool isEmpty() const
	{
		return front == nullptr;
	}

	void enqueue(int row, int col)
	{
		Node* newNode = new Node{ row, col, nullptr };
		if (isEmpty())
		{
			front = rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
	}

	void dequeue()
	{
		if (isEmpty())
			return;
		Node* temp = front;
		front = front->next;
		if (front == nullptr)
			rear = nullptr;
		delete temp;
	}

	int getFrontRow() const
	{
		if (isEmpty())
		{
			cout << "Empty" << endl;
			return -1;
		}
		return front->row;
	}

	int getFrontCol() const
	{
		if (isEmpty())
		{
			cout << "Empty" << endl;
			return -1;
		}
		return front->col;
	}

	~Queue()
	{
		while (!isEmpty())
			dequeue();
	}
};

int main()
{
	int row, col;
	cin >> row >> col;

	bool** mat = new bool* [row];
	for (int i = 0; i < row; ++i)
	{
		mat[i] = new bool[col];
		for (int j = 0; j < col; ++j)
		{
			int value;
			cin >> value;
			mat[i][j] = (value == 1);
		}
	}

	Queue queue;
	int regions = 0;

	for (int i = 1; i < row - 1; ++i)
	{
		for (int j = 1; j < col - 1; ++j)
		{
			if (mat[i][j])
			{
				regions++;
				queue.enqueue(i, j);
				mat[i][j] = false;
				while (!queue.isEmpty())
				{
					int r = queue.getFrontRow();
					int c = queue.getFrontCol();
					queue.dequeue();
					int directions[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
					for (auto& dir : directions)
					{
						int newRow = r + dir[0];
						int newCol = c + dir[1];
						if (newRow >= 0 && newRow <= row - 1 && newCol >= 0 && newCol <= col - 1
							&& mat[newRow][newCol])
						{
							queue.enqueue(newRow, newCol);
							mat[newRow][newCol] = false;
						}
					}
				}
			}
		}
	}

	cout << regions << endl;
	
	for (int i = 0; i < row; ++i)
	{
		delete[] mat[i];
	}
	delete[] mat;
	return 0;
}