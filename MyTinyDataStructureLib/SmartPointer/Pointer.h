#ifndef POINTER_H
#define POINTER_H

#include "Object/Object.h"

namespace MyTiny_DSLib {

template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = nullptr)
    {
        m_pointer = p;
    }

    T* operator -> (void)
    {
        return m_pointer;
    }

    T& operator * (void)
    {
        return *m_pointer;
    }

    T* operator -> (void) const
    {
        return m_pointer;
    }

    T& operator * (void) const
    {
        return *m_pointer;
    }

    bool isNull(void) const
    {
        return (m_pointer == nullptr);
    }

    T* getptr(void) const
    {
        return m_pointer;
    }
};

}

#endif // POINTER_H
