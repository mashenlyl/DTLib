/*
 * �����Ż�����Ϊ���ںܶ���ظ����߼���������Ҫ�Դ�������Ż���
 * һ���Ż��İ취���ǣ���֤ÿ�������㹻��С��ֻ��һ���£�
 * init()�Զ�����г�ʼ��������update()���³�Ա������ֵ��copy()����ֵ�ĸ���
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
