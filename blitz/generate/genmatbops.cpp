/*
 * $Id$
 *
 * $Log$
 * Revision 1.2  2002/06/28 23:59:49  jcumming
 * Files for generating Matrix operators and math functions.
 *
 *
 */

#include <iostream.h>
#include <fstream.h>
#include "optuple2.h"

int main()
{
    cout << "Generating <matbops.h>" << endl;

    OperandTuple2 operands(2);

    ofstream ofs("matbops.h");
    ofs << "// Generated source file.  Do not edit." << endl;
    ofs << "// Created by: " << __FILE__ << " " << __DATE__ 
        << " " << __TIME__ << endl << endl;

    ofs << "#ifndef BZ_MATBOPS_H" << endl
        << "#define BZ_MATBOPS_H" << endl
        << endl << "BZ_NAMESPACE(blitz)" << endl << endl
        << "#ifndef BZ_MATEXPR_H" << endl
        << " #error <blitz/matbops.h> must be included via <blitz/matexpr.h>" 
        << endl << "#endif" << endl << endl;

    struct {
        const char* opSymbol;
        bool        nonIntOperands;
        bool        complexOperands;
        const char* opApplicName;
        const char* comment;
    } ops[] = {
     { "+",  true,  true,  "_bz_Add",            "Addition Operators" },
     { "-",  true,  true,  "_bz_Subtract",       "Subtraction Operators" },
     { "*",  true,  true,  "_bz_Multiply",       "Multiplication Operators" },
     { "/",  true,  true,  "_bz_Divide",         "Division Operators" },
     { "%",  false, false, "_bz_Mod",            "Modulus Operators" },
     { "^",  false, false, "_bz_BitwiseXOR",     "Bitwise XOR Operators" },
     { "&",  false, false, "_bz_BitwiseAnd",     "Bitwise And Operators" },
     { "|",  false, false, "_bz_BitwiseOr",      "Bitwise Or Operators" },
     { ">>", false, false, "_bz_ShiftRight",     "Shift right Operators" },
     { "<<", false, false, "_bz_ShiftLeft",      "Shift left Operators" },
     { ">",  true,  false, "_bz_Greater",        "Greater-than Operators" },
     { "<",  true,  false, "_bz_Less",           "Less-than Operators" },
     { ">=", true,  false, "_bz_GreaterOrEqual", "Greater or equal (>=) operators" },
     { "<=", true,  false, "_bz_LessOrEqual",    "Less or equal (<=) operators" },
     { "==", true,  true,  "_bz_Equal",          "Equality operators" },
     { "!=", true,  true,  "_bz_NotEqual",       "Not-equal operators" },
     { "&&", false, false, "_bz_LogicalAnd",     "Logical AND operators" },
     { "||", false, false, "_bz_LogicalOr",      "Logical OR operators" }
    };

    for (int i=0; i < 18; ++i)
    {
    ofs << "/****************************************************************************" << endl
        << " * " << ops[i].comment << endl
        << " ****************************************************************************/" << endl;

    operands.reset();

    do {
        if (ops[i].nonIntOperands == false)
        {
            if ((operands[0].isScalar() && !operands[0].isInteger())
             || (operands[1].isScalar() && !operands[1].isInteger()))
                continue;
        }

        // Matrix<P_numtype1> + _bz_MatExpr<P_expr2>

        if (operands.anyComplex())
            ofs << "#ifdef BZ_HAVE_COMPLEX" << endl;

        ofs << endl << "// ";
        operands[0].printName(ofs);
        ofs << " " << ops[i].opSymbol << " ";
        operands[1].printName(ofs);
        ofs << endl;

        operands.printTemplates(ofs);
        ofs << endl << "inline" << endl;

        // _bz_MatExpr<_bz_MatExprOp<MatRef<T_numtype1>,
        //     _bz_MatExpr<T_expr2>, _bz_Add<T_numtype1, _bz_typename T_expr2::T_numtype> > >
        ofs << "_bz_MatExpr<_bz_MatExprOp<";
        operands.printIterators(ofs, 1);
        ofs << "," << endl << "      " << ops[i].opApplicName << "<";
        operands[0].printNumtype(ofs);
        ofs << ", ";    
        operands[1].printNumtype(ofs);
        ofs << " > > >" << endl;
     
        // operator+(const Matrix<T_numtype1>& d1, _bz_MatExpr<T_expr2> d2)
        ofs << "operator" << ops[i].opSymbol << "(";
        operands.printArgumentList(ofs, 1);
        ofs << ")" << endl << "{" << endl;

        // typedef _bz_MatExprOp<MatRef<T_numtype1>,
        // _bz_MatExpr<T_expr2>, _bz_Add<T_numtype1, _bz_typename T_expr2::T_numtype> > T_expr;
        ofs << "    typedef _bz_MatExprOp<";
        operands.printIterators(ofs, 1);
        ofs << ", " << endl << "      " << ops[i].opApplicName << "<";
        operands[0].printNumtype(ofs);
        ofs << ", ";
        operands[1].printNumtype(ofs);
        ofs << "> > T_expr;" << endl << endl;

        // return _bz_MatExpr<T_expr>(T_expr(a.begin(), b));
        ofs << "    return _bz_MatExpr<T_expr>(T_expr(";
        operands.printInitializationList(ofs,1);
        ofs << "));" << endl << "}" << endl;

        if (operands.anyComplex())
            ofs << "#endif // BZ_HAVE_COMPLEX" << endl << endl;

    } while (++operands);
    
    }

    ofs << endl << "BZ_NAMESPACE_END" << endl << endl
        << "#endif // BZ_MATBOPS_H" << endl;

   cout << operands.numSpecializations() << " operators written." << endl;
}

