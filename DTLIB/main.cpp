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
    StaticList<int, 5> s1;

    for (int i = 0; i < s1.capacity(); i++)
    {
        s1[i] = i * i;
    }

    return 0;
}
