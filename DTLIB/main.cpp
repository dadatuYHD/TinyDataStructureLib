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
#include "Array/DynamicArray.h"
#include "List/LinkList.h"
#include "Object/Object.h"

using namespace std;
using namespace DTLib;

int main(void)
{
    LinkList<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);


    for (list.move(0); !list.end(); list.next())
    {
        cout << list.current() << endl;
    }

    return 0;
 }
