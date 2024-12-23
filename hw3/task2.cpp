#include <iostream>
#include <vector>
#include <queue>

class Graph
{
public:
    explicit Graph(int verticesCount, bool oriented = false)
        : verticesCount(verticesCount), oriented(oriented), adjacency(verticesCount)
    {
    }

    void AddEdge(int from, int to)
    {
        adjacency[from].push_back(to);
        if (!oriented)
        {
            adjacency[to].push_back(from);
        }
    }

    int VerticesCount(void) const
    {
        return verticesCount;
    }

    long long CountShortestPaths(int u, int w) const
    {
        if (u == w)
        {
            return 1;
        }

        std::vector<int> dist(verticesCount, -1);
        std::vector<long long> ways(verticesCount, 0);

        std::queue<int> q;

        dist[u] = 0;
        ways[u] = 1;
        q.push(u);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (int neighbor : adjacency[current])
            {
                if (dist[neighbor] == -1)
                {
                    dist[neighbor] = dist[current] + 1;
                    ways[neighbor] = ways[current];
                    q.push(neighbor);
                }
                else if (dist[neighbor] == dist[current] + 1)
                {
                    ways[neighbor] += ways[current];
                }
            }
        }

        return ways[w];
    }

private:
    int verticesCount;
    bool oriented;
    std::vector<std::vector<int>> adjacency;
};

int main(void)
{
    int v, n;
    std::cin >> v >> n;

    Graph graph(v, false);

    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        graph.AddEdge(a, b);
    }

    int u, w;
    std::cin >> u >> w;

    long long result = graph.CountShortestPaths(u, w);

    std::cout << result << "\n";

    return 0;
}
