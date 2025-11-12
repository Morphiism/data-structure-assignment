#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX / 2;

class Graph
{
public:
    int n;
    vector<vector<pair<int, int>>> adj;

    Graph(int nodes) : n(nodes), adj(n) {}

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    vector<int> dijkstra(int src)
    {
        vector<int> dist(n, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({ 0, src });

        while (!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d > dist[u]) continue;
            for (auto& edge : adj[u])
            {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({ dist[v], v });
                }
            }
		}

        return dist;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    Graph g(V);

    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u - 1, v - 1, w);
    }

    int numHerbs, numPonies;
    cin >> numHerbs >> numPonies;

    vector<int> herbPos(numHerbs);
    for (int i = 0; i < numHerbs; ++i)
    {
        int pos;
        cin >> pos;
        herbPos[i] = pos - 1;
    }

    for (int i = 0; i < numPonies; ++i)
    {
        int start, end;
        cin >> start >> end;
        start--; end--;

        auto distStart = g.dijkstra(start);
        auto distEnd = g.dijkstra(end);

        int ans = INF;
        for (int h : herbPos)
        {
            if (distStart[h] < INF && distEnd[h] < INF)
                ans = min(ans, distStart[h] + distEnd[h]);
        }

        cout << ans << endl;
    }

    return 0;
}