/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2002/06/28 23:59:49  jcumming
 * Files for generating Matrix operators and math functions.
 *
 *
 */

#include <fstream.h>
#include <iostream.h>
#include <iomanip.h>
#include "optuple2.h"

const int ieeeflag = 1, bsdflag = 2;

ofstream ofs("matuops.h");

void two(const char* fname, int flag=0, const char* apname = 0)
{
    cout << "genmatuops.cpp: two() not implemented" << endl;
}

void one(const char* fname, int flag=0, const char* apname = 0)
{
    if (apname == 0)
        apname = fname;

    ofs << "/****************************************************************************" << endl
        << " * " << fname << endl
        << " ****************************************************************************/" << endl << endl;

    if (flag == ieeeflag)
        ofs << "#ifdef BZ_HAVE_IEEE_MATH" << endl;
    else if (flag == bsdflag)
        ofs << "#ifdef BZ_HAVE_SYSTEM_V_MATH" << endl;

    OperandTuple2 operands(1);

    do {
        operands.printTemplates(ofs);
        ofs << endl << "inline" << endl
            << "_bz_MatExpr<_bz_MatExprUnaryOp<";
        operands.printIterators(ofs);
        ofs << "," << endl << "    _bz_" << apname << "<";
        operands[0].printNumtype(ofs);
        ofs << "> > >" << endl
            << fname << "(";
        operands.printArgumentList(ofs);
        ofs << ")" << endl
            << "{" << endl
            << "    typedef _bz_MatExprUnaryOp<";
        operands.printIterators(ofs);
        ofs << "," << endl << "        _bz_" << apname << "<";
        operands[0].printNumtype(ofs);
        ofs << "> > T_expr;" << endl << endl
            << "    return _bz_MatExpr<T_expr>(T_expr(";
        operands.printInitializationList(ofs);
        ofs << "));" << endl
            << "}" << endl << endl;

    } while (++operands);
    
    if (flag != 0)
        ofs << "#endif" << endl;

    ofs << endl;
}

int main()
{
    cout << "Generating <matuops.h>" << endl;

    ofs << "// Generated source file.  Do not edit." << endl;
    ofs << "// Created by: " << __FILE__ << " " << __DATE__ 
        << " " << __TIME__ << endl << endl;

    ofs << "#ifndef BZ_MATUOPS_H" << endl
        << "#define BZ_MATUOPS_H" << endl
        << endl << "BZ_NAMESPACE(blitz)" << endl << endl
        << "#ifndef BZ_MATEXPR_H" << endl
        << " #error <blitz/matuops.h> must be included via <blitz/matexpr.h>" 
        << endl << "#endif" << endl << endl;

    one("abs");
    one("acos");
    one("acosh", ieeeflag);
    one("asin");
    one("asinh", ieeeflag);
    one("atan");
    two("atan2");
    one("atanh", ieeeflag);
    one("_class", bsdflag);
    one("cbrt", ieeeflag);
    one("ceil");
    two("copysign", bsdflag);
    one("cos");
    one("cosh");
    two("drem", bsdflag);
    one("exp");
    one("expm1", ieeeflag);
    one("erf", ieeeflag);
    one("erfc", ieeeflag);
    one("fabs", 0, "abs");
//    one("finite", ieeeflag);
    one("floor");
    two("fmod");
    two("hypot", bsdflag);
    one("ilogb", ieeeflag);
    one("blitz_isnan", ieeeflag);
    one("itrunc", bsdflag);
    one("j0", ieeeflag);
    one("j1", ieeeflag);
    one("lgamma", ieeeflag);
    one("log");
    one("logb", ieeeflag);
    one("log1p", ieeeflag);
    one("log10");
    one("nearest", bsdflag);
    two("nextafter", bsdflag);
    two("pow");
    two("remainder", bsdflag);
    one("rint", ieeeflag);
    one("rsqrt", bsdflag);
    two("scalb", bsdflag);
    one("sin");
    one("sinh");
    one("sqr");
    one("sqrt");
    one("tan");
    one("tanh");
//    one("trunc", ieeeflag);
    one("uitrunc", bsdflag);
    two("unordered", bsdflag);
    one("y0", ieeeflag);
    one("y1", ieeeflag);

    ofs << endl << "BZ_NAMESPACE_END" << endl << endl
        << "#endif // BZ_MATUOPS_H" << endl;

    return 0;
}

