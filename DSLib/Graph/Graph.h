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
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
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
};

}

#endif // GRAPH_H
