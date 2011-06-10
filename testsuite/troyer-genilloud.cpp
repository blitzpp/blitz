// #define BZ_DEBUG_LOG_ALLOCATIONS
#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    float data[4] = { 1.0, 2.0, 3.0, 4.0 };

    {
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "Normal array ctor: " << endl;
#endif
        Array<float,1> A(4);
    }

    {
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "Old ctor version:" << endl;
#endif
        Array<float,1> A(data,shape(4));
    }

    {
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "duplicateData:" << endl;
#endif
        Array<float,1> A(data,shape(4),duplicateData);
    }

    {
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "neverDeleteData:" << endl;
#endif
        Array<float,1> A(data,shape(4),neverDeleteData);
    }

    {
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "deleteDataWhenDone:" << endl;
#endif
        Array<float,1> A(new float[4], shape(4), deleteDataWhenDone);
    }

    if(BZ_SIMD_WIDTH>sizeof(float)) {
    // check that block size test works
	beginCheckAssert();
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "uneven block size deleteDataWhenDone:" << endl;
#endif
	float* p=new float[1];	
        Array<float,1> A(p, shape(1), deleteDataWhenDone);
	endCheckAssert();
    }
    if(BZ_SIMD_WIDTH>sizeof(float)) {
    // we can't actually check that the misalignment test works,
    // because that catches the assert and causes a segfault since we
    // free an incorrect pointer.
#ifdef BZ_DEBUG_LOG_ALLOCATIONS
        cout << endl << "misaligned deleteDataWhenDone:" << endl;
#endif
	// beginCheckAssert():
	// float* p=new float[simdTypes<float>::vecWidth+1];	
        // Array<float,1> A(p+1, shape(simdTypes<float>::vecWidth),
	// 		 deleteDataWhenDone);
	// endCheckAssert();
    }
}

