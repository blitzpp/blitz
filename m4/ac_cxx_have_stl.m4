


AC_DEFUN([AC_CXX_HAVE_STL],[AC_MSG_CHECKING([whether $CXX has standard template library])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#include <list>
#include <deque>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif
]],[[
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
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_STL],[],[Standard template library?])],
[AC_MSG_RESULT([no])])])


