/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2000/06/19 13:02:48  tveldhui
 * Initial source check-in; added files not usually released in the
 * distribution.
 *
 *
 */

#include <iostream.h>
#include <fstream.h>
#include "bzfstream.h"
#include "arroptuple.h"

#ifdef NO_BOOL
 #define bool int
 #define true 1
 #define false 0
#endif

int main()
{
    cout << "Generating <arraybops.cc>" << endl;

    OperandTuple operands(2);

    bzofstream ofs("arraybops.cc", "Array expression templates (2 operands)",
        __FILE__, "BZ_ARRAYBOPS_CC");

    ofs << "#ifndef BZ_ARRAYEXPR_H" << endl
        << " #error <blitz/arraybops.cc> must be included after <blitz/arrayexpr.h>" 
        << endl << "#endif" << endl << endl;

    ofs.beginNamespace();

    struct {
        const char* opSymbol;
        bool        nonIntOperands;
        bool        complexOperands;
        const char* opApplicName;
        const char* comment;
    } ops[] = {
     { "+",  true,  true,  "Add",            "Addition Operators" },
     { "-",  true,  true,  "Subtract",       "Subtraction Operators" },
     { "*",  true,  true,  "Multiply",       "Multiplication Operators" },
     { "/",  true,  true,  "Divide",         "Division Operators" },
     { "%",  false, false, "Modulo",         "Modulus Operators" },
     { ">",  true,  false, "Greater",        "Greater-than Operators" },
     { "<",  true,  false, "Less",           "Less-than Operators" },
     { ">=", true,  false, "GreaterOrEqual", "Greater or equal (>=) operators" },
     { "<=", true,  false, "LessOrEqual",    "Less or equal (<=) operators" },
     { "==", true,  true,  "Equal",          "Equality operators" },
     { "!=", true,  true,  "NotEqual",       "Not-equal operators" },
     { "&&", false, false, "LogicalAnd",     "Logical AND operators" },
     { "||", false, false, "LogicalOr",      "Logical OR operators" },


     { "^",  false, false, "BitwiseXor",     "Bitwise XOR Operators" },
     { "&",  false, false, "BitwiseAnd",     "Bitwise And Operators" },
     { "|",  false, false, "BitwiseOr",      "Bitwise Or Operators" },
     { ">>", false, false, "ShiftRight",     "Shift right Operators" },
     { "<<", false, false, "ShiftLeft",      "Shift left Operators" }
    };

    const int numOperators = 18;   // Should be 18

    for (int i=0; i < numOperators; ++i)
    {
    ofs << "/****************************************************************************" << endl
        << " * " << ops[i].comment << endl
        << " ****************************************************************************/" << endl;

    operands.reset();

    do {
        // Can't declare operator+(int,Range) or operator+(Range,int)
        // because these would conflict with the versions defined
        // in range.h.  Also, the versions in range.h will be
        // much faster.
        if (operands[0].isScalar() && operands[0].isInteger()
            && operands[1].isRange())
                continue;
        if (operands[1].isScalar() && operands[1].isInteger()
            && operands[0].isRange())
                continue;

        if (ops[i].nonIntOperands == false)
        {
            if ((operands[0].isScalar() && !operands[0].isInteger())
             || (operands[1].isScalar() && !operands[1].isInteger()))
                continue;
        }

        ofs << endl;

        if (operands.anyComplex())
            ofs << "#ifdef BZ_HAVE_COMPLEX" << endl;

        ofs << "// ";
        operands[0].printName(ofs);
        ofs << " " << ops[i].opSymbol << " ";
        operands[1].printName(ofs);
        ofs << endl;

        operands.printTemplates(ofs);
        ofs << endl << "inline" << endl;

        ofs << "_bz_ArrayExpr<_bz_ArrayExprOp<";
        operands.printIterators(ofs, 1);
        ofs << "," << endl << "      " << ops[i].opApplicName << "<";
        operands[0].printNumtype(ofs);
        ofs << ", ";    
        operands[1].printNumtype(ofs);
        ofs << " > > >" << endl;
     
        // operator+(const Vector<T_numtype1>& d1, _bz_VecExpr<T_expr2> d2)
        ofs << "operator" << ops[i].opSymbol << "(";
        operands.printArgumentList(ofs, 1);
        ofs << ")" << endl << "{" << endl;

        ofs << "    return _bz_ArrayExprOp<";
        operands.printIterators(ofs, 1);
        ofs << ", " << endl << "      " << ops[i].opApplicName << "<";
        operands[0].printNumtype(ofs);
        ofs << ", ";
        operands[1].printNumtype(ofs);
        ofs << "> >" << endl;
        ofs << "      (";
        operands.printInitializationList(ofs,1);
        ofs << ");" << endl << "}" << endl;

        if (operands.anyComplex())
            ofs << "#endif // BZ_HAVE_COMPLEX" << endl;

    } while (++operands);

   }

   cout << operands.numSpecializations() << " operators written." << endl;
}

