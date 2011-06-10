/***************************************************************************
 * blitz/memblock.cc      MemoryBlock<T> and MemoryBlockReference<T> methods
 *
 * $Id$
 *
 * Copyright (C) 1997-2011 Todd Veldhuizen <tveldhui@acm.org>
 *
 * This file is a part of Blitz.
 *
 * Blitz is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Blitz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with Blitz.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Suggestions:          blitz-devel@lists.sourceforge.net
 * Bugs:                 blitz-support@lists.sourceforge.net    
 *
 * For more information, please see the Blitz++ Home Page:
 *    https://sourceforge.net/projects/blitz/
 *
 ***************************************************************************/
#ifndef BZ_MEMBLOCK_CC
#define BZ_MEMBLOCK_CC

#include <blitz/numtrait.h>

BZ_NAMESPACE(blitz)

template<typename P_type>
void MemoryBlock<P_type>::deallocate()
{
#ifndef BZ_ALIGN_BLOCKS_ON_CACHELINE_BOUNDARY
  if(allocatedByUs_)
    delete [] dBA_tv_;
  else
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

    //assert(length%simdTypes<P_type>::vecWidth==0);

#ifndef BZ_ALIGN_BLOCKS_ON_CACHELINE_BOUNDARY
    BZASSERT(length%simdTypes<P_type>::vecWidth==0);
    dBA_tv_ = 
      new typename simdTypes<P_type>::vecType[length/simdTypes<P_type>::vecWidth];
    data_= dataBlockAddress_;
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
