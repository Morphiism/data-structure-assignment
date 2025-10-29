#include<iostream>
#include<stack>
#include<string>

using namespace std;

struct Node {
	char data;
	Node* left;
	Node* right;

	Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
	Node* root;
	Node* ptr;
	stack<Node*> nodeStack;

public:
	BinaryTree() : root(nullptr), ptr(nullptr) {}
	void push(char val)
	{
		Node* newNode = new Node(val);
		if (!root)
		{
			root = newNode;
			ptr = root;
		}
		else
		{
			if (!ptr->left)
			{
				ptr->left = newNode;
				ptr = ptr->left;
			}
			else
			{
				ptr->right = newNode;
				ptr = ptr->right;
			}
		}
		nodeStack.push(ptr);
	}
	Node* pop()
	{
		if (!nodeStack.empty())
		{
			Node* topNode = nodeStack.top();
			ptr = topNode;
			nodeStack.pop();
			return topNode;
		}
		return nullptr;
	}
	Node* getRoot()
	{
		return root;
	}
	void postOrder(Node* node)
	{
		if (node)
		{
			postOrder(node->left);
			postOrder(node->right);
			cout << node->data;
		}
	}
};

int main()
{
	int n;
	cin >> n;

	BinaryTree tree;
	string cmd;

	for (int i = 0; i < 2 * n; ++i)
	{
		cin >> cmd;
		if (cmd == "push")
		{
			char val;
			cin >> val;
			tree.push(val);
		}
		else if (cmd == "pop")
		{
			tree.pop();
		}
	}

	tree.postOrder(tree.getRoot());

	return 0;
}