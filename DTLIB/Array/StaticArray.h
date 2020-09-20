#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace DTLib {

template <typename T, int N>
class StaticAarray : public Array<T>
{
protected:
    T m_space[N];
public:
    StaticAarray()
    {
        this->m_array = m_space;
    }

    StaticAarray(const StaticAarray<T, N>& obj)
    {
        this->m_array = m_space;

        for (int i = 0; i < N; i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }

    StaticAarray<T, N>& operator= (const StaticAarray<T, N>& obj)
    {
        if (this != &obj)
        {
             for (int i = 0; i < N; i++)
             {
                 m_space[i] = obj.m_space[i];
             }
        }

        return *this;
    }

    int length() const
    {
        return N;
    }
};

}

#endif // STATICARRAY_H
