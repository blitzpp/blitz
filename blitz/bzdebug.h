// -*- C++ -*-
/***************************************************************************
 * blitz/bzdebug.h      Debugging macros
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

#ifndef BZ_DEBUG_H
#define BZ_DEBUG_H

#ifdef BZ_HAVE_STD
  #include <cstdlib>
  #include <cassert>
#else
  #include <stdlib.h>
  #include <assert.h>
#endif

#ifdef BZ_HAVE_RTTI
 #include <typeinfo>
#endif

namespace blitz {

/*
 * These globals are used by the Blitz++ testsuite.  The _bz_global 
 * modifier ensures that they will reside in libblitz.a, but appear
 * "extern" elsewhere.
 */

_bz_global bool assertFailMode     BZ_GLOBAL_INIT(false);
_bz_global int  assertFailCount    BZ_GLOBAL_INIT(0);
_bz_global int  assertSuccessCount BZ_GLOBAL_INIT(0);


#if defined(BZ_TESTSUITE)
  /*
   * In testsuite mode, these routines allow a test suite to check
   * that precondition checking is being done properly.  A typical
   * use looks like this:
   *
   * beginCheckAssert();
   *   // Some operation which should cause an assert to fail
   * endCheckAssert();
   *
   * The routine beginCheckAssert() sets a flag which results in
   * failed asserts being silently tallied.  If no asserts have
   * failed by the time endCheckAssert() is invoked, the program
   * halts and issues an error code.
   *
   * In normal operation (i.e. when beginCheckAssert() has not
   * been called), failed preconditions will cause the program
   * to halt and issue an error code.   -- TV 980226
   */

  inline void checkAssert(bool condition, const char* where=0, 
    int line=0)
  {
    if (assertFailMode == true)
    {
      if (condition == true)
        ++assertSuccessCount;
      else
        ++assertFailCount;
    }
    else {
      if (!condition)
      {
        std::cerr << "Unexpected assert failure!" << std::endl;
        if (where)
            std::cerr << where << ":" << line << std::endl;
        std::cerr.flush();
        assert(0);
      }
    }
  }

  inline void beginCheckAssert()
  {
    assertFailMode = true;
    assertSuccessCount = 0;
    assertFailCount = 0;
  }

  inline void endCheckAssert()
  {
    assert(assertFailMode == true);
    assertFailMode = false;
    if (assertFailCount == 0)
    {
      std::cerr << "Assert check failed!" << std::endl;
      assert(0);
    }
  }

    #define BZASSERT(X)        blitz::checkAssert(X, __FILE__, __LINE__)
    #define BZPRECONDITION(X)  blitz::checkAssert(X, __FILE__, __LINE__)
    #define BZPOSTCONDITION(X) blitz::checkAssert(X, __FILE__, __LINE__)
    #define BZSTATECHECK(X,Y)  blitz::checkAssert(X == Y, __FILE__, __LINE__)
    #define BZPRECHECK(X,Y)                                    \
        {                                                      \
            if ((assertFailMode == false) && (!(X)))           \
                std::cerr << Y << std::endl; \
            blitz::checkAssert(X, __FILE__, __LINE__);         \
        }

    #define BZ_DEBUG_MESSAGE(X)                                          \
        {                                                                \
            if (assertFailMode == false)                                 \
            {                                                            \
                std::cout << __FILE__ << ":" << __LINE__ << " " \
                                   << X << std::endl;           \
            }                                                            \
        }

    #define BZ_DEBUG_PARAM(X) X
    #define BZ_PRE_FAIL        blitz::checkAssert(0)
    #define BZ_ASM_DEBUG_MARKER

#elif defined(BZ_DEBUG)

    #define BZASSERT(X)        assert(X)
    #define BZPRECONDITION(X)  assert(X)
    #define BZPOSTCONDITION(X) assert(X)
    #define BZSTATECHECK(X,Y)  assert(X == Y)
    #define BZPRECHECK(X,Y)                                                 \
        { if (!(X))                                                         \
          { std::cerr << "[Blitz++] Precondition failure: Module " \
                               << __FILE__                                  \
               << " line " << __LINE__ << std::endl                \
               << Y << std::endl;                                  \
            std::cerr.flush();                                     \
            assert(0);                                                      \
          }                                                                 \
        }

    #define BZ_DEBUG_MESSAGE(X)                                    \
        { std::cout << __FILE__ << ":" << __LINE__ << " " \
                             << X << std::endl; }

    #define BZ_DEBUG_PARAM(X) X
    #define BZ_PRE_FAIL      assert(0)

// This routine doesn't exist anywhere; it's used to mark a
// position of interest in assembler (.s) files
    void _bz_debug_marker();
    #define BZ_ASM_DEBUG_MARKER   _bz_debug_marker();

#else   // !BZ_TESTSUITE && !BZ_DEBUG

    #define BZASSERT(X)
    #define BZPRECONDITION(X)
    #define BZPOSTCONDITION(X)
    #define BZSTATECHECK(X,Y)
    #define BZPRECHECK(X,Y)
    #define BZ_DEBUG_MESSAGE(X)
    #define BZ_DEBUG_PARAM(X)
    #define BZ_PRE_FAIL
    #define BZ_ASM_DEBUG_MARKER

#endif  // !BZ_TESTSUITE && !BZ_DEBUG

#define BZ_NOT_IMPLEMENTED()                                     \
    { std::cerr << "[Blitz++] Not implemented: module " \
    << __FILE__ << " line " << __LINE__ << std::endl;   \
    std::exit(1); }

#ifdef BZ_HAVE_RTTI
#define BZ_DEBUG_TEMPLATE_AS_STRING_LITERAL(X) typeid(X).name()
#else

template<typename T>
class _bz_stringLiteralForNumericType {
public:
    static const char* string()
    { return "unknown"; }
};

#define BZ_DECL_SLFNT(X,Y) \
 template<>                 \
 class _bz_stringLiteralForNumericType< X > {  \
 public:                                       \
     static const char* string()               \
     { return Y; }                             \
 }

#ifdef BZ_HAVE_BOOL
BZ_DECL_SLFNT(bool, "bool");
#endif

BZ_DECL_SLFNT(char, "char");
BZ_DECL_SLFNT(unsigned char, "unsigned char");
BZ_DECL_SLFNT(short int, "short int");
BZ_DECL_SLFNT(short unsigned int, "short unsigned int");
BZ_DECL_SLFNT(int, "int");
BZ_DECL_SLFNT(unsigned int, "unsigned int");
BZ_DECL_SLFNT(long, "long");
BZ_DECL_SLFNT(unsigned long, "unsigned long");
BZ_DECL_SLFNT(float, "float");
BZ_DECL_SLFNT(double, "double");
BZ_DECL_SLFNT(long double, "long double");

#ifdef BZ_HAVE_COMPLEX
BZ_DECL_SLFNT(complex<float>, "complex<float>");
BZ_DECL_SLFNT(complex<double>, "complex<double>");
BZ_DECL_SLFNT(complex<long double>, "complex<long double>");
#endif

#define BZ_DEBUG_TEMPLATE_AS_STRING_LITERAL(X) \
    _bz_stringLiteralForNumericType<X>::string()

#endif // !BZ_HAVE_RTTI

}

#endif // BZ_DEBUG_H
