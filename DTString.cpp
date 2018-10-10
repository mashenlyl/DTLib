#include "DTString.h"
#include <cstring>
#include <cstdlib>
#include "Exception.h"

using namespace std;

namespace DTLib
{

void String::init(const char* s)
{
    m_str = strdup(s);

    if( m_str != NULL )
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException init");
    }
}

String::String()
{
    init("");
}

String::String(const char* s)
{
    init(s ? s : "");
}

String::String(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

char& String::operator [] (int i)
{
    if( (0 <= i) && (i < m_length) )
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException []");
    }
}

char String::operator [] (int i) const
{
    return (const_cast<String&>(*this))[i];
}

bool String::equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    for(int i=0; i<len && ret; i++)
    {
        ret = (l[i] == r[i]);
    }

    return ret;
}

bool String::StartWith(const char* s) const
{
    bool ret = (s != NULL) && (strlen(s) < m_length);

    if( ret )
    {
        ret = equal(m_str, s, strlen(s));
    }

    return ret;
}

bool String::StartWith(const String& obj) const
{
    return StartWith(obj.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL) && (strlen(s) < m_length);
    int len = m_length - strlen(s);

    if( ret )
    {
        ret = equal(m_str + len, s, strlen(s));
    }

    return ret;
}

bool String::endOf(const String& obj) const
{
    return endOf(obj.m_str);
}

String& String::insert(int i, const char* s)
{
    if( (0 <= i) && (i <= m_length) )
    {
        if(  (s != NULL) && (s[0] != '\0') )
        {
            int len = strlen(s) + m_length;
            char* str = static_cast<char*>(malloc(len + 1));

            if( str != NULL )
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, strlen(s));
                strncpy(str + i + strlen(s), m_str + i, m_length - i);

                str[len] = '\0';
                free(m_str);
                m_str = str;
                m_length = len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException insert");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "InvalidParameterException insert");
    }

    return *this;
}

String& String::insert(int i, const String& obj)
{
    return insert(i, obj.m_str);
}

String& String::trim()
{
    int b = 0, e = m_length - 1;

    while(m_str[b] == ' ') b++;
    while(m_str[e] == ' ') e--;

    if( b == 0 )
    {
        m_str[e + 1] = '\0';
    }
    else
    {
        for(int i=0, j=b; i<e-b+1; i++, j++)
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b;
    }

    return *this;
}

bool String::operator == (const String& obj) const
{
    return (strcmp(m_str, obj.m_str) == 0);
}

bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& obj) const
{
    return !(*this == obj.m_str);
}

bool String::operator != (const char* s) const
{
    return !(*this == s);
}

bool String::operator > (const String& obj) const
{
    return (strcmp(m_str, obj.m_str) > 0);
}

bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator < (const String& obj) const
{
    return (strcmp(m_str, obj.m_str) < 0);
}

bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& obj) const
{
    return (strcmp(m_str, obj.m_str) >= 0);
}

bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& obj) const
{
    return (strcmp(m_str, obj.m_str) <= 0);
}

bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

String String::operator + (const String& obj) const
{
    return (*this + obj.m_str);
}

String String::operator + (const char* s) const
{
    String ret;
    s = s ? s : "";
    int len = strlen(s) + m_length;
    char* str = static_cast<char*>(malloc(len + 1));

    if( str != NULL )
    {
        strcpy(str, m_str);
        strcat(str, s);

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException +");
    }

    return ret;
}

String& String::operator += (const String& obj)
{
    return (*this = *this + obj);
}

String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& obj)
{
    return (*this = obj.m_str);
}

String& String::operator = (const char* s)
{
    if( m_str != s )
    {
        s = s ? s : "";
        char* str = strdup(s);

        if( str != NULL )
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemoryException =");
        }
    }

    return *this;
}

String& String::operator = (const char c)
{
    char s[] = {c, '\0'};
    return (*this = s);
}

String::~String()
{
    free(m_str);
}

}




