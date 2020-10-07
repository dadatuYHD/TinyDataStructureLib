/********************************************************
*   Copyright (C) 2020 All rights reserved.
*
*   Filename:main.c
*   Author  :yhd
*   Date    :2020-09-16
*   Describe:
*
********************************************************/

#include <iostream>
#include "List/CircleLinkList.h"
#include "List/DualLinkList.h"
#include "List/LinuxList.h"

struct Node
{
    struct list_head head;
    int type;
};

using namespace std;
using namespace DSLib;

void josephus(int n, int s, int m)
{
    CircleLinkList<int> cl;

    for (int i = 1; i <= n; i++)
    {
        cl.insert(i);
    }

    cl.move(s - 1, m - 1);

    while (cl.length() > 0)
    {
        cl.next();

        cout << cl.current() << endl;

        cl.remove(cl.find(cl.current()));
    }
}

int main(void)
{
    struct Node l = {0};

    struct list_head * list = (struct list_head *)&l;

    INIT_LIST_HEAD(list);

    return 0;
 }
