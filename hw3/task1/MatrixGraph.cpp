#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount)
    : matrix(verticesCount, std::vector<bool>(verticesCount, false))
{
}

MatrixGraph::MatrixGraph(const IGraph &graph)
{
    int size = graph.VerticesCount();
    matrix.resize(size, std::vector<bool>(size, false));

    for (int from = 0; from < size; ++from)
    {
        for (int to : graph.GetNextVertices(from))
        {
            matrix[from][to] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to)
{
    matrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const
{
    return static_cast<int>(matrix.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    std::vector<int> next;
    for (int to = 0; to < VerticesCount(); ++to)
    {
        if (matrix[vertex][to])
        {
            next.push_back(to);
        }
    }
    return next;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prev;
    for (int from = 0; from < VerticesCount(); ++from)
    {
        if (matrix[from][vertex])
            prev.push_back(from);
    }
    return prev;
}
