#include<iostream>
#include<queue>

using namespace std;

class Graph
{
private:
	int numVertices;
	bool** adjMatrix;

	void dfs(int v, bool* visited, bool& first)
	{
		if (!first)
			cout << " ";
		first = false;
		visited[v] = true;
		cout << v;
		for (int i = 0; i < numVertices; i++)
		{
			if (!visited[i] && adjMatrix[v][i])
			{
				dfs(i, visited, first);
			}
		}
	}

public:
	Graph(int V, int E)
	{
		numVertices = V;
		adjMatrix = new bool* [V];
		for (int i = 0; i < V; i++)
		{
			adjMatrix[i] = new bool[V];
			for (int j = 0; j < V; j++)
			{
				adjMatrix[i][j] = false;
			}
		}
		for (int i = 0; i < E; i++)
		{
			int u, v;
			cin >> u >> v;
			adjMatrix[u][v] = true;
			adjMatrix[v][u] = true;
		}
	}
	~Graph()
	{
		for (int i = 0; i < numVertices; i++)
		{
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
	}

	void bfsConnectedComponents()
	{
		bool* visited = new bool[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			visited[i] = false;
		}

		queue<int> q;
		for (int i = 0; i < numVertices; i++)
		{
			if (!visited[i])
			{
				q.push(i);
				visited[i] = true;
				cout << "{";
				while (!q.empty())
				{
					int curr = q.front();
					q.pop();
					cout << curr;
					for (int j = 0; j < numVertices; j++)
					{
						if (!visited[j] && adjMatrix[curr][j])
						{
							q.push(j);
							visited[j] = true;
						}
					}
					if (!q.empty())
						cout << " ";
				}
				cout << "}";
			}
		}

		delete[] visited;
	}

	void dfsConnectedComponents()
	{
		bool* visited = new bool[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			visited[i] = false;
		}
		for (int i = 0; i < numVertices; i++)
		{
			if (!visited[i])
			{
				cout << "{";
				bool first = true;
				dfs(i, visited, first);
				cout << "}";
			}
		}
		delete[] visited;
	}
};

int main()
{
	int V, E;
	cin >> V >> E;
	Graph g(V, E);
	g.dfsConnectedComponents();
	cout << endl;
	g.bfsConnectedComponents();

	return 0;
}