/* A C-program for MT19937: Integer version (1998/4/6)            */
/*  genrand() generates one pseudorandom unsigned integer (32bit) */
/* which is uniformly distributed among 0 to 2^32-1  for each     */
/* call. sgenrand(seed) set initial values to the working area    */
/* of 624 words. Before genrand(), sgenrand(seed) must be         */
/* called once. (seed is any 32-bit integer except for 0).        */
/*   Coded by Takuji Nishimura, considering the suggestions by    */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.              */

/* This library is free software; you can redistribute it and/or   */
/* modify it under the terms of the GNU Library General Public     */
/* License as published by the Free Software Foundation; either    */
/* version 2 of the License, or (at your option) any later         */
/* version.                                                        */
/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
/* See the GNU Library General Public License for more details.    */
/* You should have received a copy of the GNU Library General      */
/* Public License along with this library; if not, write to the    */
/* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */ 
/* 02111-1307  USA                                                 */

/* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
/* When you use this, send an email to: matumoto@math.keio.ac.jp   */
/* with an appropriate reference to your work.                     */

/* REFERENCE                                                       */
/* M. Matsumoto and T. Nishimura,                                  */
/* "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform  */
/* Pseudo-Random Number Generator",                                */
/* ACM Transactions on Modeling and Computer Simulation,           */
/* Vol. 8, No. 1, January 1998, pp 3--30.                          */

// See http://www.math.keio.ac.jp/~matumoto/emt.html
// And http://www.acm.org/pubs/citations/journals/tomacs/1998-8-1/p3-matsumoto/

// 1999-01-25 adapted to STL-like idiom
// allan@stokes.ca (Allan Stokes) www.stokes.ca

/*
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/01/26 19:52:34  tveldhui
 * Incorporated changes from Max Domeika for STL compatibility.
 *
 */

#ifndef BZ_RAND_MT
#define BZ_RAND_MT

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

#include <vector>

#ifndef UINT_MAX
  #include <limits.h>
#endif

BZ_NAMESPACE(ranlib)

class MersenneTwister
{
public:

#if UINT_MAX < 4294967295U
  typedef unsigned long twist_int;  // must be at least 32 bits
#else
  typedef unsigned int twist_int;
#endif

private:

#if defined(BZ_NAMESPACES) && defined(BZ_HAVE_STD)
  typedef std::vector<twist_int> State;
#else
  typedef vector<twist_int> State;
#endif

  typedef State::iterator Iter;

  struct BitMixer {
    enum { K = 0x9908b0df };
    BitMixer() : s0(0) {}
    inline twist_int low_mask (twist_int s1) const {
      return (s1&1u) ? K : 0u;
    }
    inline twist_int high_mask (twist_int s1) const {
      return ((s0&0x80000000)|(s1&0x7fffffff))>>1;
    }
    inline twist_int operator() (twist_int s1) {
      twist_int r = high_mask(s1) ^ low_mask(s1);
      s0 = s1;
      return r;
    }
    twist_int s0;
  };

enum { N = 624, PF = 397, reference_seed = 4357 }; 
 
  void initialize()
  {
    S.resize(N);
    I = S.end();
  }
 
public: 
  MersenneTwister()
  {
    initialize();
    seed();

    // There is a problem: static initialization + templates do not
    // mix very well in C++.  If you have a static member
    // of a class template, there is no guarantee on its order iin
    // static initialization.  This MersenneTwister class is used
    // elsewhere as a static member of a template class, and it is
    // possible (in fact, I've done so) to create a static initializer
    // that will invoke the seed() method of this object before its
    // ctor has been called (result: crash). 
    // ANSI C++ is stranger than fiction.
    // Currently the documentation forbids using RNGs from
    // static initializers.  There doesn't seem to be a good
    // fix.
  }

  MersenneTwister(twist_int initial_seed)
  {
    initialize();
    seed(initial_seed);
  }

  void seed (twist_int seed = reference_seed)
  {
    // seed cannot equal 0
    if (seed == 0)
      seed = reference_seed;

    enum { Knuth_A = 69069 }; 
    twist_int x = seed & 0xFFFFFFFF;
    Iter s = S.begin();
    twist_int mask = (seed == reference_seed) ? 0 : 0xFFFFFFFF;
    for (int j = 0; j < N; ++j) {
      // adding j here avoids the risk of all zeros 
      // we suppress this term in "compatibility" mode  
      *s++ = (x + (mask & j)) & 0xFFFFFFFF; 
      x *= Knuth_A;
    }

    reload();
  }

  void reload (void)
  {
    // This check is required because it is possible to call random()
    // before the constructor.  See the note above about static
    // initialization.

    Iter p0 = S.begin();
    Iter pM = p0 + PF;
    BitMixer twist;
    twist (S[0]); // prime the pump
    for (Iter pf_end = (Iter)&S[N-PF]; p0 != pf_end; ++p0, ++pM)
      *p0 = *pM ^ twist (p0[1]);
    pM = S.begin();
    for (Iter s_end = (Iter)&S[N-1]; p0 != s_end; ++p0, ++pM)
      *p0 = *pM ^ twist (p0[1]);
    *p0 = *pM ^ twist (S[0]);

    I = S.begin();
  }

  inline twist_int random (void)
  {
    if (I >= S.end()) reload();
    twist_int y = *I++;
    y ^= (y >> 11);
    y ^= (y <<  7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= (y >> 18);
    return y;
  }

private:
  State   S;
  Iter    I;
};


BZ_NAMESPACE_END

#endif // BZ_RAND_MT
