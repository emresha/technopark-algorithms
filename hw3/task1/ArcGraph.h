#include "IGraph.h"
#include <vector>
#include <utility>

class ArcGraph : public IGraph
{
public:
    explicit ArcGraph(int verticesCount);
    ArcGraph(const IGraph &graph);

    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int size;
    std::vector<std::pair<int, int>> edges;
};
