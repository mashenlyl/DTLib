/*
 * 使用原生数组来实现栈
 */

#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
protected:
    int m_top;
    int m_size;
    T m_space[N];
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }

    void push(const T& obj)
    {
        if( m_size < N )
        {
            m_space[m_top + 1] = obj;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException push");
        }
    }

    void pop()
    {
        if( m_size > 0 )
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException pop");
        }
    }

    T top()
    {
        if( m_size > 0 )
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException top");
        }
    }

    int size()
    {
        return m_size;
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }
};

}


#endif // STATICSTACK_H
