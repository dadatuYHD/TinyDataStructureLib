#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H

#include "Graph/LinkListGraph.h"

namespace DSLib {

class GraphAlgorithm : public Object
{
protected:
    static int searchMaxLocalPath(Graph<int, int>& graph, int value, Array<int>& count, Array<int>& path, Array<bool>& mark)
    {
        int ret = 0;
        int localMaxVertex = -1;
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
                localMaxVertex = (*pAdjacent)[i];
            }
        }

        ret++;

        count[value] = ret;
        mark[value]  = true;
        path[value]  = localMaxVertex;

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

    static void initArray(Array<int>& count, Array<int>& path, Array<bool>& mark)
    {
        for (int i = 0; i < count.length(); i++)
        {
            count[i] = 0;
        }

        for (int i = 0; i < path.length(); i++)
        {
            path[i] = -1;
        }

        for (int i = 0; i < mark.length(); i++)
        {
            mark[i] = false;
        }
    }

    static void printMaxPath(SharedPointer< Graph<int, int> >& graph, Array<int>& count, Array<int>& path)
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
            if (maxSeqNum == count[i])
            {
                cout << "globalMaxVertex : " << graph->getVertex(i) << endl;
                cout << "global the longest not descending sequence : " << graph->getVertex(i) << "-->";

                for (int j = path[i]; j != -1; j = path[j])
                {
                    cout << graph->getVertex(j) << "-->";
                }

                cout << "null" << endl;
                cout << endl;
            }
        }
    }

    static void searchMaxLocalPath(Graph<int, int>& graph, Array<int>& count, Array<int>& path, Array<bool>& mark)
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
        DynamicArray<int> path(len);
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
