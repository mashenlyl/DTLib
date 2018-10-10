#ifndef STACK_H
#define STACK_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Stack : public Object
{
public:
    virtual void clear() = 0;
    virtual void push(const T& obj) = 0;
    virtual void pop() = 0;
    virtual T top() = 0;
    virtual int size() = 0;
};

}

#endif // STACK_H
