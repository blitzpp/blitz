// Exceptions
// BZ_EXCEPTIONS

#include <typeinfo>

class foo { };

int divide(int a, int b)
{
    if (b == 0)
        throw foo();

    return a / b;
}

int main()
{
    try {
        divide(5,0);
    }
    catch(foo x) {
        return 0;
    }

    return 1;
}

