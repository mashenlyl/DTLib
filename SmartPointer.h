/*
 * (1) 模版实现
 * (2) 主动释放堆空间
 * (3) 一片堆空间最多只能由一个指针标识
 * (4) 杜绝指针运算和比较
 * 异常安全，delete掉对象可能会发生异常，发生异常的时候要保证成员状态的一致性
*/
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
#include "Pointer.h"

namespace DTLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {
    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator =(const SmartPointer<T>& obj)
    {
        if( this != &obj )
        {
            T* temp = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            delete temp;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}


#endif // SMARTPOINTER_H
