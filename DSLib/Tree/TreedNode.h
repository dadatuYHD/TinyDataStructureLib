#ifndef TREEDNODE_H
#define TREEDNODE_H

#include "Object/Object.h"

namespace DSLib
{

template <typename T>
class TreeNode : public Object
{
public:
    T value;
    TreeNode<T> * parent;

    TreeNode()
    {
        parent = nullptr;
    }

    virtual ~TreeNode() = 0;
};

}

#endif // TREEDNODE_H
