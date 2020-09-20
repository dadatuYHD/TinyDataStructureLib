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
#include "SmartPointer/SmartPointer.h"
#include "Exception/Exception.h"
#include "List/StaticList.h"
#include "List/DynamicList.h"

using namespace std;
using namespace DTLib;

int main(void)
{
    DynamicList<int> l(5);

    for (int i = 0; i < l.capacity(); i++)
    {
        l.insert(0, i);
    }

    for (int i = 0; i < l.length(); i++)
    {
        l[i] *= l[i];
    }

    for (int i = 0; i < l.length(); i++)
    {
        cout << l[i] << endl;
    }



    return 0;
}
