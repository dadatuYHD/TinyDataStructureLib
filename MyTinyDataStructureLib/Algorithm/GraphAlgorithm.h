#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H

#include "Graph/LinkListGraph.h"

namespace MyTiny_DSLib {

class GraphAlgorithm : public Object
{
protected:
    static int searchMaxLocalPath(Graph<int, int>& graph, int value, Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
    {
        int ret = 0;
        SharedPointer< Array<int> > pAdjacent = graph.getAdjacent(value);

        for (int i = 0; i < pAdjacent->length(); i++)
        {
            int localMaxVertexNum = 0;

            if ( !mark[(*pAdjacent)[i]] )
            {
                localMaxVertexNum = searchMaxLocalPath(graph, (*pAdjacent)[i], count, path, mark);
            }
            else
            {
                localMaxVertexNum = count[(*pAdjacent)[i]];
            }

            if (ret < localMaxVertexNum)
            {
                ret = localMaxVertexNum;
            }
        }

        for (int i = 0; i < pAdjacent->length(); i++)
        {
            if (ret == count[(*pAdjacent)[i]])
            {
                path[value]->insert((*pAdjacent)[i]);
            }
        }

        ret++;

        count[value] = ret;
        mark[value]  = true;

        return ret;
    }

    static SharedPointer< Graph<int, int> > createGraph(int* pSeq, int len)
    {
        SharedPointer< Graph<int, int> > pRet = new LinkListGraph<int, int>(len);

        for (int i = 0; i < len; i++)
        {
            pRet->setVertex(i, pSeq[i]);
        }

        for (int i = 0; i < len; i++)
        {
            for (int j = i + 1; j < len; j++)
            {
                if (pSeq[i] <= pSeq[j])
                {
                    pRet->setEdge(i, j, 1);
                }
            }
        }

        return pRet;
    }

    static void initArray(Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
    {
        for (int i = 0; i < count.length(); i++)
        {
            count[i] = 0;
        }

        for (int i = 0; i < path.length(); i++)
        {
            path[i] = new LinkList<int>();
        }

        for (int i = 0; i < mark.length(); i++)
        {
            mark[i] = false;
        }
    }

    static void printPath(SharedPointer< Graph<int, int> >& graph, int value, Array< LinkList<int>* >& path, LinkList<int>& cp)
    {
        cp.insert(value);

        if (path[value]->length() > 0)
        {
            for (path[value]->move(0); !path[value]->end(); path[value]->next())
            {
                printPath(graph, path[value]->current(), path, cp);
            }
        }
        else
        {
            cout << "Element : ";
            for (cp.move(0); !cp.end(); cp.next())
            {
                cout << graph->getVertex(cp.current()) << " ";
            }

            cout << endl;
        }

        cp.remove(cp.length() - 1);
    }

    static void printMaxPath(SharedPointer< Graph<int, int> >& graph, Array<int>& count, Array< LinkList<int>* >& path)
    {
        int maxSeqNum = 0;

        for (int i = 0; i < count.length(); i++)
        {
            if (maxSeqNum < count[i])
            {
                maxSeqNum = count[i];
            }
        }

        cout << "globalMaxVertexNum : " << maxSeqNum << endl;

        for (int i = 0; i < count.length(); i++)
        {
            LinkList<int> cp;

            if (maxSeqNum == count[i])
            {
                printPath(graph, i, path, cp);
            }
        }
    }

    static void searchMaxLocalPath(Graph<int, int>& graph, Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
    {
        for (int i = 0; i < graph.vertexCount(); i++)
        {
            if (!mark[i])
            {
                searchMaxLocalPath(graph, i, count, path, mark);
            }
        }
    }

public:
    static void noDscendingSeq(int* pSeq, int len)
    {
        DynamicArray<int> count(len);
        DynamicArray< LinkList<int>* > path(len);
        DynamicArray<bool> mark(len);
        SharedPointer< Graph<int, int> > graph;

        graph = createGraph(pSeq, len);

        initArray(count, path, mark);

        searchMaxLocalPath((*graph), count, path, mark);

        printMaxPath(graph, count, path);
    }

};

}

#endif // GRAPHALGORITHM_H
