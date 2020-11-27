#ifndef STATICSEQLIST_H
#define STATICSEQLIST_H

#include "SeqList.h"

namespace MyTiny_DSLib {

template <typename T, int N>
class StaticSeqList : public SeqList<T>
{
protected:
    T m_space[N];        //Sequential storage space, the N is Template parameter
public:
    StaticSeqList()
    {
        this->m_array = m_space;
        this->m_length = 0;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif // STATICSEQLIST_H
