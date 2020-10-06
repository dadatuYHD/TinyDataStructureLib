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
    //josephus(41, 1, 3);
    DualLinkList<int> dl;

    for (int i = 0; i < 5; i++)
    {
        dl.insert(0, i);
        dl.insert(0, 4);
    }

    for (dl.move(0); !dl.end(); dl.next())
    {
        cout << dl.current() << endl;
    }

    cout << "begin" << endl;

    dl.move(dl.length() - 1);

    while (!dl.end())
    {
        if (dl.current() == 4)
        {
            cout << dl.current() << endl;

            dl.remove(dl.find(dl.current()));
        }
        else
        {
            dl.pre();
        }
    }

    cout << "end" << endl;

    for (dl.move(0); !dl.end(); dl.next())
    {
        cout << dl.current() << endl;
    }

    return 0;
 }
