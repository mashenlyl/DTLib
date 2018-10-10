/*
 * (1)头结点的问题：头结点在声明的时候就会构造对象，这样不好，所以我们就模拟Node的内存布局，这样
 * 可以在不调用构造函数的前提下达到同样的效果；
 * (2)代码优化：把重复的代码优化为position函数；
 * (3)mutable关键字：被mutable修饰的成员变量，可以在const成员函数中被修改。
 */

#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    }m_header;

    int m_length;
    Node* m_current;
    int m_step;

    Node* position(int i)const
    {
        Node* current = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            current = current->next;
        }

        return current;
    }

    virtual Node* create()
    {
        return (new Node);
    }

    virtual void destroy(Node* node)
    {
        delete node;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_current = NULL;
        m_step = 1;
    }

    bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {
            Node* node = create();

            if( node != NULL )
            {
                Node* current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;
                m_length++;
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
        return insert(m_length, e);
    }

    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if( ret )
        {
            Node* current = position(i);
            Node* toDel = current->next;

            if(toDel == m_current)
            {
                m_current = toDel->next;
            }

            current->next = toDel->next;
            m_length--;
            this->destroy(toDel);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if( ret )
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    bool get(int i, T& e)const
    {
        bool ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            e = position(i)->next->value;
        }

        return ret;
    }

    virtual T get(int i)const
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
        Node* node = m_header.next;
        int i = 0;

        while( node != NULL )
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                i++;
                node = node->next;
            }
        }

        return ret;
    }

    virtual bool move(int i, int step=1)
    {
        bool ret = ((0 <= i) && (i < m_length) && (m_step>0));

        if( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }

    virtual bool next()
    {
        int i = 0;

        while( (!end()) && (i < m_step) )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    virtual T current()
    {
        if( !end() )
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException current");
        }
    }

    virtual bool end()
    {
        return (m_current == NULL);
    }

    int length()const
    {
        return m_length;
    }

    void clear()
    {
        while( m_header.next )
        {
            Node* toDel = m_header.next;
            m_header.next = toDel->next;
            m_length--;
            destroy(toDel);
        }
    }

    ~LinkList()
    {
        clear();
    }
};

}

#endif // LINKLIST_H
