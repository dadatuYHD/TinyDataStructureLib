#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception/Exception.h"

namespace DSLib {

template <typename T>
class SeqList : public List<T>
{
protected:
    T * m_array;           //Sequential storage space
    int m_length;          //Sequential storage space size
public:
    bool insert(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i <= m_length));

        ret = ret && (m_length < capacity());

        if (ret)
        {
            if (m_length == 0)
            {
                m_array[0] = e;
            }
            else
            {
                for (int p = m_length - 1; p >= i; p--)
                {
                    m_array[p + 1] = m_array[p];
                }

                m_array[i] = e;
            }

            m_length++;
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if (ret)
        {
            for (int p = i; p < m_length - 1; p++)
            {
                m_array[p] = m_array[p + 1];
            }

            m_length--;
        }

        return m_length;
    }
    bool set(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if (ret)
        {
            m_array[i] = e;
        }

        return ret;
    }
    bool get(int i, T& e) const
    {
        bool ret = ((i >= 0) && (i < m_length));

        if (ret)
        {
            e = m_array[i];
        }

        return ret;
    }
    int find(const T& e) const
    {
        int ret = -1;

        for (int i = 0; i < m_length; i++)
        {
            if (m_array[i] == e)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

    int length() const
    {
        return m_length;
    }
    void clear()
    {
        m_length = 0;
    }

    //Access sequential storage space by array
    T& operator [] (int i)
    {
        if ((i >= 0) && (i < m_length))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }
    T  operator [] (int i) const
    {
        return (const_cast<SeqList<T>&>(*this))[i];
    }

    //Sequential storage capacity limit
    virtual int capacity() const = 0;
};

}

#endif // SEQLIST_H
