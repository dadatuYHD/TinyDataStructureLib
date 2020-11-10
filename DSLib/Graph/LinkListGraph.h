#ifndef LINKLISTGRAPH_H
#define LINKLISTGRAPH_H

#include <iostream>
#include "Graph.h"
#include "Exception/Exception.h"
#include "Array/DynamicArray.h"
#include "List/LinkList.h"

namespace DSLib {

template <typename V, typename W>
class LinkListGraph : public Graph<V, W>
{
protected:
    struct Edge : public Object
    {
        int startVertex;         /*storage the start vertex number */
        int endVertex;           /*storage the end vertex number */
        W weight;                /*The weight about the edge*/

        Edge(int i = -1, int j = -1)
        {
            startVertex = i;
            endVertex   = j;
        }

        Edge(int i, int j, const W& value)
        {
            startVertex = i;
            endVertex   = j;
            weight      = value;
        }

        bool operator == (const Edge& obj)
        {
            return ((startVertex == obj.startVertex) && (endVertex == obj.endVertex));
        }

        bool operator != (const Edge& obj)
        {
            return !(*this == obj);
        }
    };

    struct Vertex : public Object
    {
        V* m_pVertexData;            /*storage the vertex value */
        LinkList< Edge > edge;   /*the edge which adjacent the vertex*/

        Vertex()
        {
            m_pVertexData = nullptr;
        }
    };

    LinkList<Vertex*> m_ajLinkList;
public:

    /****************************************************************
     * Arg[In][num]:the number of vertex
     ****************************************************************/
    LinkListGraph(unsigned int num = 0)
    {
        for (int i = 0; i < num; i++)
        {
            addVertex();
        }
    }

    /*****************************************************
     * return:the number of the vertex which is added now
     *         fail: -1
     *      success: >=0
     *****************************************************/
    int addVertex(void)
    {
        int ret = -1;

        Vertex * pVertex = new Vertex();

        if (pVertex)
        {
            m_ajLinkList.insert(pVertex);

            ret = m_ajLinkList.length() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create Vertex object ...");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();

        if (ret >= 0)
        {
            setVertex(ret, value);
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ((0 <= i) && (i < this->vertexCount()));

        if (ret)
        {
            Vertex* pVertex = m_ajLinkList.get(i);
            V* pVertexData = pVertex->m_pVertexData;

            if (!pVertexData)
            {
                pVertexData = new V();
            }

            if (pVertexData)
            {
                *pVertexData = value;
                pVertex->m_pVertexData = pVertexData;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create VertexData object ...");
            }

        }

        return ret;
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
            Vertex* pVertex = m_ajLinkList.get(i);

            if (pVertex->m_pVertexData)
            {
                value = *(pVertex->m_pVertexData);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No data assigned to the vertex ...");
            }
        }

        return ret;
    }

    bool removeVertex()
    {
        bool ret = false;

        if (m_ajLinkList.length() > 0)
        {
            int index = m_ajLinkList.length() - 1;
            Vertex* pVertex = m_ajLinkList.get(index);

            if (m_ajLinkList.remove(index))
            {
                for (int i = (m_ajLinkList.move(0), 0); !m_ajLinkList.end(); m_ajLinkList.next(), i++)
                {
                    int pos = ((m_ajLinkList.current())->edge).find(Edge(i, index)) ||
                              ((m_ajLinkList.current())->edge).find(Edge(index, i));

                    if (pos >= 0)
                    {
                        ((m_ajLinkList.current())->edge).remove(pos);
                    }
                }

                delete pVertex->m_pVertexData;
                delete pVertex;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current LinkListGraph ...");
        }

        return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* pRet = nullptr;

        if ((0 <= i) && (i < this->vertexCount()))
        {
            int vertexCount = 0;
            Vertex* pVertex = m_ajLinkList.get(i);

            if (pVertex)
            {
                pRet = new DynamicArray<int>(vertexCount);

                if (pRet)
                {
                    for (int j = ((pVertex->edge).move(0), 0); j < (pVertex->edge).length(); (pVertex->edge).next(), j++)
                    {
                        pRet->set(j, (pVertex->edge).current().endVertex);
                    }

                    if (!pRet->length())
                    {
                        cout << "Vertex(" << i <<  ") is not adjacent Vertex" << endl;
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return pRet;
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
            Vertex* pVertex = m_ajLinkList.get(i);
            int pos = (pVertex->edge).find(Edge(i, j));

            if (pos >= 0)
            {
                value = (pVertex->edge).get(pos).weight;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "This edge(i, j) is not exist ...");
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
            Vertex* pVertex = m_ajLinkList.get(i);
            int pos = (pVertex->edge).find(Edge(i, j));

            if (pos >= 0)
            {
                ret = (pVertex->edge).set(pos, Edge(i, j, value));
            }
            else
            {
                ret = (pVertex->edge).insert(0, Edge(i ,j, value));
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
            Vertex* pVertex = m_ajLinkList.get(i);
            int pos = (pVertex->edge).find(Edge(i, j));

            if (pos >= 0)
            {
                ret = (pVertex->edge).remove(pos);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "This edge(i, j) is not exist ...");
            }
        }

        return ret;
    }


    int vertexCount()
    {
        return m_ajLinkList.length();
    }

    int edgeCount()
    {
        int ret = 0;

        for (m_ajLinkList.move(0); !m_ajLinkList.end(); m_ajLinkList.next())
        {
            ret += (m_ajLinkList.current())->edge.length();
        }

        return ret;
    }

    int outDegree(int i)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= vertexCount()) )
        {
            Vertex* pVertex = m_ajLinkList.get(i);
            ret = (pVertex->edge).length();
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
            for (int j = (m_ajLinkList.move(0), 0); !m_ajLinkList.end(); m_ajLinkList.next(), j++)
            {
                LinkList<Edge>& edge = (m_ajLinkList.current())->edge;

                for (edge.move(0); !(edge.end()); edge.next())
                {
                    if (edge.current().endVertx == i)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    ~LinkListGraph()
    {
        while (m_ajLinkList.length() > 0)
        {
            Vertex* pToDel = m_ajLinkList.get(0);

            m_ajLinkList.remove(0);

            delete pToDel->m_pVertexData;
            delete pToDel;

            pToDel->m_pVertexData = nullptr;
            pToDel = nullptr;
        }
    }
};

}


#endif // LINKLISTGRAPH_H
