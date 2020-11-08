#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"

namespace DSLib {

template <int N, typename Vertex, typename Weight>
class MatrixGraph : public Graph <Vertex, Weight>
{
protected:
    Vertex* m_vertexes[N];
    Weight* m_edges[N][N];
    int m_edgeCount;

public:
    MatrixGraph()
    {
        for (int i = 0; i < this->vertexCount(); i++)
        {
            m_vertexes[i] = nullptr;

            for (int j = 0; j < this->vertexCount(); j++)
            {
                m_edges[i][j] = nullptr;
            }
        }
    }

    Vertex getVertex(int i)
    {

    }

    bool getVertex(int i, Vertex& value)
    {

    }

    bool setVertex(int i, const Vertex& value)
    {

    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {

    }

    Weight getEdge(int i, int j)
    {

    }

    bool getEdge(int i, int j, Weight& value)
    {

    }

    bool setEdge(int i, int j, const Weight& value)
    {

    }

    bool removeEdge(int i, int j)
    {

    }

    int vertexCount()
    {

    }

    int edgeCount()
    {

    }

    int outDegree(int i)
    {

    }

    int inDegree(int i)
    {

    }

    ~MatrixGraph()
    {
        for (int i = 0; i < this->vertexCount(); i++)
        {
            for (int j = 0; j < this->vertexCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }

};

}

#endif // MATRIXGRAPH_H
