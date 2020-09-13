#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;

class Test
{
public:
    Test(void)
    {
        cout << "Test(void)" << endl;
    }

    void show(void)
    {
        cout << "show" << endl;
    }

    ~Test(void)
    {
        cout << "~Test(void)" << endl;
    }
};

int main(void)
{
    SmartPointer<Test> sp = new Test();

    sp->show();   //sp.operator->()->show();
    (*sp).show(); //sp.operator*().show();

    return 0;
}
