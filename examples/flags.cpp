#include <blitz/array.h>

using namespace blitz;

// FlaggedValue<T,F> is an element which has a value T and
// a flag F.

template<class T, class F>
class FlaggedValue {
public:
    FlaggedValue()
    { }

    FlaggedValue(T value)
    {
        value_ = value;
    }

    F getFlag()
    {
        return flag_;
    }

    void setFlag(F flag)
    {
        flag_ = flag;
    }

    void operator=(T value)
    {
        value_ = value;
    }

    void operator=(const FlaggedValue<T,F>& x)
    {
        value_ = x.value_;
    }

    // maybe similarly for +=, -=, /=, ..

    operator T()
    {
        return value_;
    }

private:
    T value_;
    F flag_;
};


typedef FlaggedValue<double, int> flaggedDouble;

int main()
{
    Array<flaggedDouble,1> A(4);
    A(2).setFlag(0xffff);
    A = 3.0 * tensor::i;   // multiply by [ 0, 1, 2, 3 ]
    cout << A(2) << endl << A(2).getFlag() << endl;
}

