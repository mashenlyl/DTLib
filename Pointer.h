/*
 * 指针类，继承自Object，如果不实现析构函数，是不能作为抽象类的。
 */

#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }

    T* operator ->()
    {
        return m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    const T* operator ->() const
    {
        return m_pointer;
    }

    const T& operator *() const
    {
        return *m_pointer;
    }

    bool isNULL() const
    {
        return (m_pointer == NULL);
    }

    T* get() const
    {
        return m_pointer;
    }

};

}

#endif // POINTER_H
