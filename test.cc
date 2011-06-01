//#include <blitz/tinyvec2.h>
#include <blitz/array.h>
#include <blitz/tinyvec2.cc>
#include <blitz/array/array.cc>

using namespace blitz;

int main(int, char**)
{
   TinyVector<float,4> a,b,c;
   a=1,2,3,4;
   b=2,3,4,5;
   cout << a << endl;
   //float s=min(a);

   cout << mean(a) << endl;
   cout << any(a>2.5) << endl;
   cout << count(a>2.5) << endl;
   cout << sum(a) << endl;
   cout << max(a) << endl;
   cout << maxIndex(a) << endl;
   cout << minIndex(a) << endl;

   Array<float,1> d(4);
   d=a;
   cout << endl;
   cout << mean(d) << endl;
   cout << any(d>2.5) << endl;
   cout << count(d>2.5) << endl;
   cout << sum(d) << endl;
   cout << max(d) << endl;
   cout << maxIndex(d) << endl;
   cout << minIndex(d) << endl;


   // Array<float,1> e(4);
   // Array<float,1> l(8);
   Array<float,2> m(4,4);
   // e=.5,.25,.125,.06125;
   m=tensor::i+10*tensor::j;
   // l=2*tensor::i;
   d=max(m,tensor::j);
   cout << d << endl;

   // c=a;
   // c=a*b;
   // cout << c << endl;

   // d=a*b;
   // cout << d << endl;
   // d=a*e;
   // cout << d << endl;
   // a=d*e;
   // cout << a << endl;
   // a=d*b;
   // cout << a << endl;

   // a=b*m(1,Range::all());
   // cout << a << endl;
   // a=b*m(Range::all(),2);
   // cout << a << endl;
   // a=2*tensor::i;
   // cout << a << endl;
   // m=a(tensor::j);
   // cout << m << endl;

}
