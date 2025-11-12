#include<iostream>
#include<queue>
#include<iomanip>

using namespace std;

struct Node
{
	int data;
	Node* next;
};

class Graph
{
private:
	int numVertices;
	Node** adjLists;

public:
	Graph(int V)
	{
		numVertices = V;
		adjLists = new Node * [V];
		for (int i = 0; i < V; i++)
			adjLists[i] = new Node{ i, nullptr };
	}
	~Graph()
	{
		for (int i = 0; i < numVertices; i++)
		{
			Node* temp = adjLists[i];
			while (temp)
			{
				Node* toDelete = temp;
				temp = temp->next;
				delete toDelete;
			}
		}
		delete[] adjLists;
	}

	void addEdge(int src, int dest)
	{
		Node* newNode = new Node{ dest, nullptr };
		Node* current = adjLists[src];
		while (current->next)
			current = current->next;
		current->next = newNode;
	}

	int countVerticesWithinK(int start, int K)
	{
		vector<bool> visited(numVertices, false);
		queue<pair<int, int>> q;
		visited[start] = true;
		q.push({ start, 0 });
		int count = 1;
		while (!q.empty())
		{
			int currentVertex = q.front().first;
			int currentLevel = q.front().second;
			q.pop();
			if (currentLevel < K)
			{
				Node* temp = adjLists[currentVertex]->next;
				while (temp)
				{
					int adjVertex = temp->data;
					if (!visited[adjVertex])
					{
						visited[adjVertex] = true;
						q.push({ adjVertex, currentLevel + 1 });
						count++;
					}
					temp = temp->next;
				}
			}
		}
		return count;
	}
};

int main()
{
	int V, E;
	cin >> V >> E;
	Graph g(V);
	for (int i = 0; i < E; i++)
	{
		int src, dest;
		cin >> src >> dest;
		g.addEdge(src - 1, dest - 1);
		g.addEdge(dest - 1, src - 1);
	}

	cout << fixed << setprecision(2);
	for (int i = 0; i < V; i++)
	{
		float ratio = (float)g.countVerticesWithinK(i, 6) / V * 100;
		cout << i + 1 << ": " << ratio << "%" << endl;
	}

	return 0;
}