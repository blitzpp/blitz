#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

#ifdef BZ_SERIALIZE
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>
#endif

int main()
{
#ifdef BZ_SERIALIZE

  stringstream s;

  TinyVector<double, 4> v(1.1,2.2,3.3,4.4);
  TinyMatrix<double, 2, 4> m;
  m=1.1,2.2,3.3,4.4;
  Array<double,1> a(5),b(a);

  {  
    a=2.2, -3.3, 4.4, -5.5, 6.6;
    boost::archive::text_oarchive oa(s);

    // write class instance to archive
    oa << v << m;
    oa << a << b;
  }

  cout << s.str() << endl;

  {
    Array<double,1> aa,bb;
    boost::archive::text_iarchive ia(s);
    TinyVector<double,4> vv;
    TinyMatrix<double, 2, 4> mm;
    ia >> vv >> mm;
    ia >> aa >> bb;

    BZTEST(all(v==vv));
    BZTEST(all(m==mm));
    BZTEST(all(a==aa));
    BZTEST(all(b==bb));
    // make sure aa and bb still refer to the same block
    bb(3)=4711;
    BZTEST(aa(3)==bb(3));

   }

#endif

  return 0;
}

