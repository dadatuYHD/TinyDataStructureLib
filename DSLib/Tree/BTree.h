#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "Tree.h"
#include "BTreeNode.h"
#include "Exception/Exception.h"
#include "Queue/LinkQueue.h"
#include "Array/DynamicArray.h"

namespace DSLib {

enum BtNodePos
{
    ANY,
    LEFT,
    RIGHT,
};

enum BTTraversal
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
};

template <typename T>
class BTree : public Tree<T>
{
protected:

    LinkQueue< BTreeNode<T> *> m_queue;

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

        return ret;
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

            //cout << node->value << endl;

            if (node->getFlag())
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T> * node) const
    {
        return ((node != nullptr) ? (count(node->m_left) + count(node->m_right) + 1) : 0);
    }

    int height(BTreeNode<T> * node) const
    {
        return ((node != nullptr) ? ((height(node->m_left) > height(node->m_right)) ? height(node->m_left) + 1 : height(node->m_right) + 1) : 0);
    }

    int degree(BTreeNode<T> * node) const
    {
        int ret = 0;

        if (node)
        {
            BTreeNode<T> * child[] = {node->m_left, node->m_right};
            ret = !!(node->m_left) + !!(node->m_right);

            for (int i = 0; i < 2 && (ret < 2); i++)
            {
                int d = degree(child[i]);

                if (ret < d) ret = d;
            }
        }

        return ret;
    }

    void PreOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            queue.add(node);
            PreOrderTraversal(node->m_left, queue);
            PreOrderTraversal(node->m_right, queue);
        }
    }

    void InOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            InOrderTraversal(node->m_left, queue);
            queue.add(node);
            InOrderTraversal(node->m_right, queue);
        }
    }

    void PostOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            PostOrderTraversal(node->m_left, queue);
            PostOrderTraversal(node->m_right, queue);
            queue.add(node);
        }
    }

    BTreeNode<T> * clone(BTreeNode<T> * node) const
    {
        BTreeNode<T> * pNode = nullptr;

        if (node)
        {
            pNode = BTreeNode<T>::NewNode();

            if (pNode)
            {
                pNode->value = node->value;
                pNode->m_left = clone(node->m_left);
                pNode->m_right = clone(node->m_right);

                if (pNode->m_left)
                {
                    pNode->m_left->parent = pNode;
                }

                if (pNode->m_right)
                {
                    pNode->m_right->parent = pNode;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BTreeNode ...");
            }
        }

        return pNode;
    }

    bool isEqual(BTreeNode<T> * lNode, BTreeNode<T> * rNode) const
    {
        bool ret = false;

        if (lNode == rNode)
        {
            ret = true;
        }
        else if ((lNode != nullptr) && (rNode != nullptr))
        {
            return ((lNode->value == rNode->value) && (isEqual(lNode->m_left, rNode->m_left))
                                                   && (isEqual(lNode->m_right, rNode->m_right)));
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    BTreeNode<T> * add(BTreeNode<T> * lNode, BTreeNode<T> * rNode) const
    {
        BTreeNode<T> * ret = nullptr;

        if ((lNode == nullptr) && (rNode != nullptr))
        {
            ret = clone(rNode);
        }
        else if ((lNode != nullptr) && (rNode == nullptr))
        {
            ret = clone(lNode);
        }
        else if ((lNode != nullptr) && (rNode != nullptr))
        {
            ret = BTreeNode<T>::NewNode();

            if (ret)
            {
                ret->value = lNode->value + rNode->value;
                ret->m_left = add(lNode->m_left, rNode->m_left);
                ret->m_right = add(lNode->m_right, rNode->m_right);

                if (ret->m_left) ret->m_left->parent = ret;
                if (ret->m_right) ret->m_right->parent = ret;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BTreeNode ...");
            }
        }
        else
        {
            //occupied the blank
        }

        return ret;
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
            m_queue.clear();
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

            m_queue.clear();
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
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        m_queue.clear();

        this->m_root = nullptr;
    }

    //level traverse the BTree
    bool begin()
    {
        bool ret = (root() != nullptr);

        if (ret)
        {
            m_queue.clear();

            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if (ret)
        {
            BTreeNode<T> * node = m_queue.front();

            m_queue.remove();

            if (node->m_left) m_queue.add(node->m_left);
            if (node->m_right) m_queue.add(node->m_right);
        }

        return ret;
    }

    T current()
    {
        if (!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No tree node at current position");
        }
    }

    /*
     *
     *  traversal by preorder inorder and postorder
     *
     */

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T> * ret = nullptr;
        LinkQueue<BTreeNode<T> *> queue;

        switch (order)
        {
            case PRE_ORDER:
                PreOrderTraversal(root(), queue);
                break;
            case IN_ORDER:
                InOrderTraversal(root(), queue);
                break;
            case POST_ORDER:
                PostOrderTraversal(root(), queue);
                break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
                break;
        }

        ret = new DynamicArray<T>(queue.length());

        if (ret)
        {
            for (int i = 0; i < ret->length(); i++)
            {
                (*ret)[i] = (queue.front())->value;
                queue.remove();
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create dynamicarray ...");
        }

        return ret;
    }

    /*************************************
     *
     *       clone the binary tree
     *
     *************************************/

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T> * ret = new BTree<T>();

        if (ret)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BTree ...");
        }

        return ret;
    }

    /*********************************
     *
     *    compare the binary tree
     *
     *********************************/
    bool operator == (const BTree<T>& btree)
    {
        return isEqual(root(), btree.root());
    }

    bool operator != (const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    /*********************************
     *
     *    the operator add of binary tree
     *
     *********************************/
    SharedPointer< BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T> * ret = new BTree();

        if (ret)
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BTree ...");
        }

        return ret;
    }


    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
