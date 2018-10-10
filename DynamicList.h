/*
 * �����쳣��ȫ����й©�κ���Դ���������ƻ�����
 * ����쳣���׳��������ڵ��κγ�Ա��Ȼ�ܱ�����Ч��״̬��û�������ƻ�����Դй©��
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

                // ������temp���棬Ȼ����delete���Ƿ�ֹdeleteʧ�ܣ�Ӱ�������ĳ�Ա��״̬
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
