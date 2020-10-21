#include "DemoTest.h"
#include <iostream>

using namespace std;

namespace DSLib {

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

void linux_list_demo1(void)
{
    struct Node
    {
        struct list_head head;
        int value;
    };

    struct Node l = {0};

    struct list_head * list = (struct list_head *)&l;
    struct list_head * slider = nullptr;


    INIT_LIST_HEAD(list);

    cout << "insert start ..." << endl;

    for (int i = 0; i < 5; i++)
    {
        struct Node * n = (struct Node *)malloc(sizeof(struct Node));

        n->value = i;

        list_add_tail((struct list_head *)n, list);
    }

    list_for_each(slider, list)
    {
        cout << ((struct Node *)slider)->value << endl;
    }

    cout << "insert end ..." << endl;
}

void linux_list_demo2(void)
{
    struct Node
    {
        int value;
        struct list_head head;
    };

    struct Node l = {0};

    struct list_head * list = &l.head;
    struct list_head * slider = nullptr;


    INIT_LIST_HEAD(list);

    cout << "insert start ..." << endl;

    for (int i = 0; i < 5; i++)
    {
        struct Node * n = (struct Node *)malloc(sizeof(struct Node));

        n->value = i;

        list_add_tail(&n->head, list);
    }

    list_for_each(slider, list)
    {
        cout << list_entry(slider, struct Node, head)->value << endl;
    }

    cout << "insert end ..." << endl;
}

void DualCircleLinkList_Demo(void)
{
    DualCircleLinkList<int> Dc;

    for (int i = 0; i < 10; i++)
    {
        Dc.insert(0, i);
        Dc.insert(0, 5);
    }

    cout << "begin" << endl;

    Dc.move(Dc.length() - 1);

    while (Dc.find(5) != -1)
    {
        if (Dc.current() == 5)
        {
            cout << Dc.current() << endl;

            Dc.remove(Dc.find(Dc.current()));
        }
        else
        {
            Dc.pre();
        }
    }

    cout << "end" << endl;

    for (int i = 0; i < Dc.length(); i++)
    {
        cout << Dc.get(i) << endl;
    }
}

void Stack_Demo(void)
{
    QueueToStack<int> qts;

    for (int i = 0; i < 10; i++)
    {
        qts.push(i);
        cout << qts.top() << endl;
    }

    for (int i = 0; i < 10; i++)
    {
        cout << qts.top() << endl;
        qts.pop();
    }
}

void Queue_Demo(void)
{
    StackToQueue<int> stq;

    for (int i = 0; i < 10; i++)
    {
        stq.add(i);
    }

    while (stq.length() > 0)
    {
        cout << stq.front() << endl;

        stq.remove();
    }
}

void DString_Demo(void)
{
    DString s = "test yhd!";

    s.SubString(3,20);

    cout << s.SubString(3,20).str() << endl;
}

void linklist_reverse(void)
{
    LinkList<int> list;
    LinkListAlgorithm<int> listAlgorithm;

    for (int i = 0; i < 10; i++)
    {
        list.insert(i);
    }

    for (int i = 0; i < list.length(); i++)
    {
        cout << list.get(i) << "->";
    }
    cout << "nullptr" << endl;

    cout << "reverse the linklist" << endl;

    (list.GetHeaderNode())->next = listAlgorithm.reverse((list.GetHeaderNode())->next);

    for (int i = 0; i < list.length(); i++)
    {
        cout << list.get(i) << "->";
    }
    cout << "nullptr" << endl;
}

void linklist_merge(void)
{
    LinkList<int> list;
    LinkList<int> list1;
    LinkList<int> list2;
    LinkListAlgorithm<int> listAlgorithm;

    for (int i = 0; i <= 10; i++, i++)
    {
        list1.insert(i);
    }

    for (int i = 0; i < list1.length(); i++)
    {
        cout << list1.get(i) << "->";
    }
    cout << "nullptr" << endl;

    for (int i = 1; i <= 11; i++, i++)
    {
        list2.insert(i);
    }

    for (int i = 0; i < list2.length(); i++)
    {
        cout << list2.get(i) << "->";
    }
    cout << "nullptr" << endl;

    cout << "merge list1 and list2" << endl;

    list.GetHeaderNode()->next =  listAlgorithm.merge(list1.GetHeaderNode()->next, list2.GetHeaderNode()->next);
    *(list.GetLength()) = list1.length() + list2.length();

    for (int i = 0; i < list.length(); i++)
    {
        cout << list.get(i) << "->";
    }

    cout << "nullptr" << endl;
}

void linklist_demo(void)
{
    linklist_merge();
}

}
