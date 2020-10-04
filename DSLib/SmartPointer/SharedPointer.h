#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "SmartPointer/Pointer.h"
#include <cstdlib>
#include "Exception/Exception.h"

using namespace std;

namespace DSLib {

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int * m_ref;
    void assign(const SharedPointer<T>& obj)
    {
        m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if (m_ref)
        {
            (*m_ref)++;
        }
    }
public:
    SharedPointer(T * p = nullptr) : m_ref(nullptr)
    {
        if (p)
        {
            m_ref = static_cast<int *>(malloc(sizeof(int)));
            if (m_ref)
            {
                *m_ref = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(nullptr)
    {
        assign(obj);
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if (*this != obj)
        {
            clear();

            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        T * toDel = this->m_pointer;
        int * ref = m_ref;

        this->m_pointer = nullptr;
        m_ref = nullptr;

        if (ref)
        {
            (*ref)--;

            if (*ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator == (const SharedPointer<T>&l, const SharedPointer<T>&r)
{
    return (l.getptr() == r.getptr());
}

template <typename T>
bool operator != (const SharedPointer<T>&l, const SharedPointer<T>&r)
{
    return !(l == r);
}

}



#endif // SHAREDPOINTER_H
