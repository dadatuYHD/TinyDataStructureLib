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
    };

    struct Vertex : public Object
    {
        V* m_pVertex;            /*storage the vertex value */
        LinkList< Edge > edge;   /*the edge which adjacent the vertex*/

        Vertex()
        {
            m_pVertex = nullptr;
        }
    };

    LinkList<Vertex*> m_ajLinkList;
public:
    LinkListGraph(unsigned int num = 0)
    {

    }

    int addVertex(void)
    {
        int ret = -1;

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = -1;

        return ret;
    }
};

}


#endif // LINKLISTGRAPH_H
