#ifndef TREEDNODE_H
#define TREEDNODE_H

#include "Object/Object.h"

namespace MyTiny_DSLib
{

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;

    void * operator new (unsigned long long  size) throw()
    {
        return Object::operator new(size);
    }

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator = (const TreeNode<T>&);

public:
    T value;
    TreeNode<T> * parent;

    TreeNode()
    {
        parent = nullptr;
        m_flag = false;
    }

    bool getFlag(void)
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREEDNODE_H
