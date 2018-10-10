#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* r, int len) const;
public:
    String();
    String(const char* s);
    String(char c);
    String(const String& s);

    int length() const;
    const char* str() const;
    char& operator [] (int i);
    char operator [] (int i) const;
    bool StartWith(const char* s) const;
    bool StartWith(const String& obj) const;
    bool endOf(const char* s) const;
    bool endOf(const String& obj) const;
    String& insert(int i, const char* s);
    String& insert(int i, const String& obj);
    String& trim();

    bool operator == (const String& obj) const;
    bool operator == (const char* s) const;
    bool operator > (const String& obj) const;
    bool operator > (const char* s) const;
    bool operator < (const String& obj) const;
    bool operator < (const char* s) const;
    bool operator != (const String& obj) const;
    bool operator != (const char* s) const;
    bool operator >= (const String& obj) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& obj) const;
    bool operator <= (const char* s) const;

    String operator + (const String& obj) const;
    String operator + (const char* s) const;
    String& operator += (const String& obj);
    String& operator += (const char* s);

    String& operator = (const String& obj);
    String& operator = (const char* s);
    String& operator = (const char c);

    ~String();
};

}

#endif // DTSTRING_H
