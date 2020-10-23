#ifndef LINKLISTALGORITHM_H
#define LINKLISTALGORITHM_H

#include "List/LinkList.h"
#include <iostream>

using namespace std;

namespace DSLib
{

template <typename T>
class LinkListAlgorithm : public LinkList<T>
{
private:
    typedef typename LinkList<T>::Node Node;
    LinkListAlgorithm();
    LinkListAlgorithm(const LinkListAlgorithm&);
    LinkListAlgorithm& operator = (const LinkListAlgorithm&);
public:
    /************************************************************
     ****************linklist about operation*********************
     ***********************************************************/

    /************************************************************
     * FUNCTION:reverse()
     * Description:By recursive algorithm to reverse the single linklist
     * Arguments[list][In]:the address of the first node
     * return:the address of the first node
     * *********************************************************/
    static Node * reverse(Node * list)
    {
        if ((list == nullptr) || (list->next == nullptr))
        {
            return list;
        }
        else
        {
            Node * current = list->next;
            Node * ret = reverse(list->next);
            current->next = list;
            list->next = nullptr;

            return ret;
        }
    }

    /************************************************************
     * FUNCTION:merge()
     * Description:By recursive algorithm to merge two singly linklist in ascending order
     * Arguments[list1 list2][In]:the address of the first node
     * return:the address of the first node
     * *********************************************************/
    static Node * merge(Node * list1, Node * list2)
    {
        if ((list1 == nullptr))
        {
            return list2;
        }
        else if (list2 == nullptr)
        {
            return list1;
        }
        else if (list1->value < list2->value)
        {
            return (list1->next = merge(list1->next, list2), list1);
        }
        else
        {
            return (list2->next = merge(list2->next, list1), list2);
        }
    }

    /************************************************************
     * FUNCTION:ReversePrint()
     * Description:By Recursive algorithm to reverse print the
     * node of  single link list
     * Arguments[list][In]:the address of the first node
     * return:void
     * *********************************************************/
    static void ReversePrint(Node * list)
    {
        if (list != nullptr)
        {
            ReversePrint(list->next);

            cout << list->value << endl;
        }
    }

};

}



#endif // LINKLISTALGORITHM_H
