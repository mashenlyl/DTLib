/*
 * 频繁增删元素，会存在大量的内存碎片。所以申请一块固定的空间，在这块空间中增删元素。
 * typename Test::Ts说明Ts不是变量，而是类型
 */

#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib
{

template < typename T, int N >
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };
    unsigned char m_memory[sizeof(SNode) * N];
    int m_used[N];
public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    SNode* create()
    {
        SNode* ret = NULL;

        for(int i=0; i<N; i++)
        {
            if(m_used[i] == 0)
            {
                ret = (reinterpret_cast<SNode*>(m_memory) + i);
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_memory);
        SNode* psn = dynamic_cast<SNode*>(pn);

        for(int i=0; i<N; i++)
        {
            if( psn == space + i )
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }

    ~StaticLinkList()
    {
        this->clear();
    }

};

}


#endif // STATICLINKLIST_H
