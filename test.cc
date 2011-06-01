#include <blitz/tinyvec2.h>
#include <blitz/array.h>
#include <blitz/tinyvec2.cc>
#include <blitz/array/ops.h>

using namespace blitz;

int main(int, char**)
{
   TinyVector<float,4> a,b,c;
   a=1,2,3,4;
   b=2,3,4,5;

   Array<float,1> d(4);
   Array<float,1> e(4);
   Array<float,1> l(8);
   Array<float,2> m(4,4);
   e=.5,.25,.125,.06125;
   m=tensor::i+10*tensor::j;
   l=2*tensor::i;

   c=a;
   c=a*b;
   cout << c << endl;

   d=a*b;
   cout << d << endl;
   d=a*e;
   cout << d << endl;
   a=d*e;
   cout << a << endl;
   a=d*b;
   cout << a << endl;

   a=b*m(1,Range::all());
   cout << a << endl;
   a=b*m(Range::all(),2);
   cout << a << endl;
   a=2*tensor::i;
   cout << a << endl;
   m=a(tensor::j);
   cout << m << endl;

}
