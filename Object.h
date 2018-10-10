/*
 * ���е����ݽṹ���̳���Object�ࡣ
 * Ϊ�˼���c++����������ͬ������newʧ�ܵĽ���ǲ�һ���ġ�
 * throw()��˵���쳣�����񣺲��׳��쳣��
 * ��ҪΪ�Զ���������==����������ʵ��find���������е��Զ����඼Ҫ�̳�Object��
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
