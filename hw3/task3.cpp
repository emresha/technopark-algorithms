#include <bits/stdc++.h>
using namespace std;

static const long long INF = LLONG_MAX;

class Graph
{
public:
    Graph(int N, bool oriented = false)
        : n(N), isOriented(oriented), adjacency(N)
    {
    }

    void AddEdge(int from, int to, long long weight)
    {
        adjacency[from].push_back({to, weight});
        if (!isOriented)
        {
            adjacency[to].push_back({from, weight});
        }
    }

    long long Dijkstra(int start, int finish) const
    {
        vector<long long> dist(n, INF);

        set<pair<long long, int>> s;

        dist[start] = 0;
        s.insert({0LL, start});

        while (!s.empty())
        {
            auto [curDist, u] = *s.begin();
            s.erase(s.begin());

            if (u == finish)
                break;

            if (curDist > dist[u])
                continue;

            for (auto &edge : adjacency[u])
            {
                int v = edge.first;
                long long w = edge.second;

                if (dist[u] + w < dist[v])
                {
                    if (dist[v] != INF)
                        s.erase({dist[v], v});

                    dist[v] = dist[u] + w;

                    s.insert({dist[v], v});
                }
            }
        }

        return dist[finish];
    }

private:
    int n;

    bool isOriented;

    struct Edge
    {
        int first;
        long long second;
    };

    vector<vector<Edge>> adjacency;
};

int main(void)
{
    int N, M;
    cin >> N >> M;

    Graph graph(N, false);

    for (int i = 0; i < M; i++)
    {
        int from, to;
        long long t;
        cin >> from >> to >> t;
        graph.AddEdge(from, to, t);
    }

    int start, finish;
    cin >> start >> finish;

    long long answer = graph.Dijkstra(start, finish);

    cout << answer << "\n";

    return 0;
}
