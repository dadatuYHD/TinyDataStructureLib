#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception/Exception.h"
#include <iostream>

namespace DSLib {

template <typename T>
class GTree : public Tree<T>
{
protected:
    GTreeNode<T> * find(GTreeNode<T> * node, const T& value) const
    {
        GTreeNode<T> * ret =nullptr;

        if (node != nullptr)
        {
            if (node->value == value)
            {
                return node;
            }
            else
            {
                for (node->child.move(0);  !(node->child.end()) && (ret == nullptr); node->child.next())
                {
                    ret = find((node->child).current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T> * find(GTreeNode<T> * node, GTreeNode<T> * obj) const
    {
        GTreeNode<T> * ret =nullptr;

        if (node == obj)
        {
            return node;
        }
        else
        {
            if (node != nullptr)
            {
                for (node->child.move(0);  !(node->child.end()) && (ret == nullptr); node->child.next())
                {
                    ret = find((node->child).current(), obj);
                }
            }
        }

        return ret;
    }

    void free(GTreeNode<T> * root)
    {
        if (root != nullptr)
        {
            for (root->child.move(0); !root->child.end(); root->child.next())
            {
                free(root->child.current());
            }

            if (root->getFlag())
            {
                delete root;
            }
            else
            {
                cout << root->value << endl;
            }
        }
    }

public:
    bool insert(TreeNode<T> * node)
    {
        bool ret = true;

        if (node != nullptr)
        {
            if (this->m_root == nullptr)
            {
                node->parent = nullptr;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T> * currentNodeParent = find(node->parent);

                if (currentNodeParent != nullptr)
                {
                    if (currentNodeParent->child.find(dynamic_cast<GTreeNode<T> *>(node)) < 0)
                    {
                        currentNodeParent->child.insert(dynamic_cast<GTreeNode<T> *>(node));
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Parameter node->parent is invalid ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T> * parent)
    {
        bool ret = true;
        GTreeNode<T> * node = GTreeNode<T>::NewNode();

        if (node != nullptr)
        {
            node->value = value;
            node->parent = parent;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node to insert ...");
        }


        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        SharedPointer< Tree<T> > s;

        return s;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T> * node)
    {
        SharedPointer< Tree<T> > s;

        return s;
    }

    GTreeNode<T> * find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T> * find(TreeNode<T> * node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T> *>(node));
    }

    GTreeNode<T> * root() const
    {
        return dynamic_cast<GTreeNode<T> *>(this->m_root);
    }

    int degree() const
    {
        return 1;
    }

    int count() const
    {
        return 1;
    }

    int height() const
    {
        return 1;
    }

    void clear()
    {
        free(root());

        this->m_root = nullptr;
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
