#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "LinkList.h"
#include "Exception.h"
#include "Stack.h"

namespace DTLib
{

template < typename T >
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;
public:
    void push(const T& obj)
    {
        m_list.insert(0, obj);
    }

    void pop()
    {
        if( m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException pop");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int size()
    {
        return m_list.length();
    }

    T top()
    {
        return m_list.get(0);
    }

};

}

#endif // LINKSTACK_H
