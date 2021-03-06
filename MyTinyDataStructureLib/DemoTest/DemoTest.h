#ifndef DEMOTEST_H
#define DEMOTEST_H

#include "List/CircleLinkList.h"
#include "List/DualLinkList.h"
#include "List/LinuxList.h"
#include "List/DualCircleLinkList.h"
#include "Stack/StaticStack.h"
#include "Stack/QueueToStack.h"
#include "Queue/StaticQueue.h"
#include "Queue/LinkQueue.h"
#include "Queue/StackToQueue.h"
#include "DString/DString.h"
#include "Algorithm/LinkListAlgorithm.h"
#include "Algorithm/Recursion.h"
#include "Algorithm/QueueSolution.h"
#include "Algorithm/Sort.h"
#include "Algorithm/GraphAlgorithm.h"
#include "Array/DynamicArray.h"
#include "Array/StaticArray.h"
#include "Tree/GTree.h"
#include "Tree/BTree.h"
#include "Graph/MatrixGraph.h"
#include "Graph/LinkListGraph.h"



namespace MyTiny_DSLib {

void josephus(int n, int s, int m);
void linux_list_demo1(void);
void linux_list_demo2(void);
void DualCircleLinkList_Demo(void);
void Stack_Demo(void);
void Queue_Demo(void);
void DString_Demo(void);
void linklist_demo(void);
void HanoiTower_demo(void);
void permutation_demo(void);
void QueueSolution_demo(void);
void Sort_demo(void);
void gtree_demo(void);
void btree_demo(void);
void btree_demo2(void);
void btreeAlgorithm_demo(void);
void MatrixGraph_demo1(void);
void LinkListGraph_demo(void);
void GraphAlgorithm_demo(void);

}


#endif // DEMOTEST_H
