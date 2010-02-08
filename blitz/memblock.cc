/*
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 */

#ifndef BZ_MEMBLOCK_CC
#define BZ_MEMBLOCK_CC

#include <blitz/numtrait.h>

BZ_NAMESPACE(blitz)

template<typename P_type>
void MemoryBlock<P_type>::deallocate()
{
#ifndef BZ_ALIGN_BLOCKS_ON_CACHELINE_BOUNDARY
    delete [] dataBlockAddress_;
#else
    if (!NumericTypeTraits<T_type>::hasTrivialCtor) {
        for (int i=0; i < length_; ++i)
            data_[i].~T_type();
        delete [] reinterpret_cast<char*>(dataBlockAddress_);
    }
    else {
        delete [] dataBlockAddress_;
    }
#endif
}

template<typename P_type>
inline void MemoryBlock<P_type>::allocate(sizeType length)
{
    TAU_TYPE_STRING(p1, "MemoryBlock<T>::allocate() [T="
        + CT(P_type) + "]");
    TAU_PROFILE(p1, "void ()", TAU_BLITZ);

#ifndef BZ_ALIGN_BLOCKS_ON_CACHELINE_BOUNDARY
    dataBlockAddress_ = new T_type[length];
    data_ = dataBlockAddress_;
#else
    sizeType numBytes = length * sizeof(T_type);

    if (numBytes < 1024)
    {
        dataBlockAddress_ = new T_type[length];
        data_ = dataBlockAddress_;
    }
    else
    {
        // We're allocating a large array.  For performance reasons,
        // it's advantageous to force the array to start on a
        // cache line boundary.  We do this by allocating a little
        // more memory than necessary, then shifting the pointer
        // to the next cache line boundary.

        // Patches by Petter Urkedal to support types with nontrivial
        // constructors.

        const int cacheBlockSize = 128;    // Will work for 32, 16 also

        dataBlockAddress_ = reinterpret_cast<T_type*>
            (new char[numBytes + cacheBlockSize - 1]);

        // Shift to the next cache line boundary

        diffType offset = ptrdiff_t(dataBlockAddress_) % cacheBlockSize;
        diffType shift = (offset == 0) ? 0 : (cacheBlockSize - offset);
        data_ = reinterpret_cast<T_type*>
                (reinterpret_cast<char*>(dataBlockAddress_) + shift);

        // Use placement new to construct types with nontrival ctors
        if (!NumericTypeTraits<T_type>::hasTrivialCtor) {
            for (int i=0; i < length; ++i)
                new(&data_[i]) T_type;
        }
    }
#endif
}


BZ_NAMESPACE_END

#endif // BZ_MEMBLOCK_CC
