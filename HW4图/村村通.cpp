#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class UnionFind
{
private:
	vector<int> parent, rank;

public:
	UnionFind(int size) : parent(size), rank(size, 0)
	{
		for (int i = 0; i < size; i++)
			parent[i] = i;
	}
	int find(int u)
	{
		if (parent[u] != u)
			parent[u] = find(parent[u]);
		return parent[u];
	}
	void unite(int u, int v)
	{
		int rootU = find(u);
		int rootV = find(v);
		if (rootU != rootV)
		{
			if (rank[rootU] < rank[rootV])
				parent[rootU] = rootV;
			else if (rank[rootU] > rank[rootV])
				parent[rootV] = rootU;
			else
			{
				parent[rootV] = rootU;
				rank[rootU]++;
			}
		}
	}
	bool connected(int u, int v)
	{
		return find(u) == find(v);
	}
};

struct Edge
{
	int src, dest, weight;

	Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class WeightedGraph
{
private:
	int numVertices;
	vector<Edge> edges;
	UnionFind uf;

public:
	WeightedGraph(int V) : numVertices(V), uf(V)
	{
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				int weight;
				cin >> weight;
				if (i < j)
				{
					edges.emplace_back(i, j, weight);
				}
			}
		}
	}

	vector<Edge> initMST(int numEdges)
	{
		vector<Edge> mst;
		for (int i = 0; i < numEdges; i++)
		{
			int src, dest;
			cin >> src >> dest;
			mst.emplace_back(src - 1, dest - 1, 0);
			uf.unite(src - 1, dest - 1);
		}
		return mst;
	}

	void MST(vector<Edge>& mst)
	{
		sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
			return a.weight < b.weight;
			});
		for (const auto& edge : edges)
		{
			if (!uf.connected(edge.src, edge.dest))
			{
				mst.push_back(edge);
				uf.unite(edge.src, edge.dest);
			}
		}
	}
};

int main()
{
	int V;
	cin >> V;
	WeightedGraph g(V);

	int E;
	cin >> E;
	vector<Edge> mst = g.initMST(E);
	g.MST(mst);

	int totalWeight = 0;
	for (const auto& edge : mst)
	{
		totalWeight += edge.weight;
	}

	cout << totalWeight << endl;
	return 0;
}