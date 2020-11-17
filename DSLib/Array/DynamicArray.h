#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception/Exception.h"

namespace DSLib {

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T * copy(T * array, int len, int newlen)
    {
        T * ret = new T[newlen];

        if (nullptr != ret)
        {
            int size = (newlen > len) ? len : newlen;

            for (int i = 0; i < size; i++ )
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int len)
    {
        if (nullptr != array)
        {
            T * temp = this->m_array;

            this->m_array = array;
            this->m_length = len;

            delete [] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray pbject ...");
        }
    }

    void init(T * array, int len)
    {
        if (nullptr != array)
        {
            this->m_array = array;
            this->m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray pbject ...");
        }
    }
public:
    DynamicArray()
    {

    }
    DynamicArray(int length)
    {
        init(new T[length], length);
    }
    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }
    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if (this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length)
    {
        if (m_length != length)
        {
            update(copy(this->m_array, this->m_length, length), length);
        }
    }

    ~DynamicArray()
    {
        delete [] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
