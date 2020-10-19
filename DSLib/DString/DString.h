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
    bool equal(const char * l, const char * r, int len) const;
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


    bool StartWith(const char * s) const;    //Judge whether the string starts with s
    bool StartWith(const DString s) const;
    bool EndOf(const char * s) const;        //Judge whether the string ends with s
    bool EndOf(const DString s) const;

    DString& insert(int i, const char * s);
    DString& insert(int i, const DString& s);

    DString& trim(void);                     //Remove the space characters at both ends of the string

    //KMP
    static int kmp(const char * ds, const char * src);
    static int * MakePmt(const char * src);
    int indexOf(const char * s) const;
    int indexOf(const DString& s) const;\

    //Delete the specified substring in the string
    DString& remove(int i, int len);
    DString& remove(const char *s);
    DString& remove(const DString& s);

    ~DString();
};

}



#endif // DSTRING_H
