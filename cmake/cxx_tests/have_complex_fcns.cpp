#include <complex>
#ifdef HAVE_NAMESPACES
using namespace std;
#endif

int main() {
    complex<double> x(1.0, 1.0);
    real(x); imag(x); abs(x); arg(x); norm(x); conj(x); polar(1.0,1.0);
    return 0;
}
