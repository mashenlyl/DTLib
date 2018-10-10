#include "Object.h"
#include <cstdlib>
#include <iostream>
using namespace std;

namespace DTLib
{

void* Object::operator new(unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete(void* p) throw()
{
    free(p);
}

void* Object::operator new[](unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[](void* p) throw()
{
    free(p);
}

bool Object::operator ==(const Object& obj)
{
    return (this == &obj);
}

bool Object::operator !=(const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{

}

}
