#ifndef NODE_H
#define NODE_H
#include <QPoint>

class Node
{
private:
    int m_index;
    int m_row;
    int m_col;

public:
    bool isEntrance=false;
    bool isExit=false;
    bool isOnPath=false;

    Node(int index=0,int m_row=0,int m_col=0 );

    void setIndex(int index);
    void setCoords(QPoint p);

    int getIndex();
    int getRow();
    int getCol();
};

#endif // NODE_H
