#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"

namespace DSLib {

template <typename T>
class GTree : public Tree<T>
{
public:
    bool insert(TreeNode<T> * node)
    {}

    bool insert(const T& value, TreeNode<T> * parent)
    {}

    SharedPointer< Tree<T> > remove(const T& value)
    {}

    SharedPointer< Tree<T> > remove(TreeNode<T> * node)
    {}

    GTreeNode<T> * find(const T& value) const
    {}

    GTreeNode<T> * find(TreeNode<T> * node) const
    {}

    GTreeNode<T> * root() const
    {}

    int degree() const
    {}

    int count() const
    {}

    int height() const
    {}

    void clear()
    {}

    ~GTree()
    {}
};

}

#endif // GTREE_H
