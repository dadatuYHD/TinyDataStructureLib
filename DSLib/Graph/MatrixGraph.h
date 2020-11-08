#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception/Exception.h"
#include "Array/DynamicArray.h"

namespace DSLib {

#define INF 1 << 20

/*************************************************************
 * Function   : Create the directed graph by adjacency matrix
 * Description:
 * Weight:0、INF、Positive number
 *               0: The vertex gets the distance from itself
 *             INF: No edge between vertex
 * Positive number: The weight of the edge between two vertex
 * ***********************************************************
 * Vertex:Vertex are numbered from 0
 *************************************************************/
template <int N, typename Vertex, typename Weight>
class MatrixGraph : public Graph <Vertex, Weight>
{
protected:
    Vertex* m_vertexes[N];     /*storage the vertex value*/
    Weight* m_edges[N][N];     /*Adjacency Matrix*/
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
        Vertex value;

        if (!getVertex(i, value))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return value;
    }

    bool getVertex(int i, Vertex& value)
    {
        bool ret = ((0 <= i) && (i <= this->vertexCount()));

        if (ret)
        {
            if (m_vertexes[i])
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The vertex has not value ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const Vertex& value)
    {
        bool ret = ((0 <= i) && (i <= this->vertexCount()));

        if (ret)
        {
            Vertex* pVertex = m_vertexes[i];

            if (!pVertex)
            {
                pVertex = new Vertex();
            }

            if (pVertex)
            {
                *pVertex = value;

                m_vertexes[i] = pVertex;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create vertex ...");
            }
        }

        return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* pRet = nullptr;

        if ((0 <= i) && (i <= this->vertexCount()))
        {
            int vertexCount = 0;

            for (int j = 0; j < this->vertexCount(); j++)
            {
                if ( m_edges[i][j] && *(m_edges[i][j]) )
                {
                    vertexCount++;
                }
            }

            pRet = new DynamicArray<int>(vertexCount);

            if (pRet)
            {
                for (int j =0, k = 0; j < this->vertexCount(); j++)
                {
                    if ( m_edges[i][j] && *(m_edges[i][j]) )
                    {
                        pRet->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }
    }

    Weight getEdge(int i, int j)
    {
        Weight weight;

        if (!getEdge(i, j, weight))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i j is invalid ...");
        }

        return weight;
    }

    bool getEdge(int i, int j, Weight& value)
    {
        bool ret = ( (0 <= i) && (i <= this->vertexCount()) &&
                     (0 <= j) && (j <= this->vertexCount()) );

        if (ret)
        {
            if (m_edges[i][j])
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The edge has not exist ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const Weight& value)
    {
        bool ret = ( (0 <= i) && (i <= this->vertexCount()) &&
                     (0 <= j) && (j <= this->vertexCount()) );

        if (ret)
        {
            Weight* pEdge = m_edges[i][j];

            if (!pEdge)
            {
                pEdge = new Weight();
                m_edgeCount++;
            }

            if (pEdge)
            {
                *pEdge = value;

                m_edges[i] = pEdge;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create edge ...");
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret = ( (0 <= i) && (i <= this->vertexCount()) &&
                     (0 <= j) && (j <= this->vertexCount()) );

        if (ret)
        {
            Weight* pToDel = m_edges[i][j];

            m_edges[i][j] = nullptr;

            if (pToDel)
            {
                m_edgeCount--;

                delete pToDel;
            }
        }

        return ret;
    }

    int vertexCount()
    {
        return N;
    }

    int edgeCount()
    {
        return m_edgeCount;
    }

    int outDegree(int i)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= this->vertexCount()) )
        {
            for (int j = 0; j < this->vertexCount(); j++)
            {
                if ( m_edges[i][j] && *(m_edges[i][j]) )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    int inDegree(int i)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= this->vertexCount()) )
        {
            for (int j = 0; j < this->vertexCount(); j++)
            {
                if ( m_edges[j][i] && *(m_edges[j][i]) )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
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
