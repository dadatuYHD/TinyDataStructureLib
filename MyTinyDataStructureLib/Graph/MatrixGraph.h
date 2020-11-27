#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"

namespace MyTiny_DSLib {

/*************************************************************
 * Function   : Create the directed graph by adjacency matrix
 * Description:
 * W:0、INF、Positive number
 *               0: Two vertices are same as or No weight value
 *             INF: No edge between vertex
 * Positive number: The weight of the edge between two vertex
 * ***********************************************************
 * V:Vertex are numbered from 0
 *************************************************************/
template <int N, typename V, typename W>
class MatrixGraph : public Graph <V, W>
{
protected:
    V* m_pVertexes[N];     /*storage the vertex value*/
    W* m_pEdges[N][N];     /*Adjacency Matrix*/
    int m_edgeCount;

public:
    MatrixGraph()
    {
        for (int i = 0; i < this->vertexCount(); i++)
        {
            m_pVertexes[i] = nullptr;

            for (int j = 0; j < this->vertexCount(); j++)
            {
                m_pEdges[i][j] = nullptr;
            }
        }
    }

    V getVertex(int i)
    {
        V value;

        if (!getVertex(i, value))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return value;
    }

    bool getVertex(int i, V& value)
    {
        bool ret = ((0 <= i) && (i < this->vertexCount()));

        if (ret)
        {
            if (m_pVertexes[i])
            {
                value = *(m_pVertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The m_pVertexes[i] is nullptr ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ((0 <= i) && (i < this->vertexCount()));

        if (ret)
        {
            V* pVertex = m_pVertexes[i];

            if (!pVertex)
            {
                pVertex = new V();
            }

            if (pVertex)
            {
                *pVertex = value;

                m_pVertexes[i] = pVertex;
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

        if ((0 <= i) && (i < this->vertexCount()))
        {
            int vertexCount = 0;

            for (int j = 0; j < this->vertexCount(); j++)
            {
                if ( m_pEdges[i][j] && (*(m_pEdges[i][j]) != INF))
                {
                    vertexCount++;
                }
            }

            pRet = new DynamicArray<int>(vertexCount);

            if (pRet)
            {
                if (vertexCount)
                {
                    for (int j =0, k = 0; j < this->vertexCount(); j++)
                    {
                        if ( m_pEdges[i][j] && (*(m_pEdges[i][j]) != INF))
                        {
                            pRet->set(k++, j);
                        }
                    }
                }
                else
                {
                    cout << "Vertex(" << i <<  ") is not adjacent Vertex" << endl;
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

        return pRet;
    }

    bool isAdjacent(int i, int j)
    {
         return (0 <= i) && (i < vertexCount()) && (0 <= j) &&
                (j < vertexCount()) && (m_pEdges[i][j] != nullptr) &&
                (*m_pEdges[i][j]) != INF;
    }

    W getEdge(int i, int j)
    {
        W weight;

        if (!getEdge(i, j, weight))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i j is invalid ...");
        }

        return weight;
    }

    bool getEdge(int i, int j, W& value)
    {
        bool ret = ( (0 <= i) && (i < this->vertexCount()) &&
                     (0 <= j) && (j < this->vertexCount()) );

        if (ret)
        {
            if (m_pEdges[i][j])
            {
                if (*(m_pEdges[i][j]) != INF)
                {
                    value = *(m_pEdges[i][j]);
                }
                else
                {
                    cout << "the edge(" << i << "-->" << j << ") is not exist ..." << endl;
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The adjacent matrix m_pEdges[i][j] is nullptr ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const W& value)
    {
        bool ret = ( (0 <= i) && (i < this->vertexCount()) &&
                     (0 <= j) && (j < this->vertexCount()) );

        if (ret)
        {
            W* pEdge = m_pEdges[i][j];

            if (!pEdge)
            {
                pEdge = new W();
                m_edgeCount++;
            }

            if (pEdge)
            {
                *pEdge = value;

                m_pEdges[i][j] = pEdge;
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
        bool ret = ( (0 <= i) && (i < this->vertexCount()) &&
                     (0 <= j) && (j < this->vertexCount()) );

        if (ret)
        {
//            W* pToDel = m_pEdges[i][j];

//            m_pEdges[i][j] = nullptr;

//            if (pToDel)
//            {
//                m_edgeCount--;

//                delete pToDel;
//            }
            *(m_pEdges[i][j]) = INF;

            m_edgeCount--;
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
                if ( m_pEdges[i][j] && (*(m_pEdges[i][j]) != INF))
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
                if ( m_pEdges[j][i] && (*(m_pEdges[j][i]) != INF))
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
                W* pToDel = m_pEdges[i][j];

                m_pEdges[i][j] = nullptr;

                if (pToDel)
                {
                    delete pToDel;
                }
            }

            V* pToDel = m_pVertexes[i];

            m_pVertexes[i] = nullptr;

            if (pToDel)
            {
                delete pToDel;
            }
        }
    }

};

}

#endif // MATRIXGRAPH_H
