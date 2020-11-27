#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception/Exception.h"

namespace MyTiny_DSLib {

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;
public:
    StaticStack(void)
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity(void) const
    {
        return N;
    }

    void push(const T& e)
    {
        if (m_size < N)
        {
            m_space[m_top + 1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }
    void pop(void)
    {
        if (m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }
    T top(void) const
    {
        if (m_top > -1 && m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element to get at in current stack top ...");
        }
    }
    void clear(void)
    {
        m_size = 0;
        m_top = -1;
    }
    int size(void) const
    {
        return m_size;
    }
};

}

#endif // STATICSTACK_H
