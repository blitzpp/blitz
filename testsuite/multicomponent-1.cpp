#include "testsuite.h"
#include <blitz/array.h>
#include <blitz/array.cc>
#include <blitz/tinyvec2.h>
#include <blitz/tinyvec2.cc>
#include <blitz/tinymat2.h>
#include <blitz/tinymat2.cc>

BZ_USING_NAMESPACE(blitz)

static const double eps = 0.0001;

#define ISCLOSE(a, b) BZTEST(fabs((a)-(b))<eps)

#define __TEST_FOR_VECTOR_EXPR

typedef TinyMatrix<double, 2, 3> T_matrix;
typedef TinyVector<double, 3> T_vector;
typedef Array<double, 2> T_array_2;
typedef Array<double, 1> T_array_1;
typedef Array<T_vector, 1> T_array_1_of_vector;
typedef Array<T_vector, 2> T_array_2_of_vector;
typedef Array<T_matrix, 1> T_array_1_of_matrix;
typedef Array<T_matrix, 2> T_array_2_of_matrix;

#ifndef __TEST_FOR_VECTOR_EXPR
#define EXPR2(a) (T_vector(a * 2 + 1))
#define EXPR3(a) (T_vector(a * 3 - 4))
#else
#define EXPR2(a) (a * 2 + 1)
#define EXPR3(a) (a * 3 - 4)
#endif

#define EXPR4(a, b) (a - b * 5 + 6)

int main() {

	T_vector V1(1, 2, 3);
	T_vector V2 = EXPR2(V1);
	T_vector V3 = EXPR3(V1);
	T_vector V4 = EXPR4(V2, V1);
	cout << "V1 = " << V1 << endl;
	cout << "V2 = " << V2 << endl;
	cout << "V3 = " << V3 << endl;
	cout << "V4 = " << V4 << endl;

	cout << "Testing for 1d-Array:" << endl;

	//Here TinyVector is composite object like as Array in the left side
	T_array_1 A1(3);
	A1 = EXPR2(V1);
	cout << A1 << endl;
	for (int k = 0; k < 3; ++ k) { ISCLOSE(A1(k), V2(k)); }
	//Here we construct TinyVector as scalar value and fill Array
	T_array_1_of_vector A1V(5);
	A1V = EXPR2(V1);
	cout << A1V << endl;
	for (int i = 0; i < 5; ++ i)
	for (int k = 0; k < 3; ++ k) { ISCLOSE(A1V(i)(k), V2(k)); }
	//Partial assignment of a vector expression
	A1V(Range(1, 3)) = EXPR3(V1);
	cout << A1V << endl;
	for (int i = 0; i < 5; ++ i)
	for (int k = 0; k < 3; ++ k) {
		if ((i >= 1) && (i <= 3)) {
			ISCLOSE(A1V(i)(k), V3(k));
		}
		else {
			ISCLOSE(A1V(i)(k), V2(k));
		}
	}
	//Check for component wise assignment
	for (int k = 0; k < 3; ++ k) {
		A1V[k] = V4(k);
	}
	cout << A1V << endl;
	for (int i = 0; i < 5; ++ i)
	for (int k = 0; k < 3; ++ k) { ISCLOSE(A1V(i)(k), V4(k)); }

	cout << "Testing for 2d-Array:" << endl;

	//Here we construct TinyVector as scalar value and fill Array
	T_array_2_of_vector A2V(5, 4);
	A2V = EXPR2(V1);
	cout << A2V << endl;
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j)
	for (int k = 0; k < 3; ++ k) { ISCLOSE(A2V(i, j)(k), V2(k)); }
	//Partial assignment of a vector expression
	A2V(Range(2, 3), Range(1, 2)) = EXPR3(V1);
	cout << A2V << endl;
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j)
	for (int k = 0; k < 3; ++ k) {
		if ((i >= 2) && (i <= 3) &&
		    (j >= 1) && (j <= 2)) {
			ISCLOSE(A2V(i, j)(k), V3(k));
		}
		else {
			ISCLOSE(A2V(i, j)(k), V2(k));
		}
	}
	//Check for component wise assignment
	for (int k = 0; k < 3; ++ k) {
		A2V[k] = V4(k);
	}
	cout << A2V << endl;
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j)
	for (int k = 0; k < 3; ++ k) { ISCLOSE(A2V(i, j)(k), V4(k)); }
	//Check for array expression
	T_array_2_of_vector A(5, 4);
	T_array_2_of_vector B(5, 4);
	T_array_2_of_vector C(5, 4);
	A = V1;
	B = V2;
	B(0, 3) = EXPR3(V1);
	B(4, 0) = V3;
	C = EXPR4(B, A);
	cout << C << endl;
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j)
	for (int k = 0; k < 3; ++ k) {
		ISCLOSE(C(i, j)(k), EXPR4(B(i, j)(k), A(i, j)(k)));
	}

	return 0;
}
