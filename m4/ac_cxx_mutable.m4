

AC_DEFUN([AC_CXX_MUTABLE],[AC_MSG_CHECKING([whether $CXX accepts the 'mutable' keyword])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// 'mutable' keyword
// BZ_MUTABLE

class num {

public:
   num(int z)
   {
       x_ = z;
       numReads_ = 0;
   }

   void set(int z)
   { x_ = z; }

   int get() const
   {
       ++numReads_;
       return x_;
   }

private:
   int x_;
   mutable int numReads_;
};
]],[[
   num q(4);
   q.set(5);
   int k = q.get();
   q.get();
   return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_MUTABLE],[],[What about the 'mutable' keyword?])],
[AC_MSG_RESULT([no])])])


