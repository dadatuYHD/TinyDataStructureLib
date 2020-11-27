#ifndef CIRCLELINKLIST_H
#define CIRCLELINKLIST_H

#include "LinkList.h"

namespace MyTiny_DSLib {

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

    int mod(int i) const
    {
        return (i % this->m_length);
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

        ret = LinkList<T>::insert(i, e);

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

    bool set(int i, const T& e)
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i, T& e) const
    {
        return LinkList<T>::get(i, e);
    }

    int find(const T& e) const
    {
        int ret = -1;
        Node * slider = this->m_header.next;

        for (int i = 0; i < this->m_length; i++)
        {
            if (slider->value == e)
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear()
    {
        while (this->m_length > 1)
        {
            remove(1);
        }

        if (this->m_length == 1)
        {
            Node * toDel = this->m_header.next;

            this->m_header.next = nullptr;
            this->m_length = 0;
            this->m_current = nullptr;

            this->destory(toDel);
        }
    }

    bool move(int i, int step)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return ((this->m_current == nullptr) || (this->m_length == 0));
    }

    ~CircleLinkList()
    {
        clear();
    }

};

}

#endif // CIRCLELINKLIST_H
