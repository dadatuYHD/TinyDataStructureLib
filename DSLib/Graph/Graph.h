#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "Object/Object.h"
#include "SmartPointer/SharedPointer.h"
#include "Exception/Exception.h"
#include "Array/DynamicArray.h"
#include "List/LinkList.h"
#include "Queue/LinkQueue.h"
#include "Stack/LinkStack.h"
#include "Exception/Exception.h"



namespace DSLib { 

#define INF 1 << 20

template <typename W>
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

template <typename V, typename W>
class Graph: public Object
{
protected:
    template <typename T>
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* pArray = new DynamicArray<T>(queue.length());

        if (pArray)
        {
            for (int i = 0; i < pArray->length(); i++, queue.remove())
            {
                pArray->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray ...");
        }

        return pArray;
    }

    void depthFirstSearch(Graph<V, W>& graph, int startVertex, Array<bool>& isVisted)
    {
        if ( (0 <= startVertex) && (startVertex < vertexCount()) )
        {
            if (!isVisted[startVertex])
            {
                cout << startVertex << endl;

                isVisted[startVertex] = true;

                SharedPointer< Array<int> > pAdjacent = graph.getAdjacent(startVertex);

                for (int i = 0; i < pAdjacent->length(); i++)
                {
                    if (!isVisted[(*pAdjacent)[i]])
                    {
                        depthFirstSearch(graph, (*pAdjacent)[i], isVisted);
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Index startVertex is invalid ...");
        }
    }

public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual bool isAdjacent(int i, int j) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
    virtual W getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, W& value) = 0;
    virtual bool setEdge(int i, int j, const W& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vertexCount() = 0;
    virtual int edgeCount() = 0;
    virtual int outDegree(int i) = 0;
    virtual int inDegree(int i) = 0;

    /********************************
     *   the degree of the vertex
     *******************************/
    virtual int TDegree(int i)
    {
        return outDegree(i) + inDegree(i);
    }

    /*************************************************
     *   judge the directed graph wheahter can as the
     *    undirected graph
     *************************************************/
    bool asUndirected(void)
    {
        bool ret = false;

        for (int i = 0; i < vertexCount(); i++)
        {
            for (int j = 0; j < vertexCount(); j++)
            {
                if (isAdjacent(i, j))
                {
                    ret = isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    /***********************************************
     *   the traverse algorrithm of Graph as follow
     ***********************************************/

    SharedPointer< Array<int> > breadthFirstSearch(int startVertex)
    {
        DynamicArray<int>* ret = nullptr;

        if ( (0 <= startVertex) && (startVertex < vertexCount()) )
        {
            LinkQueue<int> openList;
            LinkQueue<int> closeList;
            DynamicArray<bool> isVisted(vertexCount());

            for (int i = 0; i < isVisted.length(); i++)
            {
                isVisted[i] = false;
            }

            openList.add(startVertex);

            while (openList.length() > 0)
            {
                int value = openList.front();

                openList.remove();

                if (!isVisted[value])
                {
                    SharedPointer< Array<int> > pAdjacent = getAdjacent(value);

                    for (int i = 0; i < pAdjacent->length(); i++)
                    {
                        openList.add((*pAdjacent)[i]);
                    }

                    closeList.add(value);
                    isVisted[value] = true;
                }
            }

            ret = toArray(closeList);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Index start is invalid ...");
        }

        return ret;
    }

    SharedPointer< Array<int> > depthFirstSearch(int startVertex)
    {
        DynamicArray<int>* ret = nullptr;

        if ( (0 <= startVertex) && (startVertex < vertexCount()) )
        {
            LinkStack<int> openList;
            LinkQueue<int> closeList;
            DynamicArray<bool> isVisted(vertexCount());

            for (int i = 0; i < isVisted.length(); i++)
            {
                isVisted[i] = false;
            }

            openList.push(startVertex);

            while (openList.size() > 0)
            {
                int value = openList.top();

                openList.pop();

                if (!isVisted[value])
                {
                    SharedPointer< Array<int> > pAdjacent = getAdjacent(value);

                    for (int i = pAdjacent->length() - 1; i >= 0 ; i--)
                    {
                        openList.push((*pAdjacent)[i]);
                    }

                    closeList.add(value);
                    isVisted[value] = true;
                }
            }

            ret = toArray(closeList);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Index start is invalid ...");
        }

        return ret;
    }



    void depthFirstSearch(Graph<V, W>& graph, int startVertex)
    {
        DynamicArray<bool> isVisted(vertexCount());

        for (int i = 0; i < isVisted.length(); i++)
        {
            isVisted[i] = false;
        }

        depthFirstSearch(graph, startVertex, isVisted);
    }

    SharedPointer< Array< Edge<W> > > prim()
    {
        LinkQueue< Edge<W> > retEdge;

        if (asUndirected())
        {
            DynamicArray<bool> mark(vertexCount());
            DynamicArray<W> cost(vertexCount());
            DynamicArray<int> adjVex(vertexCount());
            int startVertex = 0;
            bool end = false;

            for (int i = 0; i < mark.length(); i++)
            {
                mark[i]   = false;
                cost[i]   = INF;
                adjVex[i] = -1;
            }

            mark[startVertex] = true;
            SharedPointer< Array<int> > pArray = getAdjacent(startVertex);

            for (int i = 0; i < pArray->length(); i++)
            {
                cost[(*pArray)[i]] = getEdge(startVertex, (*pArray)[i]);
                adjVex[(*pArray)[i]] = startVertex;
            }

            for (int i = 0; (i < vertexCount()) && !end; i++)
            {
                W edgeWeight = INF;
                int vertexIndex = -1;

                for (int j = 0; j < vertexCount(); j++)
                {
                    if (!mark[j] && (cost[j] < edgeWeight))
                    {
                        edgeWeight = cost[j];
                        vertexIndex = j;
                    }
                }

                end = (vertexIndex == -1);

                if (!end)
                {
                    retEdge.add( Edge<W>(adjVex[vertexIndex], vertexIndex, getEdge(adjVex[vertexIndex], vertexIndex)) );

                    mark[vertexIndex] = true;

                    pArray = getAdjacent(vertexIndex);

                    for (int i = 0; i < pArray->length(); i++)
                    {
                        if ( (!mark[(*pArray)[i]]) && (getEdge(vertexIndex, (*pArray)[i]) < cost[(*pArray)[i]]) )
                        {
                            cost[(*pArray)[i]] = getEdge(vertexIndex, (*pArray)[i]);
                            adjVex[(*pArray)[i]] = vertexIndex;
                        }
                    }
                }
            }

            if (retEdge.length() != (vertexCount() - 1))
            {
                THROW_EXCEPTION(InvalidOperationException, "No enough edge for prim operation ...");
            }

            return toArray(retEdge);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undirected graph only ...");
        }
    }
};

}

#endif // GRAPH_H
