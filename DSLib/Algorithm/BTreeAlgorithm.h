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

enum BTDataStructual
{
    USE_DataStructual,
    NOT_USE_DataStructual,
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

    /****************************************************************
     *Description:connect the btree node in the queue to dual linklist
     *Arg[In][queue]:storage the btree node
     *return:The first node address of dual linklist
     ****************************************************************/
    static BTreeNode<T> * connect(LinkQueue< BTreeNode<T> * >& queue)
    {
        BTreeNode<T> * ret = nullptr;

        if (queue.length() > 0)
        {
            ret = queue.front();

            BTreeNode<T> * slider = queue.front();
            queue.remove();
            slider->m_left = nullptr;

            while (queue.length() > 0)
            {
                slider->parent = nullptr;
                slider->m_right = queue.front();
                (queue.front())->m_left = slider;
                slider = queue.front();
                queue.remove();
            }
            slider->m_right = nullptr;
        }

        return ret;
    }

    static void PreOrderTraversal(BTreeNode<T> * node, BTreeNode<T> * &preNode, BTreeNode<T> * &leftNode)
    {
//        if (node)
//        {
//            leftNode = node->m_left;
//            node->m_left = preNode;

//            if (preNode)
//            {
//                preNode->m_right = node;
//            }

//            preNode = node;

//            PreOrderTraversal(leftNode, preNode, leftNode);
//            PreOrderTraversal(node->m_right, preNode, leftNode);

//            node->m_left = nullptr;
//        }
    }

    static void InOrderTraversal(BTreeNode<T> * node, BTreeNode<T> * &preNode)
    {
        if (node)
        {
            InOrderTraversal(node->m_left, preNode);
            node->m_left = preNode;

            if (preNode)
            {
                preNode->m_right = node;
            }

            preNode = node;

            InOrderTraversal(node->m_right, preNode);
        }
    }

    static void InOrderTraversal(BTreeNode<T> * node, BTreeNode<T> * &head, BTreeNode<T> * &tail)
    {

        if (node)
        {
            BTreeNode<T> * h = nullptr;
            BTreeNode<T> * t = nullptr;

            InOrderTraversal(node->m_left, h, t);

            node->m_left = t;
            if (t) t->m_right = node;
            head = h ? h : node;
            head->m_left = nullptr;

            h = nullptr;
            t = nullptr;

            InOrderTraversal(node->m_right, h, t);

            node->m_right = h;
            if (h) h->m_left = node;
            tail = t ? t : node;
            tail->m_right = nullptr;
        }
    }

    static void PostOrderTraversal(BTreeNode<T> * node, BTreeNode<T> * &preNode)
    {
//        if (node)
//        {
//            PostOrderTraversal(node->m_left, preNode);
//            PostOrderTraversal(node->m_right, preNode);

//            node->m_left = preNode;

//            if (preNode)
//            {
//                preNode->m_right = node;
//            }

//            preNode = node;

//        }
    }

    /*****************************************************************
     * Description    :according the arg order traverse and thread the btree
     * Arg1[In][node] :root node of the binary tree
     * Arg2[In][order]:binary tree traverse order
     *****************************************************************/
    static void traversalByPre(BTreeNode<T> * &node, BTTraversal order)
    {
        BTreeNode<T> * preNode = nullptr;
        BTreeNode<T> * tempNode = nullptr;
        BTreeNode<T> * headNode = nullptr;
        BTreeNode<T> * tailNode = nullptr;


        switch (order)
        {
            case PRE_ORDER:
                PreOrderTraversal(node, preNode, tempNode);
                break;
            case IN_ORDER:
#define USE_TWO 1
#if USE_TWO
                InOrderTraversal(node, headNode, tailNode);
                node = tailNode;
#else
                InOrderTraversal(node, preNode);
#endif
                break;
            case POST_ORDER:
                PostOrderTraversal(node, preNode);
                break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
                break;
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

    /*****************************************************************
     * Description    :Use the queue as auxiliary data_structure to
     *                 thread the binary tree
     * Arg1[In][node] :root node of the binary tree
     * Arg2[In][order]:binary tree traverse order
     * return         :The first node address of the dual linklist
     *****************************************************************/

    static BTreeNode<T> * thread(BTreeNode<T> * node, BTTraversal order, BTDataStructual useDataStructure)
    {
        BTreeNode<T> * firstNode = nullptr;

        if (useDataStructure == USE_DataStructual)
        {
            LinkQueue< BTreeNode<T> * > queue;

            BTreeAlgorithm<T>::traversal(node, order, queue);

            firstNode = connect(queue);
        }
        else
        {
            BTreeAlgorithm<T>::traversalByPre(node, order);  //only IN_ORDER can run

            firstNode = node;

            //while ((firstNode) && (firstNode->m_left != nullptr)) firstNode = firstNode->m_left;
        }

        return firstNode;
    }
};

}


#endif // BTREEALGORITHM_H
