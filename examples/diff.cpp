#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>
#include <blitz/array/stencils.h>
#include <stdio.h>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(blitz::tensor)

BZ_DECLARE_STENCIL3(deriv14,A,dA,h)
  dA = central14n(A) / h;
BZ_END_STENCIL

BZ_DECLARE_STENCIL3(deriv12,A,dA,h)
  dA = central12n(A) / h;
BZ_END_STENCIL

template<class T_stencil>
double calculateError(double h, T_stencil stencil)
{
    const int N = 1024;
    Array<double,1> A(N), dA(N), x(N), hv(N), exactdA(N);
    x = 1/3.0 + (i - N/2.0) * h;
    hv = h;

    // Calculate the sampled function values
    A = cos(x*50);

    // Apply the finite difference approximation
    applyStencil(stencil, A, dA, hv);

    // Calculate the exact derivative
    exactdA = -50*sin(x*50);

    // Find the root mean-squared error (RMS), ignoring values near
    // the boundaries
    Range I(5,N-5);
    double rms = sqrt(sum(pow2(dA(I)-exactdA(I))) / I.length());

    return rms;
}

template<class T_stencil>
double calculateAccuracyOrder(T_stencil stencil)
{
    double h = 1/32.0;
    double oldrms = 0.0, oldh = 0.0;
    double order;

    for (int i=0; i < 9; ++i)
    {
        double rms = calculateError(h, stencil);

        if (i > 0)
        {
            order = (log(rms)-log(oldrms))/(log(h)-log(oldh));
            printf("%18.10lf  %18.10lf  %18.10lf\n", h, rms, order);
        }
        oldh = h; 
        h /= 2.0;
        oldrms = rms;
    }

    return order;
}

int main()
{
    cout << "This program illustrates the O(h^2) and O(h^4) finite difference"
         << endl << "approximations to the first derivative." << endl << endl;

    cout << "central12: first derivative, O(h^2) error" << endl;

    cout.flush();
    printf("     %-15s     %-15s     %-15s\n", "h", "Error", "Order");

    calculateAccuracyOrder(deriv12());
   
    cout << endl << endl
         << "central14: first derivative, O(h^4) error" << endl;
    cout.flush();

    printf("     %-15s     %-15s     %-15s\n", "h", "Error", "Order");

    calculateAccuracyOrder(deriv14());

    return 0;
}

