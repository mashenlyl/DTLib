#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Queue : public Object
{
public:
    virtual void clear() = 0;
    virtual void add(const T& obj) = 0;
    virtual void remove() = 0;
    virtual T front() = 0;
    virtual int length() = 0;
};

}

#endif // QUEUE_H
