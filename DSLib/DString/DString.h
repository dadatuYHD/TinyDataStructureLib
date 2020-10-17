#ifndef DSTRING_H
#define DSTRING_H

#include "Object/Object.h"


namespace DSLib {

class DString : public Object
{
protected:
    char * m_str;
    int m_length;
    void init(const char * s);
public:
    DString();
    DString(const char * s);
    DString(const DString& s);
    DString(char c);

    int length(void) const;
    const char* str() const;

    char& operator [] (int i);
    char operator [] (int i) const;
    bool operator == (const DString& s) const;
    bool operator == (const char * s) const;
    bool operator != (const DString& s) const;
    bool operator != (const char * s) const;
    bool operator > (const DString& s) const;
    bool operator > (const char * s) const;
    bool operator < (const DString& s) const;
    bool operator < (const char * s) const;
    bool operator >= (const DString& s) const;
    bool operator >= (const char * s) const;
    bool operator <= (const DString& s) const;
    bool operator <= (const char * s) const;

    DString operator + (const DString& s) const;
    DString operator + (const char * s) const;
    DString& operator += (const DString& s);
    DString& operator += (const char * s);

    DString& operator = (const DString& s);
    DString& operator = (const char * s);
    DString& operator = (const char c);

    bool StartWith(const char * s) const;
    bool StartWith(const DString s) const;
    bool EndOf(const char * s) const;
    bool EndOf(const DString s) const;

    ~DString();
};

}



#endif // DSTRING_H
