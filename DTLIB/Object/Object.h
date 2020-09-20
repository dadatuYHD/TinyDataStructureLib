#ifndef OBJECT_H
#define OBJECT_H

namespace  DTLib{

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

    virtual ~Object() = 0;
};

}


#endif // OBJECT_H
