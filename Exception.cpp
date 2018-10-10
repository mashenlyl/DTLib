#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace DTLib
{

void Exception::init(const char* message, const char* file, int line)
{
    m_message = (message ? strdup(message) : NULL);
    if( file != NULL ){
        char buf[20] = {0};

        itoa(line, buf, 10);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(buf) + 2));
        if( m_location != NULL)
        {
            strcpy(m_location, file);
            strcat(m_location, ":");
            strcat(m_location, buf);
        }
    }
    else{
        m_location = NULL;
    }

}
Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}
Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}
Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& obj)
{
    m_message = strdup(obj.m_message);
    m_location = strdup(obj.m_location);
}
Exception& Exception::operator=(const Exception& obj)
{
    if( this != &obj ){
        free(m_message);
        free(m_location);
        m_message = strdup(obj.m_message);
        m_location = strdup(obj.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}

