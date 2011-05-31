#include <blitz/constpointerstack.h>
#include <blitz/array.h>
#include <blitz/tinyvec2.h>
#include <blitz/tinyvec-et.h>

using namespace blitz;

//void operator*(TinyVector2<float,4> a,TinyVector2<float,4> b)
//{}

int main(int, char**)
{
   TinyVector2<float,4> a,b,c;
   TinyVector<float,4> aa,bb,cc;
   a=1,2,3,4;
   b=2,3,4,5;
   aa=1,2,3,4;
   bb=2,3,4,5;
   /*
   Array<float,1> d(4);
   Array<float,1> e(4);
   Array<float,1> l(8);
   Array<float,2> m(4,4);
   e=.5,.25,.125,.06125;
   m=tensor::i+10*tensor::j;
   l=2*tensor::i;
   */
   asm("nop; nop; nop;");
   cc=aa*bb;
   asm("nop; nop; nop;");
   c=a*b;
   asm("nop; nop;");
  cout << cc << endl;
  cout << c << endl;
  //d=m(Range::all(),2);
  
  //cout << d << endl;
   asm("nop; nop;");
   //c=d*2;
   //cout << c << endl;
}
