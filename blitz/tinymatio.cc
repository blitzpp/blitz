/*
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 */

#ifndef BZ_TINYMATIO_CC
#define BZ_TINYMATIO_CC

#ifndef BZ_TINYMAT_H
 #include <blitz/tinymat.h>
#endif

BZ_NAMESPACE(blitz)

// NEEDS_WORK???
// This version of operator<< is updated on August 2005
// by Sergei Mingaleev <mingaleev@gmail.com>. 
// Also, the corresponding operator>> is updated.

template <typename P_numtype, int N_rows, int N_columns>
ostream& operator<<(ostream& os,
    const TinyMatrix<P_numtype, N_rows, N_columns>& x)
{
    os << "(";
    for (int i=0; i < N_rows-1; ++i) 
    {
        os << x(i,0);
        for (int j=1; j < N_columns; ++j)
        {
            os << "," << x(i,j);
        }
        os << "; ";
    }
    os << x(N_rows-1,0);
    for (int j=1; j < N_columns; ++j) 
    {
       os << "," << x(N_rows-1,j);
    }
    os << ")";
    return os;
}

template <typename P_numtype, int N_rows, int N_columns>
istream& operator>>(istream& is, 
    TinyMatrix<P_numtype, N_rows, N_columns>& x)
{
    char sep;
    is >> sep;
    BZPRECHECK(sep == '(', "Format error while scanning input TinyMatrix"
      << endl << " (expected '(' opening TinyMatrix)");

    for (int i=0; i<N_rows-1; i++) {
      is >> x(i,0);
      for (int j=1; j<N_columns; j++) {
        is >> sep;
        BZPRECHECK(sep == ',', "Format error while scanning input TinyMatrix" 
	  << endl << " (expected ',' between TinyMatrix components)");
        is >> x(i,j);
      }
      is >> sep;
      BZPRECHECK(sep == ';', "Format error while scanning input TinyMatrix"
        << endl << " (expected ';' between TinyMatrix rows)");
    }
    is >> x(N_rows-1,0);
    for (int j=1; j<N_columns; j++) {
      is >> sep;
      BZPRECHECK(sep == ',', "Format error while scanning input TinyMatrix"
        << endl << " (expected ',' between TinyMatrix components)");
      is >> x(N_rows-1,j);
    }
    is >> sep;
    BZPRECHECK(sep == ')', "Format error while scanning input TinyMatrix"
      << endl << " (expected ')' closing TinyMatrix)");

    return is;
}

BZ_NAMESPACE_END

#endif // BZ_TINYMATIO_CC

