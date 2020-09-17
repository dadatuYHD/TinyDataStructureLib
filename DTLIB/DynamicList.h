#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;      //Sequential storage space size
public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if (this->m_array != nullptr)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }
    //Reset the Sequential storage space size
    int capacity() const
    {
        return m_capacity;
    }
    void resize(int capacity)
    {
        T * array = new T[capacity];

        if (nullptr != array)
        {
            int length = (this->m_length > capacity ? capacity : this->m_length);

            for (int i = 0; i < length; i++)
            {
                array[i] = this->m_array[i];
            }

            T * temp = this->m_array;

            this->m_array = array;
            this->m_capacity = capacity;
            this->m_length = length;

            delete [] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }
    ~DynamicList()
    {
        delete [] this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
