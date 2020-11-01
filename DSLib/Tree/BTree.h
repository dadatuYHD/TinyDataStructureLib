#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "Tree.h"
#include "BTreeNode.h"
#include "Exception/Exception.h"
#include "Queue/LinkQueue.h"

namespace DSLib {

enum BtNodePos
{
    ANY,
    LEFT,
    RIGHT,
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    virtual BTreeNode<T> * find(BTreeNode<T> * node, const T& value) const
    {
        BTreeNode<T> * ret = nullptr;

        if (node)
        {
            if (node->value == value)
            {
                return ret = node;
            }
            else
            {
                if (ret == nullptr)
                {
                    ret = find(node->m_left, value);
                }

                if (ret == nullptr)
                {
                    ret = find(node->m_right, value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T> * find(BTreeNode<T> * node, BTreeNode<T> * obj) const
    {
        BTreeNode<T> * ret = nullptr;

        if (node)
        {
            if (node == obj)
            {
                return ret = node;
            }
            else
            {
                if (ret == nullptr)
                {
                    ret = find(node->m_left, obj);
                }

                if (ret == nullptr)
                {
                    ret = find(node->m_right, obj);
                }
            }
        }

        return ret;
    }

    virtual bool insert(BTreeNode<T> * node, BTreeNode<T> * nodeParent, BtNodePos pos)
    {
        bool ret = true;

        if (pos == LEFT)
        {
            if (nodeParent->m_left == nullptr)
            {
                nodeParent->m_left = node;
            }
            else
            {
                ret =false;
            }
        }
        else if (pos == RIGHT)
        {
            if (nodeParent->m_right == nullptr)
            {
                nodeParent->m_right = node;
            }
            else
            {
                ret =false;
            }
        }
        else if (pos == ANY)
        {
            if (nodeParent->m_left == nullptr)
            {
                nodeParent->m_left = node;
            }
            else if (nodeParent->m_right == nullptr)
            {
                nodeParent->m_right = node;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter pos is invalid ...");
        }
    }

    virtual void remove(BTreeNode<T> * node, BTree<T> *& ret)
    {
        ret = new BTree<T>();

        if (ret)
        {
            if (node)
            {
                if (node == root())
                {
                    this->m_root = nullptr;
                }
                else
                {
                    BTreeNode<T> * nodeParent = dynamic_cast<BTreeNode<T> *>(node->parent);

                    if (nodeParent->m_left == node)
                    {
                        nodeParent->m_left = nullptr;
                    }
                    else if (nodeParent->m_right == node)
                    {
                        nodeParent->m_right = nullptr;
                    }
                    else
                    {
                        //occupied the position
                    }
                    node->parent = nullptr;
                }

                ret->m_root = node;
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Parameter node id invalid ...");
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        if (node)
        {
            free(node->m_left);
            free(node->m_right);

            cout << node->value << endl;

            if (node->getFlag())
            {
                delete node;
            }
        }
    }

public:

    virtual bool insert(TreeNode<T> * node, BtNodePos pos)
    {
        bool ret = true;

        if (node)
        {
            if (this->m_root == nullptr)
            {
                this->m_root = node;
                node->parent = nullptr;
            }
            else
            {
                BTreeNode<T> * nodeParent = find(node->parent);

                if (nodeParent)
                {
                    insert(dynamic_cast<BTreeNode<T> *>(node), nodeParent, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent btree node");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node can not be nullptr ...");
        }

        return ret;
    }

    virtual bool insert(const T& value, TreeNode<T> * parent, BtNodePos pos)
    {
        BTreeNode<T> * node = BTreeNode<T>::NewNode();
        bool ret = true;

        if (node)
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);
            if (ret == false)
            {
                delete node;
            }

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BTreeNode ...");
        }
    }

    bool insert(TreeNode<T> * node)
    {
        return insert(node, ANY);
    }

    bool insert(const T& value, TreeNode<T> * parent)
    {
        return insert(value, parent, ANY);
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T> * ret = nullptr;
        BTreeNode<T> * node = find(value);

        if (node)
        {
            remove(node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T> * node)
    {
        BTree<T> * ret = nullptr;

        node = find(node);

        if (node)
        {
            remove(dynamic_cast<BTreeNode<T> *>(node), ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    BTreeNode<T> * find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T> * find(TreeNode<T> * node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T> *>(node));
    }

    BTreeNode<T> * root() const
    {
        return dynamic_cast<BTreeNode<T> *>(this->m_root);
    }

    int degree() const
    {

    }

    int count() const
    {

    }

    int height() const
    {

    }

    void clear()
    {
        free(root());

        this->m_root = nullptr;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
