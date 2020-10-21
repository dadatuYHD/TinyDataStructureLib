#ifndef LINKLISTALGORITHM_H
#define LINKLISTALGORITHM_H

#include "List/LinkList.h"

namespace DSLib
{

template <typename T>
class LinkListAlgorithm : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
public:
    /*
     *linklist some operation
    */

    //Recursion递归
    Node * reverse(Node * list)
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

    Node * merge(Node * list1, Node * list2)
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
};

}



#endif // LINKLISTALGORITHM_H
