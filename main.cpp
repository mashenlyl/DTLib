#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "SharedPointer.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualCircleList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "LinuxLinkQueue.h"
#include "DTString.h"
#include <cstring>

using namespace std;
using namespace DTLib;

int* make_pmt(const char* s)
{

}

int main()
{
    String s;
    cout << s.StartWith("LYL") << endl;
    cout << s.endOf("abc") << endl;
    cout << s[1] << endl;

    return 0;
}

void test_1()
{
    cout << "begin" << endl;
    String s = "a";
    String a = s;
    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (a > s) << endl;
    cout << (a + s).str() << endl;
    cout << (a += s).str() << endl;
    cout << a.str() << endl;
    a = 'd';
    cout << a.str() << endl;

    cout << "end" << endl;
}

template < typename T >
class QueueToStack
{
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T>* m_pIn;
    LinkQueue<T>* m_pOut;

    void move()
    {
        int n = m_pIn->length() - 1;

        for(int i=0; i<n; i++)
        {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }

    void swap()
    {
        LinkQueue<T>* temp = NULL;
        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }

public:
    QueueToStack()
    {
        m_pIn = &m_queue_1;
        m_pOut = &m_queue_2;
    }

    void clear()
    {
        m_pIn->clear();
        m_pOut->clear();
    }

    void push(const T& obj)
    {
        m_pIn->add(obj);
    }

    void pop()
    {
        if( m_pIn->length() > 0)
        {
            move();
            m_pIn->remove();
            swap();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException pop");
        }
    }

    T top()
    {
        if( m_pIn->length() > 0)
        {
            move();
            return m_pIn->front();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException top");
        }
    }

    int size()
    {
        return m_pIn->length() + m_pOut->length();
    }
};

template < typename T >
class StackToQueue
{
protected:
    LinkStack<T> stack_in;
    LinkStack<T> stack_out;

    void move()
    {
        if( stack_out.size() == 0 )
        {
            while( stack_in.size() > 0 )
            {
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }
    }

public:
    void clear()
    {
        stack_in.clear();
        stack_out.clear();
    }

    void add(const T& obj)
    {
        stack_in.push(obj);
    }

    void remove()
    {
        move();

        if( stack_out.size() > 0 )
        {
            stack_out.pop();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException remove");
        }
    }

    T front()
    {
        move();

        if( stack_out.size() > 0 )
        {
            return stack_out.top();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException remove");
        }
    }

    int length()
    {
        return stack_in.size() + stack_out.size();
    }
};


// 用循环链表来解决约瑟夫环问题
void josephus(int n, int s, int m)
{
    CircleList<int> cl;
    for(int i=1; i<=n; i++)
    {
        cl.insert(i);
    }

    cl.move(s-1, m-1);
    while(cl.length() > 0)
    {
        cl.next();

        cout << cl.current() << endl;

        cl.remove(cl.find(cl.current()));
    }
}

bool is_left(char c)
{
    return (c == '(') || (c == '{') || (c == '[') || (c == '<');
}

bool is_right(char c)
{
    return (c == ')') || (c == '}') || (c == ']') || (c == '>');
}

bool is_quot(char c)
{
    return (c == '\'') || (c == '\"');
}

bool is_match(char l, char r)
{
    return (l == '(' && r == ')') ||
           (l == '{' && r == '}') ||
           (l == '[' && r == ']') ||
           (l == '<' && r == '>') ||
           (l == '\'' && r == '\'') ||
           (l == '\"' && r == '\"');
}

// 用栈来进行符号匹配
bool scan(const char* s)
{
    bool ret = true;
    int i = 0;
    LinkStack<char> ls;

    s = (s == NULL) ? "" : s;

    while( ret && (s[i] != '\0'))
    {
        if( is_left(s[i]) )
        {
            ls.push(s[i]);
        }
        else if( is_right(s[i]) )
        {
            if( (ls.size() > 0) && is_match(ls.top(), s[i]) )
            {
                ls.pop();
            }
            else
            {
                ret = false;
            }
        }
        else if( is_quot(s[i]) )
        {
            if( (ls.size() == 0) || !is_match(ls.top(), s[i]) )
            {
                ls.push(s[i]);
            }
            else if( is_match(ls.top(), s[i]) )
            {
                ls.pop();
            }
        }
        i++;
    }

    return (ret && (ls.size() == 0));
}



