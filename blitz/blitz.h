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
 ***************************************************************************
 * $Log$
 * Revision 1.7  2001/02/11 22:03:44  tveldhui
 * Fixed minor typo in blitz.h
 *
 * Revision 1.6  2001/02/04 22:36:41  tveldhui
 * Oops, was including <pthread.h> inside the blitz namespace.
 *
 * Revision 1.5  2001/02/04 16:32:28  tveldhui
 * Made memory block reference counting (optionally) threadsafe when
 * BZ_THREADSAFE is defined.  Currently uses pthread mutex.
 * When compiling with gcc -pthread, _REENTRANT automatically causes
 * BZ_THREADSAFE to be enabled.
 *
 * Revision 1.4  2001/01/26 18:30:50  tveldhui
 * More source code reorganization to reduce compile times.
 *
 * Revision 1.3  2001/01/24 22:51:50  tveldhui
 * Reorganized #include orders to avoid including the huge Vector e.t.
 * implementation when using Array.
 *
 * Revision 1.2  2001/01/24 20:22:49  tveldhui
 * Updated copyright date in headers.
 *
 * Revision 1.1.1.1  2000/06/19 12:26:08  tveldhui
 * Imported sources
 *
 * Revision 1.7  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.6  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.5  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 * Revision 1.4  1997/01/23 03:28:28  tveldhui
 * Periodic RCS update
 *
 * Revision 1.3  1997/01/13 22:19:58  tveldhui
 * Periodic RCS update
 *
 * Revision 1.2  1996/11/11 17:29:13  tveldhui
 * Periodic RCS update
 *
 * Revision 1.1  1996/04/14  21:13:00  todd
 * Initial revision
 *
 */

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

#include <string>
#include <stdio.h>                   // sprintf, etc.

#ifdef BZ_HAVE_STD
  #include <iostream>
  #include <iomanip>
#else
  #include <iostream.h>
  #include <iomanip.h>
#endif

#ifdef BZ_MATH_FN_IN_NAMESPACE_STD 
  #include <cmath>
#endif

#include <math.h>

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

#ifdef _REENTRANT
 #define BZ_THREADSAFE
#endif

#ifdef BZ_THREADSAFE
#define BZ_THREADSAFE_USE_PTHREADS

#ifdef BZ_THREADSAFE_USE_PTHREADS
 #include <pthread.h>

 #define BZ_MUTEX_DECLARE(name)   pthread_mutex_t name
 #define BZ_MUTEX_INIT(name)      pthread_mutex_init(&name,NULL)
 #define BZ_MUTEX_LOCK(name)      pthread_mutex_lock(&name)
 #define BZ_MUTEX_UNLOCK(name)    pthread_mutex_unlock(&name)
 #define BZ_MUTEX_DESTROY(name)   pthread_mutex_destroy(&name)
#else
 #define BZ_MUTEX_DECLARE(name)
 #define BZ_MUTEX_INIT(name)
 #define BZ_MUTEX_LOCK(name)
 #define BZ_MUTEX_UNLOCK(name)
 #define BZ_MUTEX_DESTROY(name)
#endif

#endif  // BZ_THREADSAFE

#include <blitz/bzdebug.h>           // Debugging macros

#endif // BZ_BLITZ_H
