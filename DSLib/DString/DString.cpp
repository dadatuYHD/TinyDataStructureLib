#include "DString.h"
#include <cstring>
#include <cstdlib>
#include "Exception/Exception.h"

using namespace std;

namespace DSLib {

void DString::init(const char * s)
{
     m_str = strdup(s);

     if (m_str)
     {
         m_length = strlen(m_str);
     }
     else
     {
         THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String object ...");
     }


}

DString::DString()
{
    init("");
}

DString::DString(const char * s)
{
    init(s ? s : "");
}

DString::DString(const DString& s)
{
    init(s.m_str);
}

DString::DString(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

DString::~DString()
{
    free(m_str);
}

int DString::length(void) const
{
    return m_length;
}

const char* DString::str() const
{
    return m_str;
}

bool DString::operator == (const DString& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool DString::operator == (const char * s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool DString::operator != (const DString& s) const
{
    return !(strcmp(m_str, s.m_str) == 0);
}

bool DString::operator != (const char * s) const
{
    return !(strcmp(m_str, s ? s : "") == 0);
}

bool DString::operator > (const DString& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool DString::operator > (const char * s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool DString::operator < (const DString& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool DString::operator < (const char * s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool DString::operator >= (const DString& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}

bool DString::operator >= (const char * s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool DString::operator <= (const DString& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool DString::operator <= (const char * s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

DString  DString::operator + (const DString& s) const
{
    return (*this + s.m_str);
}

DString  DString::operator + (const char * s) const
{
    DString ret;
    int len = m_length + strlen(s ? s : "");
    char * str = reinterpret_cast<char *>(malloc(len + 1));

    if (str)
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to add string ... ");
    }

    return ret;
}

DString& DString::operator += (const DString& s)
{
    return (*this = *this + s);
}

DString& DString::operator += (const char * s)
{
    return (*this = *this + s);
}

DString& DString::operator = (const DString& s)
{
    return (*this = s.m_str);
}

DString& DString::operator = (const char * s)
{
    if (m_str != s)
    {
        char * str = strdup(s ? s : "");

        if (str)
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new String ...");
        }
    }

    return *this;
}

DString& DString::operator = (const char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

char& DString::operator [] (int i)
{
    if (0 <= i && i < m_length)
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "");
    }
}

char  DString::operator [] (int i) const
{
    return const_cast<DString&>(*this)[i];
}

}
