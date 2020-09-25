#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception/Exception.h"

namespace DTLib {

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node * next;
    };

    //mutable Node m_header;
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node * next;
    } m_header;
    int m_length;
    Node * position(int i) const
    {
        Node * ret = reinterpret_cast<Node *>(&m_header);

        for (int p = 0; p < i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }
public:
    LinkList()
    {
        m_header.next = nullptr;
        m_length = 0;
    }

    bool insert(const T& e)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if (ret)
        {
            Node * node = new Node();

            if (nullptr != node)
            {
                node->value = e;
                node->next = position(i)->next;
                position(i)->next = node;

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element");
            }
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            Node * toDel = position(i)->next;

            position(i)->next = toDel->next;
            toDel->next = nullptr;

            delete toDel;

            m_length--;
        }

        return ret;
    }
    bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    T get(int i)
    {
        T ret;

        if (get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
        }
    }

    bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            e = position(i)->next->value;
        }

        return ret;
    }
    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        Node * node = m_header.next;

        while (node)
        {
            if (node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                i++;
                node = node->next;
            }
        }

        return ret;
    }
    int length() const
    {
        return m_length;
    }
    void clear()
    {
        while (m_header.next)
        {
            Node * toDel = m_header.next;

            m_header.next = toDel->next;

            delete toDel;
            m_length--;
        }
    }

    ~LinkList()
    {
        clear();
    }
};

}


#endif // LINKLIST_H
