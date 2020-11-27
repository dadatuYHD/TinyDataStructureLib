#ifndef OBJECT_H
#define OBJECT_H

namespace  MyTiny_DSLib{

class Object
{
public:
    /*    Because different compilers may cause new to return
     *    different results when an error occurs, so overload
     *    new and delete in the top-level parent class
     */
    void * operator new (unsigned long long size) throw();
    void   operator delete (void * p) throw();
    void * operator new[] (unsigned long long size) throw();
    void   operator delete[] (void * p) throw();
    bool  operator == (const Object& obj);
    bool  operator != (const Object& obj);

    virtual ~Object() = 0;
};

}


#endif // OBJECT_H
