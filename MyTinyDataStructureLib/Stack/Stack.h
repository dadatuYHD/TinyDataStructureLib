#ifndef STACK_H
#define STACK_H

#include "Object/Object.h"

namespace MyTiny_DSLib {

template <typename T>
class Stack : public Object
{
public:
    virtual void push(const T& e) = 0;
    virtual void pop(void) = 0;
    virtual T top(void) const = 0;
    virtual void clear(void) = 0;
    virtual int size(void) const = 0;
};

}

#endif // STACK_H
