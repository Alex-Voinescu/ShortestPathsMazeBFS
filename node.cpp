#include "node.h"

Node::Node(int index, int row, int col):m_index(index), m_row(row),m_col(col)
{}

void Node::setIndex(int index){
    m_index=index;
}

int Node::getIndex(){
    return m_index;
}
int Node::getCol(){
    return m_col;
}
int Node::getRow(){
    return m_row;
}
