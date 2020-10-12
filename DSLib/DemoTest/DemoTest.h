#ifndef DEMOTEST_H
#define DEMOTEST_H

#include <iostream>
#include "List/CircleLinkList.h"
#include "List/DualLinkList.h"
#include "List/LinuxList.h"
#include "List/DualCircleLinkList.h"
#include "Stack/StaticStack.h"
#include "Queue/StaticQueue.h"
#include "Queue/LinkQueue.h"

namespace DSLib {

void josephus(int n, int s, int m);
void linux_list_demo1(void);
void linux_list_demo2(void);
void DualCircleLinkList_Demo(void);
void StaticStack_Demo(void);
void StaticQueue_Demo(void);
void LinkQueue_Demo(void);

}

using namespace std;
using namespace DSLib;

#endif // DEMOTEST_H
