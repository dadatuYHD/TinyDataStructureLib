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
#include "List/StaticLinkList.h"
#include "List/LinkList.h"

using namespace std;
using namespace DTLib;

int main(void)
{
    StaticLinkList<int, 10> list;

    for (int i = 0; i < 10; i++)
    {
        list.insert(0, i);
    }

    for (list.move(0); !list.end(); list.next())
    {
        cout << list.current() << endl;
    }

    return 0;
 }
