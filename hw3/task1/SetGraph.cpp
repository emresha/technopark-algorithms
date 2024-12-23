#include "SetGraph.h"

SetGraph::SetGraph(int verticesCount)
    : adjacencySets(verticesCount)
{
}

SetGraph::SetGraph(const IGraph &graph)
{
    int size = graph.VerticesCount();
    adjacencySets.resize(size);

    for (int from = 0; from < size; ++from)
    {
        for (int to : graph.GetNextVertices(from))
        {
            adjacencySets[from].insert(to);
        }
    }
}

void SetGraph::AddEdge(int from, int to)
{
    adjacencySets[from].insert(to);
}

int SetGraph::VerticesCount() const
{
    return (int)(adjacencySets.size());
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    std::vector<int> result;
    result.reserve(adjacencySets[vertex].size());

    for (int to : adjacencySets[vertex])
    {
        result.push_back(to);
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (int from = 0; from < VerticesCount(); ++from)
    {
        if (adjacencySets[from].find(vertex) != adjacencySets[from].end())
        {
            result.push_back(from);
        }
    }
    return result;
}
