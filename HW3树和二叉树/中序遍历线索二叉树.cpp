#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct Node
{
	char data;
	bool ltag, rtag;
	Node* lchild, * rchild;

	Node(char val) : data(val), ltag(false), rtag(false), lchild(nullptr), rchild(nullptr) {}
};

class ThrBinTree
{
private:
	Node* root;

public:
	ThrBinTree() : root(nullptr) {}
	Node*& getRoot() { return root; }

	void constructTree(Node*& subTree)
	{
		char val;
		cin >> val;
		if (val == '#')
		{
			subTree = nullptr;
		}
		else
		{
			subTree = new Node(val);
			constructTree(subTree->lchild);
			constructTree(subTree->rchild);
		}
	}

	void inOrderThrd(Node*& subTree, Node*& pre)
	{
		if (subTree)
		{
			inOrderThrd(subTree->lchild, pre);
			if (!subTree->lchild)
			{
				subTree->ltag = true;
				subTree->lchild = pre;
			}
			if (pre && !pre->rchild)
			{
				pre->rtag = true;
				pre->rchild = subTree;
			}
			pre = subTree;
			inOrderThrd(subTree->rchild, pre);
		}
	}

	vector<Node*> inOrderTraversal()
	{
		vector<Node*> result;
		Node* current = root;

		while (current && !current->ltag)
		{
			current = current->lchild;
		}

		while (current)
		{
			result.push_back(current);
			if (current->rtag)
			{
				current = current->rchild;
			}
			else
			{
				current = current->rchild;
				while (current && !current->ltag)
				{
					current = current->lchild;
				}
			}
		}

		return result;
	}
};

int main()
{
	ThrBinTree tree;
	tree.constructTree(tree.getRoot());

	Node* pre = nullptr;
	tree.inOrderThrd(tree.getRoot(), pre);
	if (pre)
	{
		pre->rtag = true;
		pre->rchild = nullptr;
	}

	vector<Node*> nodes = tree.inOrderTraversal();

	for (size_t i = 0; i < nodes.size(); ++i)
	{
		cout << nodes[i]->data;
	}
	cout << endl;

	char val;
	cin >> val;

	bool isFound = false;
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		if (nodes[i]->data == val)
		{
			isFound = true;
			Node* succ = (i + 1 < nodes.size()) ? nodes[i + 1] : nullptr;
			Node* prev = (i > 0) ? nodes[i - 1] : nullptr;
			cout << "succ is " << (succ ? (string(1, succ->data) + to_string(succ->rtag)) : "NULL") << endl;
			cout << "prev is " << (prev ? (string(1, prev->data) + to_string(prev->ltag)) : "NULL") << endl;
		}
	}

	if (!isFound)
	{
		cout << "Not found" << endl;
	}

	return 0;
}