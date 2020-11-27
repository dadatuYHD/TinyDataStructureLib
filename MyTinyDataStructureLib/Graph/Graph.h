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
#include "Algorithm/Sort.h"



namespace MyTiny_DSLib { 

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

    bool operator > (const Edge& obj)
    {
        return (weight > obj.weight);
    }

    bool operator >= (const Edge& obj)
    {
        return (weight >= obj.weight);
    }

    bool operator < (const Edge& obj)
    {
        return (weight < obj.weight);
    }

    bool operator <= (const Edge& obj)
    {
        return (weight <= obj.weight);
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

    SharedPointer< Array<Edge<W>> > getUndirectedGraphEdges(void)
    {
        DynamicArray< Edge<W> >* ret = nullptr;

        if (asUndirected())
        {
            LinkQueue< Edge<W> > queue;

            for (int i = 0; i < vertexCount(); i++)
            {
                for (int j = 0; j < vertexCount(); j++)
                {
                    if (isAdjacent(i, j))
                    {
                        queue.add(Edge<W>(i, j, getEdge(i, j)));
                    }
                }
            }

            ret = toArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "This function is for undirected graph ...");
        }

        return ret;
    }

    int find(Array<int>& pre, int v)
    {
        while (-1 != pre[v])
        {
            v = pre[v];
        }

        return v;
    }

    bool isOpenListNull(DynamicArray<bool>& openList)
    {
        int count = 0;
        bool ret = true;

        for (int i = 0; i < openList.length(); i++)
        {
            if (openList[i] == true)
            {
                count++;
            }
        }

        if (count)
        {
            ret = false;
        }

        return ret;
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

    SharedPointer< Array< Edge<W> > > kruskal(void)
    {
        LinkQueue< Edge<W> > ret;
        SharedPointer< Array<Edge<W>> > edges = getUndirectedGraphEdges();
        DynamicArray<int> pre(vertexCount());

        for (int i = 0; i < pre.length(); i++)
        {
            pre[i] = -1;
        }

        Sort::shell(*edges);

        for ( int i = 0; (i < edges->length()) && (ret.length() < (vertexCount() - 1)); i++)
        {
            int startVertex = find(pre, (*edges)[i].startVertex);
            int endVertex = find(pre, (*edges)[i].endVertex);

            if (startVertex != endVertex)
            {
                pre[startVertex] = endVertex;

                ret.add((*edges)[i]);
            }
        }

        if ((ret.length()) != (vertexCount() - 1))
        {
            THROW_EXCEPTION(InvalidOperationException, "kruskal operation is invalid ...");
        }


        return toArray(ret);
    }

    SharedPointer< Array<int> > djikstra(int startVertex, int endVertex)
    {
        LinkQueue<int> ret;

        if ( (0 <= startVertex) && (startVertex < vertexCount()) &&
             (0 <= endVertex)   && (endVertex   < vertexCount()) )
        {
            DynamicArray<W>    weight(vertexCount());
            DynamicArray<bool> openList(vertexCount());
            DynamicArray<bool> closeList(vertexCount());
            DynamicArray<int> path(vertexCount());


            for (int i = 0; i < vertexCount(); i++)
            {
                openList[i] = false;
                closeList[i] = false;
                path[i] = -1;
                weight[i] = isAdjacent(startVertex, i) ? getEdge(startVertex, i) : INF;
            }

            openList[startVertex] = true;
            int tempVertex = startVertex;
            W weightValue = INF;
            int expectedVertex = -1;

            while (!isOpenListNull(openList))
            {
                openList[tempVertex] = false;
                closeList[tempVertex] = true;


                if (tempVertex == endVertex)
                {
                    break;
                }

                for (int i = 0; i < vertexCount(); i++)
                {
                    if (isAdjacent(tempVertex, i) && !closeList[i])
                    {
                        if ( (weight[i] == INF) || (weight[i] >= weight[tempVertex] + getEdge(tempVertex, i)) )
                        {
                            weight[i] = weight[tempVertex] + getEdge(tempVertex, i);
                            path[i] = tempVertex;
                        }

                        openList[i] = true;
                    }
                }

                weightValue = INF;
                for (int i = 0; i < vertexCount(); i++)
                {
                    if ((weight[i] < weightValue) && openList[i])
                    {
                        weightValue = weight[i];
                        expectedVertex = i;
                    }
                }

                if (-1 == expectedVertex)
                {
                    break;
                }

                tempVertex = expectedVertex;
            }

            LinkStack<int> stack;
            for (int i = endVertex; i != -1; i = path[i])
            {
                stack.push(i);
            }

            while (stack.size() > 0)
            {
                ret.add(stack.top());
                stack.pop();
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Index <start, end> is invalid ...");
        }

        if (ret.length() < 2)
        {
            THROW_EXCEPTION(ArithmeticException, "There is no path form start to end ");
        }

        return toArray(ret);
    }

    SharedPointer< Array<int> > floyd(int startVertex, int endVertex)
    {
        LinkQueue<int> ret;

        if ( (0 <= startVertex) && (startVertex < vertexCount()) &&
             (0 <= endVertex)   && (endVertex   < vertexCount()) )
        {
            DynamicArray< DynamicArray<W> > weight(vertexCount());
            DynamicArray< DynamicArray<int> > path(vertexCount());

            for (int i = 0; i < vertexCount(); i++)
            {
                weight[i].resize(vertexCount());
                path[i].resize(vertexCount());
            }

            for (int i = 0; i < vertexCount(); i++)
            {
                for (int j = 0; j < vertexCount(); j++)
                {
                    weight[i][j] = isAdjacent(i, j) ? getEdge(i, j) : INF;
                    path[i][j]   = isAdjacent(i, j) ? j : -1;
                }
            }

            for (int transitNode = 0; transitNode < vertexCount(); transitNode++)
            {
                for (int i = 0; i < vertexCount(); i++)
                {
                    for (int j = 0; j < vertexCount(); j++)
                    {
                        if ( weight[i][j] > (weight[i][transitNode] + weight[transitNode][j]) )
                        {
                            weight[i][j] = weight[i][transitNode] + weight[transitNode][j];
                            path[i][j]   = path[i][transitNode];
                        }
                    }
                }
            }

            while ((startVertex != -1) && (startVertex != endVertex))
            {
                ret.add(startVertex);
                startVertex = path[startVertex][endVertex];
            }

            if (startVertex != -1)
            {
                ret.add(startVertex);
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Index <start, end> is invalid ...");
        }

        if (ret.length() < 2)
        {
            THROW_EXCEPTION(ArithmeticException, "There is no path form start to end ");
        }

        return toArray(ret);
    }
};

}

#endif // GRAPH_H
