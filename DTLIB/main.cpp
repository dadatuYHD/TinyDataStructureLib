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

using namespace std;
using namespace DTLib;

int main(void)
{
    DynamicArray<int> s1(5);

    for (int i = 0; i < s1.length(); i++)
    {
        s1[i] = i * i;
    }

    for (int i = 0; i < s1.length(); i++)
    {
        cout << s1[i] << endl;
    }



    return 0;
}
