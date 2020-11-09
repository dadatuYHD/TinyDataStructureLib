#ifndef GRAPH_H
#define GRAPH_H

#include "Object/Object.h"
#include "SmartPointer/SharedPointer.h"
#include "Array/DynamicArray.h"


namespace DSLib {

template <typename V, typename W>
class Graph: public Object
{
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
};

}

#endif // GRAPH_H
