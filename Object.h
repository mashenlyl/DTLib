/*
 * 所有的数据结构都继承自Object类。
 * 为了兼容c++编译器，不同编译器new失败的结果是不一样的。
 * throw()：说明异常处理规格：不抛出异常；
 * 需要为自定义类重载==操作符，以实现find操作；所有的自定义类都要继承Object类
 */
#ifndef OBJECT_H
#define OBJECT_H

namespace DTLib
{

class Object
{
public:
    void* operator new(unsigned int size) throw();
    void operator delete(void* p) throw();
    void* operator new[](unsigned int size) throw();
    void operator delete[](void* p) throw();
    bool operator ==(const Object& obj);
    bool operator !=(const Object& obj);
    virtual ~Object() = 0;
};

}
#endif // OBJECT_H
