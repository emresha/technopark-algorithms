#include "ListGraph.h"

ListGraph::ListGraph(int verticesCount)
    : adjacencyLists(verticesCount)
{
}

ListGraph::ListGraph(const IGraph &graph)
{
    int size = graph.VerticesCount();
    adjacencyLists.resize(size);

    for (int i = 0; i < size; ++i)
    {
        auto nextVertices = graph.GetNextVertices(i);
        adjacencyLists[i] = nextVertices;
    }
}

void ListGraph::AddEdge(int from, int to)
{
    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
    return static_cast<int>(adjacencyLists.size());
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (int from = 0; from < VerticesCount(); ++from)
    {
        for (int to : adjacencyLists[from])
        {
            if (to == vertex)
                result.push_back(from);
        }
    }
    return result;
}
