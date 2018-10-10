#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "Exception.h"
#include "LinkList.h"

namespace DTLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
protected:
    LinkList<int> m_list;
public:
    void add(const T& obj)
    {
        m_list.insert(obj);
    }

    void remove()
    {
        if( m_list.length() > 0 )
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException remove");
        }
    }

    T front()
    {
        if( m_list.length() > 0 )
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException remove");
        }
    }

    int length()
    {
        return m_list.length();
    }

    void clear()
    {
        m_list.clear();
    }
};

}

#endif // LINKQUEUE_H
