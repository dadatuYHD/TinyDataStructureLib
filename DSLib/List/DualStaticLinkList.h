#ifndef DUALSTATICLINKLIST_H
#define DUALSTATICLINKLIST_H

#include "List/DualLinkList.h"

namespace DSLib {

template <typename T, int N>
class DualStaticLinkList : public DualLinkList<T>
{
protected:
    typedef typename DualLinkList<T>::Node Node;

    struct SNode : public Node
    {
        void * operator new (unsigned long long size, void *loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];



    Node * create()
    {
        SNode * ret = nullptr;

        for (int i = 0; i < N; i++)
        {
            if (!m_used[i])
            {
                ret = reinterpret_cast<SNode *>(m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void destory(Node * ptr)
    {
        SNode * space = reinterpret_cast<SNode *>(m_space);
        SNode * psn = dynamic_cast<SNode *>(ptr);

        for (int i = 0; i < N; i++)
        {
            if (psn == (space + i))
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }
public:
    DualStaticLinkList()
    {
        for (int i = 0; i < N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    ~DualStaticLinkList()
    {
        this->clear();
    }
};

}

#endif // DUALSTATICLINKLIST_H
