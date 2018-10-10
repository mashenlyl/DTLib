/*
 * 线性表，顺序存储结构；
 * 对于容器类型的类，可以考虑禁用拷贝构造函数和赋值操作；
 * 因为提供了拷贝构造函数，编译器就不会默认提供构造函数了，所以需要我们自己定义构造函数；
 */

#ifndef LIST_H
#define LIST_H
#include "Object.h"

namespace DTLib
{

template <typename T>
class List : public Object
{
protected:
    List(const List& l);
    List& operator =(const List& l);
public:
    List() {}
    virtual bool insert(int i, const T& e) = 0;
    virtual bool insert(const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e)const = 0;
    virtual int length()const = 0;
    virtual int find(const T& e)const = 0;
    virtual void clear() = 0;
};

}

#endif // LIST_H
