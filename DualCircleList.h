/*
 * 双向循环链表：用linux内核链表来实现的
 */

#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"
#include "LinuxList.h"

namespace DTLib
{

template < typename T >
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    list_head* position(int i)const
    {
        list_head* current = const_cast<list_head*>(&m_header);

        for(int p=0; p<i; p++)
        {
            current = current->next;
        }

        return current;
    }

    int mod(int i) const
    {
        return ((this->m_length == 0) ? 0 : i%this->m_length);
    }
public:
    DualCircleList()
    {
        INIT_LIST_HEAD(&m_header);
        this->m_length = 0;
        m_current = NULL;
        this->m_step = 1;
    }

    bool insert(int i, const T& e)
    {
        i = i % (this->m_length + 1);
        bool ret = ((0 <= i) && (i <= this->m_length));

        if( ret )
        {
            Node* node = new Node();

            if( node != NULL )
            {
                node->value = e;
                list_add_tail(&node->head, position(i)->next);

                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException insert");
            }
        }
        return ret;
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool remove(int i)
    {
        i = mod(i);
        bool ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            list_head* toDel = position(i)->next;

            if( toDel == m_current )
            {
                m_current = toDel->next;
            }

            list_del(toDel);
            this->m_length--;

            delete list_entry(toDel, Node, head);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        i = mod(i);
        bool ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            list_entry(position(i)->next, Node, head)->value = e;
        }

        return ret;
    }

    bool get(int i, T& e)const
    {
        i = mod(i);
        bool ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            e = list_entry(position(i)->next, Node, head)->value;
        }

        return ret;
    }

    T get(int i)const
    {
        T ret = 0;
        if( get(i, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "IndexOutOfBoundsException get");
        }
    }

    int find(const T& e)const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;

        list_for_each(slider, &m_header)
        {
            if( list_entry(slider, Node, head)->value == e)
            {
                ret = i;
                break;
            }
            i++;
        }

        return ret;
    }

    bool move(int i, int step=1)
    {
        i = mod(i);
        bool ret = ((0 <= i) && (i < this->m_length) && (this->m_step>0));

        if( ret )
        {
            m_current = position(i)->next;
            this->m_step = step;
        }
        return ret;
    }

    bool next()
    {
        int i = 0;

        while( (!end()) && (i < this->m_step) )
        {
            if( m_current == &m_header )
            {
                m_current = m_current->next;
            }
            else
            {
                m_current = m_current->next;
                i++;
            }
        }

        if( m_current == &m_header )
        {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    bool pre()
    {
        int i = 0;

        while( (!end()) && (i < this->m_step) )
        {
            if( m_current == &m_header )
            {
                m_current = m_current->prev;
            }
            else
            {
                m_current = m_current->prev;
                i++;
            }
        }

        if( m_current == &m_header )
        {
            m_current = m_current->prev;
        }

        return (i == this->m_step);
    }

    T current()
    {
        if( !end() )
        {
            return list_entry(m_current, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException current");
        }
    }

    bool end()
    {
        return (this->m_length == 0) || (m_current == NULL);
    }

    int length()const
    {
        return this->m_length;
    }

    void clear()
    {
        while( this->m_length > 0 )
        {
            remove(0);
        }
    }

    ~DualCircleList()
    {
        clear();
    }

};

}

#endif // DUALCIRCLELIST_H
