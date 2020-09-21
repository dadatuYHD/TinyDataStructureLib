#ifndef LIST_H
#define LIST_H

#include "Object/Object.h"

namespace DTLib {

template <typename T>
class List : public Object
{
protected:
    //Prohibit copy constructors and assignment overloaded functions
    List(const List &);
    List& operator = (const List &);
public:
    List() {};
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};

}


#endif // LIST_H
