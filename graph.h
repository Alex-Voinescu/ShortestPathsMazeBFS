#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>


class Graph
{

private:
    std::vector<std::vector<int>> m_matrix;
    std::vector<std::vector<int>> m_adjList;
    std::vector<std::vector<int>> m_nodeId;
    std::vector<int> m_exits;
    int m_startPoint=-1;
    std::vector<std::vector<bool>> m_visited;

public:
    Graph();
    ~Graph();

    const std::vector<std::vector<int>>& getMatrix();
    const std::vector<std::vector<bool>>& getVisited();
    const std::vector<std::vector<int>>& getIdMatrix();
    const std::vector<std::vector<int>>& getAdjList();

    void readMatrixFromFile(const std::string& filename);
    void createGraph();
    void createAdjList();
    void printAdjList() const;
    void BFS();
    void colorPaths(const std::vector<int>& parent);
};

#endif // GRAPH_H
