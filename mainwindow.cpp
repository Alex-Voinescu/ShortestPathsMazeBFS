#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1000, 800);
    m_graph.readMatrixFromFile("labirint.txt");
    m_graph.createAdjList();
    m_graph.BFS();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{

    QPainter p(this);  
    auto matrix = m_graph.getMatrix();
    auto visited = m_graph.getVisited();
    auto adjList = m_graph.getAdjList();
    auto idMatrix = m_graph.getIdMatrix();

    if (matrix.empty()) return;

    int graphCenterY = 150;

    int nrRows = matrix.size();
    int nrCols = matrix[0].size();
    int cell = 40;
    int offsetX1 = 220, offsetY = 350;
    int offsetX2=offsetX1 + nrCols * cell + 80;
    p.save();

    int totalNodes = adjList.size();
    if (totalNodes > 0) {
        int centerX = width() / 2;
        int radius = 120;
        int nodeRadius = 15;

        std::vector<QPointF> pos(totalNodes);
        for (int i = 0; i < totalNodes; ++i) {
            double angle = (2 * M_PI * i) / totalNodes;
            pos[i] = QPointF(centerX + radius * std::cos(angle),
                             graphCenterY + radius * std::sin(angle));
        }


        p.setPen(QPen(Qt::darkGray, 2));
        for (int i = 0; i < totalNodes; ++i)
            for (int v : adjList[i])
                if (v > i)
                    p.drawLine(pos[i], pos[v]);


        for (int i = 0; i < totalNodes; ++i) {
            QRectF rect(pos[i].x() - nodeRadius, pos[i].y() - nodeRadius,
                        nodeRadius * 2, nodeRadius * 2);
            p.setBrush(Qt::white);
            p.setPen(Qt::black);
            p.drawEllipse(rect);
            p.drawText(rect, Qt::AlignCenter, QString::number(i+1));
        }

        p.setPen(Qt::white);
        p.drawText(centerX - 80, graphCenterY - radius - 20,
                   "Graful bazat pe lista de adiacenta");
    }

    p.restore();
    matrix=m_graph.getMatrix();

    for (int i = 0; i < nrRows; i++) {
        for (int j = 0; j < nrCols; j++) {
            QRect rect1(offsetX1 + j * cell, offsetY + i * cell, cell, cell);

            int val = matrix[i][j];
            QColor color;

            if (val == 0) color = Qt::black;
            else if (val == 1) color = Qt::white;
            else if (val == 2) color = Qt::red;
            else if (val == 3) color = Qt::blue;
            p.fillRect(rect1, color);
            p.drawRect(rect1);

            QRect rect2(offsetX2 + j * cell, offsetY + i * cell, cell, cell);

            if (val == 0) color = Qt::black;
            else if (val == 1) color = Qt::white;
            else if (val == 2) color = Qt::red;
            else if (val == 3) color = Qt::blue;

            if (visited.size() == nrRows && visited[i][j] &&
                val != 0 && val != 2 && val != 3)
                color = Qt::green;

            p.fillRect(rect2, color);
            p.drawRect(rect2);
        }
    }


    p.setPen(Qt::white);
    p.drawText(offsetX1+60, offsetY - 15, "Labirint initial");
    p.drawText(offsetX2+60, offsetY - 15, "Rezolvare labirint");

}
