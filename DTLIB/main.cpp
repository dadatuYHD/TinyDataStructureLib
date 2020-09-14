#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main(void)
{
    try
    {
        THROW_EXCEPTION(ArithmeticException, "test");
    }
    catch (const ArithmeticException& e)
    {
        cout << "catch (const ArithmeticException& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch (const Exception& e)
    {
        cout << "catch (const Exception& e) " << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    return 0;
}
