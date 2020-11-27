#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "List/LinkList.h"
#include "Exception/Exception.h"

namespace MyTiny_DSLib {

template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;
public:
    void push(const T& e)
    {
        m_list.insert(0, e);
    }

    void pop(void)
    {
        if (m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top(void) const
    {
        if (m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }
    void clear(void)
    {
        m_list.clear();
    }
    int size(void) const
    {
        return m_list.length();
    }
};

}

#endif // LINKSTACK_H
