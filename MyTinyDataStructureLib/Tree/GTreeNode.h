#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreedNode.h"
#include "List/LinkList.h"

namespace MyTiny_DSLib {

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList< GTreeNode<T> * > child;

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
