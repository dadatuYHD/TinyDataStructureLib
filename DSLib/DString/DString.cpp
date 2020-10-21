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

DString DString::operator  - (const DString& s) const
{
    return DString(*this).remove(s);
}

DString  DString::operator  - (const char * s) const
{
    return DString(*this).remove(s);
}

DString& DString::operator -= (const DString& s)
{
    return remove(s);
}

DString& DString::operator -= (const char * s)
{
    return remove(s);
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
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
}

char  DString::operator [] (int i) const
{
    return const_cast<DString&>(*this)[i];
}

bool DString::equal(const char * l, const char * r, int len) const
{
    bool ret = true;

    for (int i = 0; i < len && ret; i++)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

bool DString::StartWith(const char * s) const
{
    bool ret = (s != nullptr);

    if (ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool DString::StartWith(const DString s) const
{
    return StartWith(s.str());
}

bool DString::EndOf(const char * s) const
{
    bool ret = (s != nullptr);

    if (ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str + m_length - len, s, len);
    }

    return ret;
}

bool DString::EndOf(const DString s) const
{
    return EndOf(s.str());
}

DString& DString::insert(int i, const char * s)
{
    if ((0 <= i) && (i <= m_length))
    {
        if ((s != nullptr) && (s[0] != '\0'))
        {
            int len = m_length + strlen(s);
            char * str = reinterpret_cast<char *>(malloc(len + 1));

            if (str)
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
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert String ...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter i is invalid ...");
    }

    return *this;
}

DString& DString::insert(int i, const DString& s)
{
    return insert(i, s.m_str);
}

DString& DString::trim(void)
{
    int front = 0;
    int rear = m_length - 1;

    while (m_str[front] == ' ') front++;
    while (m_str[rear]  == ' ') rear--;

    if (front == 0)
    {
        m_str[rear + 1] = '\0';
        m_length = rear + 1;
    }
    else
    {
        for (int i = 0, j = front; j <= rear; i++, j++)
        {
            m_str[i] = m_str[j];
        }

        m_str[rear - front + 1] = '\0';
        m_length = rear - front + 1;
    }

    return *this;
}

int * DString::MakePmt(const char * src)
{
    int len = strlen(src);

    int * pmt = static_cast<int *>(malloc(sizeof(int) * len));

    if (pmt)
    {
        int ll = 0;

        pmt[0] = 0;

        for (int i = 1; i < len; i++)
        {
            while ((src[i] != src[ll]) && ll > 0)
            {
                ll = pmt[ll - 1];
            }

            if (src[i] == src[ll])
            {
                ll++;
            }

            pmt[i] = ll;
        }
    }

    return pmt;
}

int DString::kmp(const char * ds, const char * src)
{
    int ret = -1;
    int dsLen = strlen(ds);
    int srcLen = strlen(src);
    int * pmt = MakePmt(src);

    for (int i = 0, j = 0; i < dsLen; i++)
    {
        while ((j > 0) && (ds[i] != src[j]))
        {
            j = pmt[j - 1];
        }

        if (ds[i] == src[j])
        {
            j++;
        }

        if (j == srcLen)
        {
            ret = i + 1 - srcLen;
            break;
        }
    }

    free(pmt);

    return ret;
}

int DString::indexOf(const char * s) const
{
    return kmp(m_str, (s ? s : ""));
}

int DString::indexOf(const DString& s) const
{
    return kmp(m_str, s.m_str);
}

DString& DString::remove(int i, int len)
{
    if ((0 <= i) && (i < m_length))
    {
        int n = i;
        int m = i + len;

        while ((n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

DString& DString::remove(const char *s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

DString& DString::remove(const DString& s)
{
    return remove(indexOf(s), s.length());
}

DString& DString::replace(const char * dest, const char * src)
{
    int index = indexOf(dest);

    if (index >= 0)
    {
        remove(dest);
        insert(index, src);
    }

    return *this;
}

DString& DString::replace(const DString& dest, const char * src)
{
    return replace(dest.m_str, src);
}

DString& DString::replace(const char * dest, const DString& src)
{
    return replace(dest, src.m_str);
}

DString& DString::replace(const DString& dest, const DString& src)
{
    return replace(dest.m_str, src.m_str);
}

DString DString::SubString(int i, int len) const
{
    DString ret;

    if ((0 <= i) && (i <= m_length))
    {
        if (len < 0) len = 0;
        if (len + i > m_length) len = m_length - i;

        char * str = reinterpret_cast<char *>(malloc(len + 1));

        strncpy(str, m_str + i, len);

        ret = str;

        return ret;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
}

}
