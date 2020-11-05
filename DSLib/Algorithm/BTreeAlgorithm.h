#ifndef BTREEALGORITHM_H
#define BTREEALGORITHM_H

#include "Tree/BTree.h"

namespace DSLib {

enum BTTraversal
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER,
};

template <typename T>
class BTreeAlgorithm : public Object
{
protected:
    static void PreOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            queue.add(node);
            PreOrderTraversal(node->m_left, queue);
            PreOrderTraversal(node->m_right, queue);
        }
    }

    static void InOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            InOrderTraversal(node->m_left, queue);
            queue.add(node);
            InOrderTraversal(node->m_right, queue);
        }
    }

    static void PostOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            PostOrderTraversal(node->m_left, queue);
            PostOrderTraversal(node->m_right, queue);
            queue.add(node);
        }
    }

    static void LevelOrderTraversal(BTreeNode<T> * node, LinkQueue< BTreeNode<T> * >& queue)
    {
        if (node)
        {
            LinkQueue< BTreeNode<T> * >tmp;

            tmp.add(node);

            while (tmp.length() > 0)
            {
                BTreeNode<T> * node = tmp.front();

                if (node->m_left)  tmp.add(node->m_left);
                if (node->m_right) tmp.add(node->m_right);

                tmp.remove();
                queue.add(node);
            }
        }
    }
public:
    /****************************************************************
     * Description    :delete the node which the degree is one,
     *                 and the btree node has parent pointer
     * Arg1[In][node] :root node of the binary tree
     * return         :root node of the binary tree which is deleted
     ****************************************************************/
    static BTreeNode<T> * delOneDeg(BTreeNode<T> * node)
    {
         BTreeNode<T> * ret = nullptr;

        if (node)
        {
            if (((node->m_left != nullptr) && (node->m_right == nullptr)) ||
               ((node->m_left == nullptr) && (node->m_right != nullptr)))
            {
                BTreeNode<T> * parent = dynamic_cast<BTreeNode<T> *>(node->parent);
                BTreeNode<T> * nodeChild = (node->m_left ? node->m_left : node->m_right);

                if (parent)
                {
                    (parent->m_left == node) ? (parent->m_left = nodeChild) : (parent->m_right = nodeChild);
                }

                nodeChild->parent = parent;

                if (node->getFlag()) delete node;

                ret = delOneDeg(nodeChild);
            }
            else
            {
                delOneDeg(node->m_left);
                delOneDeg(node->m_right);

                ret = node;
            }
        }

        return ret;
    }

    /****************************************************************
     * Description    :delete the node which the degree is one,
     *                 and the btree node has not parent pointer
     * Arg1[In][node] :root node of the binary tree
     * return         :root node of the binary tree which is deleted
     ****************************************************************/
    static void delOneDeg2(BTreeNode<T> * & node)
    {
        if (node)
        {
            if (((node->m_left != nullptr) && (node->m_right == nullptr)) ||
               ((node->m_left == nullptr) && (node->m_right != nullptr)))
            {
                BTreeNode<T> * nodeChild = (node->m_left ? node->m_left : node->m_right);

                if (node->getFlag()) delete node;

                node = nodeChild;

                delOneDeg(node);
            }
            else
            {
                delOneDeg(node->m_left);
                delOneDeg(node->m_right);
            }
        }
    }

    /****************************************************************
     * Description    :according the arg order traverse the btree and
     *                 storage the btree node address to the queue
     * Arg1[In][node] :root node of the binary tree
     * Arg2[In][order]:binary tree traverse order
     * Arg3[In][queue]:storage the node address
     ****************************************************************/
    static void traversal(BTreeNode<T> * node, BTTraversal order, LinkQueue<BTreeNode<T> *>& queue)
    {
        switch (order)
        {
            case PRE_ORDER:
                PreOrderTraversal(node, queue);
                break;
            case IN_ORDER:
                InOrderTraversal(node, queue);
                break;
            case POST_ORDER:
                PostOrderTraversal(node, queue);
                break;
            case LEVEL_ORDER:
                LevelOrderTraversal(node, queue);
                break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
                break;
        }
    }

    /*****************************************************************
     * Description    :according the arg order traverse the btree
     * Arg1[In][node] :root node of the binary tree
     * Arg2[In][order]:binary tree traverse order
     * return         :The array which storaged btree node address
     *****************************************************************/
    static SharedPointer< Array<T> > traversal(BTreeNode<T> * node, BTTraversal order)
    {
        DynamicArray<T> * ret = nullptr;
        LinkQueue<BTreeNode<T> *> queue;

        traversal(node, order, queue);

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
};

}


#endif // BTREEALGORITHM_H
