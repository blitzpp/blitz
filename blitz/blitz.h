// -*- C++ -*-
/***************************************************************************
 * blitz/blitz.h      Includes all the important header files
 *
 * $Id$
 *
 * Copyright (C) 1997-2001 Todd Veldhuizen <tveldhui@oonumerics.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * Suggestions:          blitz-dev@oonumerics.org
 * Bugs:                 blitz-bugs@oonumerics.org    
 *
 * For more information, please see the Blitz++ Home Page:
 *    http://oonumerics.org/blitz/
 *
 ***************************************************************************/

#ifndef BZ_BLITZ_H
#define BZ_BLITZ_H

/*
 * These symbols allow use of the IEEE and System V math libraries
 * (libm.a and libmsaa.a) on some platforms.
 */

#ifdef BZ_ENABLE_XOPEN_SOURCE
 #ifndef _ALL_SOURCE
  #define _ALL_SOURCE
 #endif
 #ifndef _XOPEN_SOURCE
  #define _XOPEN_SOURCE
 #endif
 #ifndef _XOPEN_SOURCE_EXTENDED
  #define _XOPEN_SOURCE_EXTENDED 1
 #endif
#endif

#include <blitz/compiler.h>          // Compiler-specific directives
#include <blitz/tuning.h>            // Performance tuning
#include <blitz/tau.h>               // Profiling

#ifdef BZ_HAVE_STL
  #include <string>
#endif

#ifdef BZ_HAVE_STD
  #include <iostream>
  #include <iomanip>
  #include <cstdio>                    // sprintf, etc.
  #include <cmath>
#else
  #include <iostream.h>
  #include <iomanip.h>
  #include <stdio.h>                   // sprintf, etc.
  #include <math.h>
#endif

#ifdef BZ_HAVE_COMPLEX
  #include <complex>
#endif

#define BZ_THROW                     // Needed in <blitz/numinquire.h>

BZ_NAMESPACE(blitz)

#ifdef BZ_HAVE_STD
 BZ_USING_NAMESPACE(std)
#endif

#ifdef BZ_GENERATE_GLOBAL_INSTANCES
 #define _bz_global
 #define BZ_GLOBAL_INIT(X)   =X
#else
 #define _bz_global extern
 #define BZ_GLOBAL_INIT(X) 
#endif

BZ_NAMESPACE_END

/*
 * Thread safety issues.
 * Compiling with -pthread under gcc, or -mt under solaris,
 * should automatically define _REENTRANT. Also have support
 * for OpenMP (which defines _OPENMP) or Windows thread implementation.
 * The --enable-threadsafe configure option now defines BZ_THREADSAFE.
 */

/*
 * Which mutex implementation should be used for synchronizing
 * reference counts.  Options are pthreads, OpenMP, or Windows threads.
 */
#ifdef BZ_THREADSAFE
 #if defined(_REENTRANT)
  #define BZ_THREADSAFE_USE_PTHREADS
 #elif defined (_OPENMP)
  #define BZ_THREADSAFE_USE_OPENMP
 #elif defined(_WIN32)
  #define BZ_THREADSAFE_USE_WINDOWS
 #endif
#endif

#ifdef BZ_THREADSAFE_USE_PTHREADS
 #include <pthread.h>

 #define BZ_MUTEX_DECLARE(name)   mutable pthread_mutex_t name;
 #define BZ_MUTEX_INIT(name)      pthread_mutex_init(&name,NULL);
 #define BZ_MUTEX_LOCK(name)      pthread_mutex_lock(&name);
 #define BZ_MUTEX_UNLOCK(name)    pthread_mutex_unlock(&name);
 #define BZ_MUTEX_DESTROY(name)   pthread_mutex_destroy(&name);
#elif defined (BZ_THREADSAFE_USE_WINDOWS)
 // Include Windows.h header in case user has not already done so.
 // Disable Windows min/max macro definitions
 #define NOMINMAX
 #include <Windows.h>

 #define BZ_MUTEX_DECLARE(name)   mutable CRITICAL_SECTION name;
 #define BZ_MUTEX_INIT(name)      ::InitializeCriticalSection(&name);
 #define BZ_MUTEX_LOCK(name)      ::EnterCriticalSection(&name);
 #define BZ_MUTEX_UNLOCK(name)    ::LeaveCriticalSection(&name);
 #define BZ_MUTEX_DESTROY(name)   ::DeleteCriticalSection(&name);
#elif defined (BZ_THREADSAFE_USE_OPENMP)
 #include <omp.h>

 #define BZ_MUTEX_DECLARE(name)   mutable omp_lock_t name;
 #define BZ_MUTEX_INIT(name)      omp_init_lock(&name);
 #define BZ_MUTEX_LOCK(name)      omp_set_lock(&name);
 #define BZ_MUTEX_UNLOCK(name)    omp_unset_lock(&name);
 #define BZ_MUTEX_DESTROY(name)   omp_destroy_lock(&name);
#else
 #define BZ_MUTEX_DECLARE(name)
 #define BZ_MUTEX_INIT(name)
 #define BZ_MUTEX_LOCK(name)
 #define BZ_MUTEX_UNLOCK(name)
 #define BZ_MUTEX_DESTROY(name)
#endif

#include <blitz/bzdebug.h>           // Debugging macros

#endif // BZ_BLITZ_H
