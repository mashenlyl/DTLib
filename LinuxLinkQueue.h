#ifndef LINUXLINKQUEUE_H
#define LINUXLINKQUEUE_H

#include "LinuxList.h"
#include "Exception.h"
#include "Queue.h"

namespace DTLib
{

template < typename T >
class LinuxLinkQueue : public Queue<T>
{
protected:
    struct Node
    {
        list_head head;
        T value;
    };
    list_head m_header;
    int m_length;
public:
    LinuxLinkQueue()
    {
        m_length = 0;

        INIT_LIST_HEAD(&m_header);
    }

    void add(const T& obj)
    {
        Node* node = new Node();

        if( node != NULL )
        {
            node->value = obj;
            list_add_tail(&node->head, &m_header);
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException insert");
        }
    }

    void remove()
    {
        if( m_length > 0 )
        {
            list_head* toDel = m_header.next;
            list_del(toDel);
            m_length--;
            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException remove");
        }
    }

    T front()
    {
        if( m_length > 0 )
        {
            return list_entry(m_header.next, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException front");
        }
    }

    void clear()
    {
        while( m_length > 0)
        {
            remove();
        }
    }

    int length()
    {
        return m_length;
    }

    ~LinuxLinkQueue()
    {
        clear();
    }
};

}

#endif // LINUXLINKQUEUE_H
