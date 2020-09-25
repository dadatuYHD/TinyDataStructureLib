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

class Test : public Object
{
    int i;
public:
    Test(int v = 0)
    {
        i = v;
    }

    bool operator == (const Test &obj)
    {
        return (i == obj.i);
    }
};

int main(void)
{
    Test t1(1);
    Test t2(2);
    Test t3(3);
    Test t4(4);

    LinkList<Test> list;

    list.insert(t1);
    list.insert(t2);
    list.insert(t3);
    list.insert(t4);

    cout << list.find(t2) << endl;

    return 0;
 }
