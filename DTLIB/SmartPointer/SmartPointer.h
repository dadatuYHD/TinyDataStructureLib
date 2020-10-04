#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "SmartPointer/Pointer.h"

namespace DTLib {

template <typename T>
class SmartPointer : public Pointer<T>
{
protected:
    T* m_pointer;
public:
    SmartPointer(T* p = nullptr) : Pointer<T>(p)
    {}

    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
    }

    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if (this != &obj)
        {
            T * p = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;

            delete p;
        }

        return *this;
    }

    ~SmartPointer(void)
    {
        delete m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
