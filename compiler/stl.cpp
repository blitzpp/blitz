#include <list>
#include <deque>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif

int main()
{
    list<int> x;
    x.push_back(5);
    x.push_back(10);

    int sum = 0;

    for (list<int>::iterator iter = x.begin();
        iter != x.end(); ++iter)
    {
        sum += *iter;
    }

    if (sum != 15)
        return 1;

    return 0;
}

