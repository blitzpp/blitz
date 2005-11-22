#include <blitz/array.h>
#include <blitz/array/indirect.h>
#include <list>
#include <vector>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(std)

void example1()
{
    // Indirection using a list of TinyVector<int,N> objects

    Array<int,2> A(4,4), B(4,4);
    A = 0;
    B = 10*tensor::i + tensor::j;

    typedef TinyVector<int,2> coord;

    list<coord> I;
    I.push_back(coord(1,1));
    I.push_back(coord(2,2));

    A[I] = B;

    cout << "B = " << B << endl << "A = " << A << endl;

    // B = 4 x 4
    //     0         1         2         3
    //    10        11        12        13
    //    20        21        22        23
    //    30        31        32        33

    // A = 4 x 4
    //     0         0         0         0
    //     0        11         0         0
    //     0         0        22         0
    //     0         0         0         0
}

void example2()
{
    // Cartesian-product indirection

    Array<int,2> A(6,6), B(6,6);
    A = 0;
    B = 10*tensor::i + tensor::j;

    vector<int> I, J;
    I.push_back(1);
    I.push_back(2);
    I.push_back(4);

    J.push_back(2);
    J.push_back(0);
    J.push_back(5);

    A[indexSet(I,J)] = B;

    cout << "B = " << B << endl << "A = " << A << endl;

    // B = 6 x 6
    //     0         1         2         3         4         5
    //    10        11        12        13        14        15
    //    20        21        22        23        24        25
    //    30        31        32        33        34        35
    //    40        41        42        43        44        45
    //    50        51        52        53        54        55

    // A = 6 x 6
    //     0         0         0         0         0         0
    //    10         0        12         0         0        15
    //    20         0        22         0         0        25
    //     0         0         0         0         0         0
    //    40         0        42         0         0        45
    //     0         0         0         0         0         0

}

void example3()
{
    // Simple 1-D indirection, using a STL container of int
    Array<int,1> A(5), B(5);
    A = 0;
    B = 1, 2, 3, 4, 5;

    vector<int> I;
    I.push_back(2);
    I.push_back(4);
    I.push_back(1);

    A[I] = B;

    cout << "B = " << B << endl << "A = " << A << endl;

    // B = [          1         2         3         4         5 ]
    // A = [          0         2         3         0         5 ]

    // Test setting indexed items back to zero.
    A[I] = 0;
    cout << "After reset:" << endl << "A = " << A << endl;

    // A = [          0         0         0         0         0 ]
}

void example4()
{
    // Indirection using a list of RectDomain<N> objects.

    const int N = 7;
    Array<int,2> A(N,N), B(N,N);
    typedef TinyVector<int,2> coord;

    A = 0;
    B = 1;

    double centre_i = (N-1)/2.0;
    double centre_j = (N-1)/2.0;
    double radius = 0.8 * N/2.0;

    // circle will contain a list of strips which represent a circular
    // subdomain.

    list<RectDomain<2> > circle;
    for (int i=0; i < N; ++i)
    {
        double jdist2 = pow2(radius) - pow2(i-centre_i);
        if (jdist2 < 0.0)
            continue;

        int jdist = int(sqrt(jdist2));
        coord startPos(i, int(centre_j - jdist));
        circle.push_back(strip(startPos, secondDim, int(centre_j + jdist)));
    }

    // Set only those points in the circle subdomain to 1
    A[circle] = B;

    cout << "A = " << A << endl;

    // A = 7 x 7
    //  0  0  0  0  0  0  0
    //  0  0  1  1  1  0  0
    //  0  1  1  1  1  1  0
    //  0  1  1  1  1  1  0
    //  0  1  1  1  1  1  0
    //  0  0  1  1  1  0  0
    //  0  0  0  0  0  0  0
}

int main()
{
    example1();
    example2();
    example3();
    example4();   
}

