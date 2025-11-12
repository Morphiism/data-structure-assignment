#include<iostream>
#include<string>

using namespace std;

void dfs(int u, int k, string s, bool** adj)
{
	if (k == 9)
	{
		for (int i = 0; i < 9; i++)
			s[i]++;

		cout << s << endl;
		return;
	}

	for (int v = 0; v < 5; v++)
	{
		if (adj[u][v])
		{
			adj[u][v] = false;
			adj[v][u] = false;

			dfs(v, k + 1, s + to_string(v), adj);

			adj[u][v] = true;
			adj[v][u] = true;
		}
	}
}

int main()
{
	bool** adj = new bool* [5];
	for (int i = 0; i < 5; i++)
	{
		adj[i] = new bool[5];
		for (int j = 0; j < 5; j++)
			adj[i][j] = true;
	}
	
	adj[0][0] = false;
	adj[1][1] = false;
	adj[2][2] = false;
	adj[3][3] = false;
	adj[4][4] = false;
	adj[0][3] = false;
	adj[3][0] = false;
	adj[1][3] = false;
	adj[3][1] = false;

	for (int i = 0; i < 5; i++)
		dfs(i, 1, to_string(i), adj);

	for (int i = 0; i < 5; i++)
		delete[] adj[i];
	delete[] adj;
	return 0;
}