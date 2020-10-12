#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "List/LinuxList.h"
#include "Exception/Exception.h"

namespace DSLib {

template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    int m_length;
public:
    LinkQueue()
    {
        m_length = 0;

        INIT_LIST_HEAD(&m_header);
    }

    void add(const T& e)
    {
        Node * node = new Node();

        if (node)
        {
            node->value = e;

            list_add_tail(&node->head, &m_header);

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue ...");
        }
    }
    void remove()
    {
        if (m_length > 0)
        {
            list_head * toDel = m_header.next;

            list_del(toDel);

            m_length--;

            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }
    T front() const
    {
        if (m_length > 0)
        {
            return (list_entry(m_header.next, Node, head))->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }
    void clear()
    {
        while (m_length > 0)
        {
            remove();
        }
    }
    int length() const
    {
        return m_length;
    }

    ~LinkQueue()
    {
        clear();
    }

};

}

#endif // LINKQUEUE_H
