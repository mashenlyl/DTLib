/*
 * 使用规定：(1)类型不能混用；(2)只能用于指向堆空间；(3)不需要手动释放空间
 */

#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include <cstdlib>
#include "Exception.h"

namespace DTLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;

    void assign(const SharedPointer& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if( this->m_ref )
        {
            (*this->m_ref)++;
        }
    }
public:
    SharedPointer(T* p = NULL) : m_ref(NULL)
    {
        if( p )
        {
            m_ref = static_cast<int*>(std::malloc(sizeof(int)));

            if( m_ref )
            {
                this->m_pointer = p;
                *m_ref = 1;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException");
            }
        }

    }

    SharedPointer(const SharedPointer& obj) : Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer& operator =(const SharedPointer& obj)
    {
        if( this != &obj )
        {
            clear();

            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        int* ref = m_ref;
        T* toDel = this->m_pointer;

        m_ref = NULL;
        this->m_pointer = NULL;

        if( ref )
        {
            (*ref)--;
            if( (*ref) == 0 )
            {
                free(ref);
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        this->clear();
    }
};

template < typename T >
bool operator ==(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template < typename T >
bool operator !=(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r);
}

}
#endif // SHAREDPOINTER_H
