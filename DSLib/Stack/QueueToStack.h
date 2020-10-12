#ifndef QUEUETOSTACK_H
#define QUEUETOSTACK_H

#include "Stack.h"
#include "Queue/LinkQueue.h"
#include "Exception/Exception.h"

namespace DSLib {

template <typename T>
class QueueToStack : public Stack<T>
{
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T> * m_pIn;
    LinkQueue<T> * m_pOut;

    void move(void) const
    {
        while (m_pIn->length() > 1)
        {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }

    void swap(void)
    {
        LinkQueue<T> * temp = nullptr;

        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }

public:
    QueueToStack()
    {
        m_pIn  = &m_queue_1;
        m_pOut = &m_queue_2;
    }

    void push(const T& e)
    {
        m_pIn->add(e);
    }

    void pop(void)
    {
        if (m_pIn->length() > 0)
        {
            move();

            m_pIn->remove();

            swap();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top(void) const
    {
        if (m_pIn->length() > 0)
        {
            move();

            return m_pIn->front();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear(void)
    {
        m_queue_1.clear();
        m_queue_2.clear();
    }

    int size(void) const
    {
        return m_queue_1.length() + m_queue_2.length();
    }
};

}

#endif // QUEUETOSTACK_H
