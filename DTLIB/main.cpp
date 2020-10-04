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
#include "Object/Object.h"
#include "SmartPointer/SharedPointer.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int value;

    Test(int p) : value(p)
    {
        cout << "Test(int p)" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }

};

int main(void)
{
    SharedPointer<Test> p1 = new Test(1);
    SharedPointer<Test> p2(p1);
    SharedPointer<Test> p3 = nullptr;

    p3 = p2;

    p3->value = 98;

    cout << p1->value << endl;
    cout << p2->value << endl;
    cout << p3->value << endl;

    p2.clear();

    cout << (p1 == p2) << endl;


    return 0;
 }
