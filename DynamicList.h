/*
 * 函数异常安全：不泄漏任何资源，不允许破坏数据
 * 如果异常被抛出，对象内的任何成员仍然能保持有效的状态，没有数据破坏及资源泄漏。
 */

#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace DTLib
{

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];
        if( this->m_array != NULL)
        {
            this->m_length = 0;
            m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException");
        }
    }
    int capacity()const
    {
        return m_capacity;
    }
    void resize(int capacity)
    {
        if( m_capacity != capacity)
        {
            T* array = new T[capacity];
            if(array != NULL)
            {
                int len = this->m_length < capacity ? this->m_length : capacity;
                for(int i=0; i<len; i++)
                {
                    array[i] = this->m_array[i];
                }

                // 这里用temp保存，然后再delete，是防止delete失败，影响其他的成员的状态
                T* temp = this->m_array;
                this->m_array = array;
                this->m_length = len;
                m_capacity = capacity;
                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException");
            }

        }
    }
    ~DynamicList()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
