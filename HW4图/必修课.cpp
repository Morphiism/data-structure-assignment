#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<vector<int>> reverseGraph(const vector<vector<int>>& graph, int n)
{
	vector<vector<int>> revGraph(n);
	for (int i = 0; i < n; i++)
	{
		for (int pre : graph[i])
		{
			revGraph[pre].emplace_back(i);
		}
	}
	return revGraph;
}

int main()
{
	int n;
	cin >> n;

	vector<vector<int>> graph;
	vector<int> time(n, 0);
	vector<int> indegree(n, 0);

	for (int i = 0; i < n; i++)
	{
		int t;
		cin >> t;
		time[i] = t;

		vector<int> pre;
		int preCount;
		cin >> preCount;
		for (int j = 0; j < preCount; j++)
		{
			int preTask;
			cin >> preTask;
			pre.emplace_back(preTask - 1);
		}
		graph.emplace_back(pre);
		indegree[i] = preCount;
	}

	vector<vector<int>> revGraph = reverseGraph(graph, n);

	vector<int> earliest_end(n, 0);
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		if (indegree[i] == 0)
		{
			earliest_end[i] = time[i];
			q.push(i);
		}
	}

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();
		for (int next : revGraph[curr])
		{
			earliest_end[next] = max(earliest_end[next], earliest_end[curr] + time[next]);
			indegree[next]--;
			if (indegree[next] == 0)
			{
				q.push(next);
			}
		}
	}

	queue<int> qr;
	int earliest_end_time = 0;
	for (int t : earliest_end)
	{
		earliest_end_time = max(earliest_end_time, t);
	}
	vector<bool> critical(n, false);

	for (int i = 0; i < n; i++)
	{
		if (earliest_end[i] == earliest_end_time)
		{
			qr.push(i);
			critical[i] = true;
		}
	}

	while (!qr.empty())
	{
		int curr = qr.front();
		qr.pop();
		for (int pre : graph[curr])
		{
			if (earliest_end[pre] + time[curr] == earliest_end[curr] && !critical[pre])
			{
				critical[pre] = true;
				qr.push(pre);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		cout << earliest_end[i] << " " << (critical[i] ? 1 : 0) << endl;
	}

	return 0;
}