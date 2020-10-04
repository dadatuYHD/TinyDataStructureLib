#ifndef CIRCLELINKLIST_H
#define CIRCLELINKLIST_H

#include "LinkList.h"

namespace DSLib {

template <typename T>
class CircleLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    Node * last(void) const
    {
        return (this->position(this->length()));
    }

    void last_to_first(void) const
    {
        last()->next = this->m_header.next;
    }
public:
    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T&e)
    {
        bool ret = true;

        i = i % (this->m_length + 1);

        ret = LinkList<T>::insert(e, i);

        if (ret && (i == 0))
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = i % this->m_length;

        if (i == 0)
        {
            Node * toDel = this->m_header.next;

            if (toDel != nullptr)
            {
                this->m_header.next = toDel->next;
                this->m_length--;

                if (this->m_length > 0)
                {
                    last_to_first();

                    if (this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = nullptr;
                    this->m_current = nullptr;
                }

                this->destory(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }



};

}

#endif // CIRCLELINKLIST_H
