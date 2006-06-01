/*
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 */

#ifndef BZ_MATRIX_CC
#define BZ_MATRIX_CC

#ifndef BZ_MATRIX_H
 #include <blitz/matrix.h>
#endif

BZ_NAMESPACE(blitz)

// Matrix expression operand
template<typename P_numtype, typename P_structure> template<typename P_expr>
Matrix<P_numtype, P_structure>& 
Matrix<P_numtype, P_structure>::operator=(_bz_MatExpr<P_expr> expr)
{
    // Check for compatible structures.

    // Fast evaluation (compatible structures)
    // (not implemented)

    // Slow evaluation
    _bz_typename P_structure::T_iterator iter(rows(), cols());
    while (iter)
    {
        data_[iter.offset()] = expr(iter.row(), iter.col());
        ++iter;
    }

    return *this;
}

template<typename P_numtype, typename P_structure>
ostream& operator<<(ostream& os, const Matrix<P_numtype, P_structure>& matrix)
{
    os << matrix.rows() << " x " << matrix.columns() << endl;
    os << "[ ";
    for (int i=0; i < matrix.rows(); ++i)
    {
        for (int j=0; j < matrix.columns(); ++j)
        {
            os << matrix(i,j) << " ";
        }
        if (i != matrix.rows() - 1)
            os << endl << "  ";
    }
    os << "]";
    return os;
}

template<typename P_numtype, typename P_structure>
istream& operator>>(istream& is, Matrix<P_numtype, P_structure>& matrix)
{
    unsigned rows, columns;
    char sep;

    is >> rows;
    BZPRECHECK(!is.bad(), "Premature end of input while scanning Matrix");
    is >> sep;
    BZPRECHECK(sep == 'x', "Format error while scanning input \
Matrix \n (expected 'x' between Matrix extents)");
    is >> columns;
    BZPRECHECK(!is.bad(), "Premature end of input while scanning Matrix");
    matrix.resize(rows,columns);

    is >> sep;
    BZPRECHECK(sep == '[', "Format error while scanning input \
Matrix \n (expected '[' before beginning of Matrix data)");
    for (int i=0; i < matrix.rows(); ++i) {
        for (int j=0; j < matrix.columns(); ++j) {
            BZPRECHECK(!is.bad(), "Premature end of input while scanning Matrix");
            is >> matrix(i,j);
        }
    }

    is >> sep;
    BZPRECHECK(sep == ']', "Format error while scanning input \
Matrix \n (expected ']' after end of Matrix data)");
    return is;
}

BZ_NAMESPACE_END

#endif // BZ_MATRIX_CC
