#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreedNode.h"
#include "List/LinkList.h"

namespace DSLib {

template <typename T>
class GTreeNode : public TreeNode<T>
{
protected:
    bool m_flag;

    void * operator new (unsigned long long  size) throw()
    {
        return Object::operator new(size);
    }

public:
    LinkList< GTreeNode<T> * > child;

    GTreeNode()
    {
        m_flag = false;
    }

    bool getFlag(void)
    {
        return m_flag;
    }

    static GTreeNode<T> * NewNode(void)
    {
        GTreeNode<T> * ret = new GTreeNode<T>();

        if (ret)
        {
            ret->m_flag = true;
        }

        return ret;
    }



};

}

#endif // GTREENODE_H
