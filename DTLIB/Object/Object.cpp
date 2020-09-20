/********************************************************
*   Copyright (C) 2020 All rights reserved.
*
*   Filename:Object.c
*   Author  :yhd
*   Date    :2020-09-16
*   Describe:
*
********************************************************/
#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace DTLib {

void * Object::operator new (unsigned long long size) throw()
{
    cout << "Object::operator new" << endl;
    return malloc(size);
}
void   Object::operator delete (void * p) throw()
{
    cout << "Object::operator delete" << endl;
    free(p);
}
void * Object::operator new[] (unsigned long long size) throw()
{
    cout << "Object::operator new[]" << endl;
    return malloc(size);
}
void   Object::operator delete[] (void * p) throw()
{
    cout << "Object::operator delete[]" << endl;
    free(p);
}

Object::~Object() {}

}
