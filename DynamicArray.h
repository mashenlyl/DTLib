/*
 * 代码优化：因为存在很多的重复的逻辑，所以需要对代码进行优化；
 * 一般优化的办法就是，保证每个函数足够的小，只干一件事；
 * init()对对象进行初始化操作，update()更新成员变量的值，copy()进行值的复制
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    void init(T* array, int len)
    {
        if( array != NULL)
        {
            this->m_array = array;
            this->m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException");
        }
    }
    T* copy(T* array, int len, int Newlen)
    {
        T* d_array = new T[Newlen];

        if( d_array != NULL)
        {
            int length = len < Newlen ? len : Newlen;
            for(int i=0; i<length; i++)
            {
                d_array[i] = array[i];
            }
        }
        return d_array;
    }
    void update(T* array, int len)
    {
        if( array != NULL)
        {
            T* temp = this->m_array;
            this->m_array = array;
            this->m_length = len;
            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException");
        }
    }

public:
    DynamicArray(int length = 0)
    {
        init(new T[length], length);
    }
    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }
    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if( this != &obj )
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }
    void resize(int length)
    {
        if( length != m_length)
        {
            update(copy(this->m_array, m_length, length), length);
        }
    }
    int length()const
    {
        return m_length;
    }
    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
