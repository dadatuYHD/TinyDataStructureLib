#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreedNode.h"

namespace DSLib {

template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T> * m_left;
    BTreeNode<T> * m_right;

    BTreeNode()
    {
        m_left = nullptr;
        m_right = nullptr;
    }

    static BTreeNode<T> * NewNode(void)
    {
        BTreeNode<T> * ret = new BTreeNode<T>();

        if (ret)
        {
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // BTREENODE_H
