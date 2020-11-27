#ifndef STACKTOQUEUE_H
#define STACKTOQUEUE_H

#include "Queue.h"
#include "Stack/LinkStack.h"
#include "Exception/Exception.h"

namespace MyTiny_DSLib {

template <typename T>
class StackToQueue : public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;

    void StackinToStackout(void) const
    {
        if (m_stack_out.size() == 0)
        {
            while (m_stack_in.size() > 0)
            {
                m_stack_out.push(m_stack_in.top());
                m_stack_in.pop();
            }
        }
    }

public:
    void add(const T& e)
    {
        m_stack_in.push(e);
    }

    void remove()
    {
        StackinToStackout();

        if (m_stack_out.size() > 0)
        {
            m_stack_out.pop();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const
    {
        StackinToStackout();

        if (m_stack_out.size() > 0)
        {
            return m_stack_out.top();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }

    int length() const
    {
        return m_stack_in.size() + m_stack_out.size();
    }
};

}

#endif // STACKTOQUEUE_H
