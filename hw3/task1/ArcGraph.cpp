#include "ArcGraph.h"

ArcGraph::ArcGraph(int verticesCount)
    : size(verticesCount)
{
}

ArcGraph::ArcGraph(const IGraph &graph)
{
    size = graph.VerticesCount();

    for (int from = 0; from < size; ++from)
    {
        for (int to : graph.GetNextVertices(from))
        {
            edges.emplace_back(from, to);
        }
    }
}

void ArcGraph::AddEdge(int from, int to)
{
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const
{
    return size;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    std::vector<int> result;
    for (auto &edge : edges)
    {
        if (edge.first == vertex)
            result.push_back(edge.second);
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (auto &edge : edges)
    {
        if (edge.second == vertex)
            result.push_back(edge.first);
    }
    return result;
}
