#include<iostream>
#include<queue>

using namespace std;

struct Node {
	bool visited;
	Node* left;
	Node* right;
	Node* parent;

	Node() : visited(false), left(nullptr), right(nullptr), parent(nullptr) {}
};

int main()
{
	int n, start;
	cin >> n >> start;

	Node** nodes = new Node * [n];
	for (int i = 0; i < n; i++)
	{
		nodes[i] = new Node();
	}

	for (int i = 0; i < n; i++)
	{
		int leftID, rightID;
		cin >> leftID >> rightID;
		if (leftID != -1)
		{
			nodes[i]->left = nodes[leftID];
			nodes[leftID]->parent = nodes[i];
		}
		if (rightID != -1)
		{
			nodes[i]->right = nodes[rightID];
			nodes[rightID]->parent = nodes[i];
		}
	}

	queue<Node*> bfsQueue;
	bfsQueue.push(nodes[start]);

	int distance = 0;
	size_t layerSize = bfsQueue.size();
	while (!bfsQueue.empty())
	{
		if (layerSize == 0)
		{
			distance++;
			layerSize = bfsQueue.size();
		}
		Node* currentNode = bfsQueue.front();
		bfsQueue.pop();
		layerSize--;
		currentNode->visited = true;
		if (currentNode->left && !currentNode->left->visited)
		{
			bfsQueue.push(currentNode->left);
		}
		if (currentNode->right && !currentNode->right->visited)
		{
			bfsQueue.push(currentNode->right);
		}
		if (currentNode->parent && !currentNode->parent->visited)
		{
			bfsQueue.push(currentNode->parent);
		}
	}

	cout << distance << endl;

	delete[] nodes;
	return 0;
}