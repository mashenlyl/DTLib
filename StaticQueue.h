#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "queue.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity()
    {
        return N;
    }

    void add(const T& obj)
    {
        if( m_length < N )
        {
            m_space[m_rear] = obj;
            m_rear = (m_rear + 1) % N;
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException add");
        }
    }

    void remove()
    {
        if( m_length > 0 )
        {
            m_front = (m_front + 1) % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException remove");
        }
    }

    T front()
    {
        if( m_length > 0 )
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException front");
        }
    }

    void clear()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length()
    {
        return m_length;
    }
};

}

#endif // STATICQUEUE_H
