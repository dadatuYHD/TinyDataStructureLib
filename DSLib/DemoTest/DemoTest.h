#ifndef DEMOTEST_H
#define DEMOTEST_H

#include "List/CircleLinkList.h"
#include "List/DualLinkList.h"
#include "List/LinuxList.h"
#include "List/DualCircleLinkList.h"
#include <iostream>

namespace DSLib {

void josephus(int n, int s, int m);
void linux_list_demo1(void);
void linux_list_demo2(void);
void DualCircleLinkList_Demo(void);
}

using namespace std;
using namespace DSLib;

#endif // DEMOTEST_H
