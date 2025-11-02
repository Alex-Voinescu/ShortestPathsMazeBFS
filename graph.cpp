#include "graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <QCoreApplication>
#include <QDir>

Graph::Graph() {}

Graph::~Graph(){
}

void Graph::readMatrixFromFile(const std::string& filename)
{
    QString path = QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(filename);
    std::ifstream fin(path.toStdString());
    if (!fin.is_open()) {
        std::cout<<"Can't open file \n";
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty())
            continue;

        std::vector<int> row;
        for (char ch : line) {
            if (ch == ' ' || ch == '\t')
                continue;
            if (ch >= '0' && ch <= '9') {
                row.push_back(ch - '0');
            }
        }
        if (!row.empty())
            m_matrix.push_back(row);
    }

    fin.close();
}

void Graph::createAdjList(){
    if (m_matrix.empty()) return;

    int nrRows = m_matrix.size();
    int nrCols = m_matrix[0].size();
    m_nodeId.assign(nrRows, std::vector<int>(nrCols, -1));

    int cnt = 0;
    for (int i = 0; i < nrRows; i++)
        for (int j = 0; j < nrCols; j++)
            if (m_matrix[i][j] != 0)
                m_nodeId[i][j] = cnt++;

    m_adjList.assign(cnt, std::vector<int>());


    for (int i = 0; i < nrRows; i++) {
        for (int j = 0; j < nrCols; j++) {
            if (m_matrix[i][j] == 0) continue;

            int n = m_nodeId[i][j];
            if (m_matrix[i][j] == 3)
                m_startPoint = n;
            if (m_matrix[i][j] == 2)
                m_exits.push_back(n);

            const int dr[4] = {-1, 1, 0, 0};
            const int dc[4] = {0, 0, -1, 1};

            for (int k = 0; k < 4; ++k) {
                int ni = i + dr[k];
                int nj = j + dc[k];

                if (ni < 0 || nj < 0 || ni >= nrRows || nj >= nrCols) continue;
                if (m_matrix[ni][nj] != 0)
                    m_adjList[n].push_back(m_nodeId[ni][nj]);
            }
        }
    }

}

void Graph::printAdjList() const
{
    for (size_t i = 0; i < m_adjList.size(); i++) {
        std::cout << "Nod " << i << " -> ";
        for (int v : m_adjList[i])
            std::cout << v << " ";
        std::cout << "\n";
    }
    std::cout << "Start: " << m_startPoint << "\nExits: ";
    for (int e : m_exits) std::cout << e << " ";
    std::cout << "\n";
}


const std::vector<std::vector<int>>& Graph::getMatrix(){
    return m_matrix;
}
const std::vector<std::vector<bool>>& Graph::getVisited(){
    return m_visited;
}
const std::vector<std::vector<int>>& Graph::getIdMatrix(){
    return m_nodeId;
}
const std::vector<std::vector<int>>& Graph::getAdjList(){
    return m_adjList;
}
void Graph::BFS(){
    if (m_startPoint == -1) {
        std::cout << "Start point doesn't exist\n";
        return;
    }

    int N = m_adjList.size();

    std::vector<int> parent(N, -1);
    std::vector<int> level(N, -1);
    std::vector<bool> visited(N, false);

    std::queue<int> q;


    level[m_startPoint] = 0;
    visited[m_startPoint] = true;
    q.push(m_startPoint);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int y : m_adjList[x]) {
            if (!visited[y]) {
                visited[y] = true;
                parent[y] = x;
                level[y] = level[x] + 1;
                q.push(y);
            }
        }
    }

    colorPaths(parent);
}

void Graph::colorPaths(const std::vector<int>& parent)
{
    int n = m_matrix.size(), m = m_matrix[0].size();
    m_visited.assign(n, std::vector<bool>(m, false));

    for (int exitId : m_exits) {
        int x = exitId;
        while (x != -1) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    if (m_nodeId[i][j] == x)
                        m_visited[i][j] = true;
            x = parent[x];
        }
    }
}
