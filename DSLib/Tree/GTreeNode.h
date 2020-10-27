#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreedNode.h"
#include "List/LinkList.h"

namespace DSLib {

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList< GTreeNode<T *> > child;
};

}

#endif // GTREENODE_H
