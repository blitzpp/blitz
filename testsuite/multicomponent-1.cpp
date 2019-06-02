#include "testsuite.h"
#include <blitz/array.h>
#include <blitz/array.cc>
#include <blitz/tinyvec2.h>
#include <blitz/tinyvec2.cc>
#include <blitz/tinymat2.h>
#include <blitz/tinymat2.cc>

BZ_USING_NAMESPACE(blitz)

static const double eps = 1.e-7;

#define ISCLOSE(a, b) BZTEST(fabs((a)-(b))<eps)

#define ROW (2)
#define COL (3)

typedef TinyMatrix<double, ROW, COL> T_matrix;
typedef TinyVector<double, COL> T_vector;
typedef Array<T_matrix, 2> T_array_2_of_matrix;
typedef Array<T_matrix, 1> T_array_1_of_matrix;
typedef Array<T_vector, 2> T_array_2_of_vector;
typedef Array<T_vector, 1> T_array_1_of_vector;
typedef Array<double, 2> T_array_2;
typedef Array<double, 1> T_array_1;

#define __TEST_FOR_MATRIX_EXPR
#define __TEST_FOR_VECTOR_EXPR

#ifndef __TEST_FOR_MATRIX_EXPR
#define MAT_EXPR1(a) (T_matrix(a * 2 + 1))
#define MAT_EXPR2(a) (T_matrix(a * 3 - 4))
#else
#define MAT_EXPR1(a) (a * 2 + 1)
#define MAT_EXPR2(a) (a * 3 - 4)
#endif

#define MAT_EXPR3(a, b) (a - b * 5 + 6)

#ifndef __TEST_FOR_VECTOR_EXPR
#define VEC_EXPR1(a) (T_vector(a * 2 + 1))
#define VEC_EXPR2(a) (T_vector(a * 3 - 4))
#else
#define VEC_EXPR1(a) (a * 2 + 1)
#define VEC_EXPR2(a) (a * 3 - 4)
#endif

#define VEC_EXPR3(a, b) (a - b * 5 + 6)

void test_for_matrix() {

	cout << "Testing for Array<TinyMatrix>:" << endl;

	T_matrix M1;
	M1 = 1, 2, 3, 4, 5, 6;
	T_matrix M2 = MAT_EXPR1(M1);
	T_matrix M3 = MAT_EXPR2(M1);
	T_matrix M4 = MAT_EXPR3(M2, M1);
	cout << "M1 = " << M1 << endl;
	cout << "M2 = " << M2 << endl;
	cout << "M3 = " << M3 << endl;
	cout << "M4 = " << M4 << endl;

	cout << "Testing for 1d-Array:" << endl;

	//Here TinyMatrix is composite object like as Array in the left side
	T_array_2 A2(2, 3);
	A2 = MAT_EXPR1(M1);
	cout << A2 << endl;
	for (int k = 0; k < ROW; ++ k)
	for (int l = 0; l < COL; ++ l) { ISCLOSE(A2(k, l), M2(k, l)); }

	//Here we construct TinyMatrix as scalar value and fill Array
	T_array_1_of_matrix A1M(5);
	A1M = MAT_EXPR1(M1);
	cout << A1M << endl;
	for (int k = 0; k < ROW; ++ k)
	for (int l = 0; l < COL; ++ l)
	for (int i = 0; i < 5; ++ i) { ISCLOSE(A1M(i)(k, l), M2(k, l)); }

	//Partial assignment of a matrix expression
	A1M(Range(1, 3)) = MAT_EXPR2(M1);
	cout << A1M << endl;
	for (int k = 0; k < ROW; ++ k)
	for (int l = 0; l < COL; ++ l)
	for (int i = 0; i < 5; ++ i) {
		if ((i >= 1) && (i <= 3)) {
			ISCLOSE(A1M(i)(k, l), M3(k, l));
		}
		else {
			ISCLOSE(A1M(i)(k, l), M2(k, l));
		}
	}

	cout << "Testing for 2d-Array:" << endl;

	//Here we construct TinyMatrix as scalar value and fill Array
	T_array_2_of_matrix A2M(5, 4);
	A2M = MAT_EXPR1(M1);
	cout << A2M << endl;
	for (int k = 0; k < ROW; ++ k)
	for (int l = 0; l < COL; ++ l)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) { ISCLOSE(A2M(i, j)(k, l), M2(k, l)); }

	//Partial assignment of a matrix expression
	A2M(Range(2, 3), Range(1, 2)) = MAT_EXPR2(M1);
	cout << A2M << endl;
	for (int k = 0; k < ROW; ++ k)
	for (int l = 0; l < COL; ++ l)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) {
		if ((i >= 2) && (i <= 3) &&
		    (j >= 1) && (j <= 2)) {
			ISCLOSE(A2M(i, j)(k, l), M3(k, l));
		}
		else {
			ISCLOSE(A2M(i, j)(k, l), M2(k, l));
		}
	}

	//Check for array expression
	T_array_2_of_matrix A(5, 4);
	T_array_2_of_matrix B(5, 4);
	T_array_2_of_matrix C(5, 4);
	A = M1;
	B = M2;
	B(0, 3) = MAT_EXPR2(M1);
	B(4, 0) = M3;
	C = MAT_EXPR3(B, A);
	cout << C << endl;
	for (int k = 0; k < ROW; ++ k)
	for (int l = 0; l < COL; ++ l)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) {
		ISCLOSE(C(i, j)(k, l), MAT_EXPR3(B(i, j)(k, l), A(i, j)(k, l)));
	}
}

void test_for_vector() {

	cout << "Testing for Array<TinyVector>:" << endl;

	T_vector V1(1, 2, 3);
	T_vector V2 = VEC_EXPR1(V1);
	T_vector V3 = VEC_EXPR2(V1);
	T_vector V4 = VEC_EXPR3(V2, V1);
	cout << "V1 = " << V1 << endl;
	cout << "V2 = " << V2 << endl;
	cout << "V3 = " << V3 << endl;
	cout << "V4 = " << V4 << endl;

	cout << "Testing for 1d-Array:" << endl;

	//Here TinyVector is composite object like as Array in the left side
	T_array_1 A1(3);
	A1 = VEC_EXPR1(V1);
	cout << A1 << endl;
	for (int k = 0; k < COL; ++ k) { ISCLOSE(A1(k), V2(k)); }

	//Here we construct TinyVector as scalar value and fill Array
	T_array_1_of_vector A1V(5);
	A1V = VEC_EXPR1(V1);
	cout << A1V << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i) { ISCLOSE(A1V(i)(k), V2(k)); }

	//Partial assignment of a vector expression
	A1V(Range(1, 3)) = VEC_EXPR2(V1);
	cout << A1V << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i) {
		if ((i >= 1) && (i <= 3)) {
			ISCLOSE(A1V(i)(k), V3(k));
		}
		else {
			ISCLOSE(A1V(i)(k), V2(k));
		}
	}

	//Check for component wise assignment
	for (int k = 0; k < COL; ++ k) {
		A1V[k] = V4(k);
	}
	cout << A1V << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i) { ISCLOSE(A1V(i)(k), V4(k)); }

	cout << "Testing for 2d-Array:" << endl;

	//Here we construct TinyVector as scalar value and fill Array
	T_array_2_of_vector A2V(5, 4);
	A2V = VEC_EXPR1(V1);
	cout << A2V << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) { ISCLOSE(A2V(i, j)(k), V2(k)); }

	//Partial assignment of a vector expression
	A2V(Range(2, 3), Range(1, 2)) = VEC_EXPR2(V1);
	cout << A2V << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) {
		if ((i >= 2) && (i <= 3) &&
		    (j >= 1) && (j <= 2)) {
			ISCLOSE(A2V(i, j)(k), V3(k));
		}
		else {
			ISCLOSE(A2V(i, j)(k), V2(k));
		}
	}

	//Check for component wise assignment
	for (int k = 0; k < COL; ++ k) {
		A2V[k] = V4(k);
	}
	cout << A2V << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) { ISCLOSE(A2V(i, j)(k), V4(k)); }

	//Check for array expression
	T_array_2_of_vector A(5, 4);
	T_array_2_of_vector B(5, 4);
	T_array_2_of_vector C(5, 4);
	A = V1;
	B = V2;
	B(0, 3) = VEC_EXPR2(V1);
	B(4, 0) = V3;
	C = VEC_EXPR3(B, A);
	cout << C << endl;
	for (int k = 0; k < COL; ++ k)
	for (int i = 0; i < 5; ++ i)
	for (int j = 0; j < 4; ++ j) {
		ISCLOSE(C(i, j)(k), VEC_EXPR3(B(i, j)(k), A(i, j)(k)));
	}
}

int main() {
	test_for_matrix();
	test_for_vector();
	return 0;
}
