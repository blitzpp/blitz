#include <iostream.h>
#include <fstream.h>

class operand {
public:
    operand(const char* name, const char* templateName1, 
        const char* templateName2, const char* iterator, const char* numtype, 
        const char* initialization)
      : name_(name), template1_(templateName1), template2_(templateName2),
        iterator_(iterator), numtype_(numtype), initialization_(initialization)
    { }

    int haveTemplate1() const
    { return template1_ != 0; }

    int haveTemplate2() const
    { return template2_ != 0; }

    void setOperandNum(int i) 
    { operandNum_ = i; }

    virtual void printName(ostream& os)
    { 
        os << name_;           
        printTemplates(os);
    }

    virtual void printTemplates(ostream& os)
    {
        if (haveTemplate1())
        {
            os << "<" << template1_ << operandNum_;
            if (haveTemplate2())
            {
                os << ", " << template2_ << operandNum_;
            }
            os << ">";
        }
    }

    virtual void printTemplate1(ostream& os)
    {
        if (haveTemplate1())
            os << template1_ << operandNum_;
    }

    virtual void printTemplate2(ostream& os)
    {
        if (haveTemplate2())
            os << template2_ << operandNum_;
    }

    virtual int isScalar() const
    { return 0; }

    virtual int isInteger() const
    { return 0; }

    virtual void printArgument(ostream& os)
    {
        printName(os);
        os << " d" << operandNum_;      
    }

    virtual void printIterator(ostream& os)
    {
        os << iterator_;
        printTemplates(os);
    }

    virtual void printNumtype(ostream& os)
    {
        os << numtype_ << operandNum_;
    }

    virtual void printInitialization(ostream& os)
    {
        os << "d" << operandNum_;       
        if (initialization_ != 0)
            os << initialization_;
    }

protected:
    const char* name_;
    const char* template1_;
    const char* template2_;
    const char* iterator_;
    const char* numtype_;
    const char* initialization_;
    int operandNum_;
};

class MatOperand : public operand {
public:
    MatOperand()
      : operand("Matrix", "P_numtype", "P_struct", "_bz_MatrixRef",
           "P_numtype", "._bz_getRef()")
    { }

    virtual void printArgument(ostream& os)
    {
        os << "const ";
        printName(os);
        os << "& d" << operandNum_;
    }

};

class MatExprOperand : public operand {
public:
    MatExprOperand()
      : operand("_bz_MatExpr", "P_expr", 0, "_bz_MatExpr",
           0, 0)
    { }

    virtual void printNumtype(ostream& os)
    {
        os << "_bz_typename P_expr" << operandNum_ << "::T_numtype";
    }
};

class ScalarOperand : public operand {
public:
    ScalarOperand(const char* name)
      : operand(name, 0, 0, 0, name, 0)
    { }

    virtual void printIterator(ostream& os)
    {
        os << "_bz_MatExprConstant<" << name_ << ">";
    }

    virtual void printInitialization(ostream& os)
    {
        os << "_bz_MatExprConstant<" << name_ << ">(d"
           << operandNum_ << ")";
    }

    virtual void printNumtype(ostream& os)
    {
        os << name_;
    }

    virtual int isScalar() const
    { return 1; }

    virtual int isInteger() const
    { return !strcmp(name_, "int"); }

};

int main()
{
    cout << "Generating <matbops.h>" << endl;

    MatOperand aop1;
    MatExprOperand aop2;
    ScalarOperand aop3("int");
    ScalarOperand aop4("float");
    ScalarOperand aop5("double");
    ScalarOperand aop6("long double");
    ScalarOperand aop7("complex<float> ");
    ScalarOperand aop8("complex<double> ");
    ScalarOperand aop9("complex<long double> ");
    const int numOperands = 9;
    operand* aoperands[numOperands];
    aoperands[0] = &aop1;
    aoperands[1] = &aop2;
    aoperands[2] = &aop3;
    aoperands[3] = &aop4;
    aoperands[4] = &aop5;
    aoperands[5] = &aop6;
    aoperands[6] = &aop7;
    aoperands[7] = &aop8;
    aoperands[8] = &aop9;

    MatOperand bop1;
    MatExprOperand bop2;
    ScalarOperand bop3("int");
    ScalarOperand bop4("float");
    ScalarOperand bop5("double");
    ScalarOperand bop6("long double");
    ScalarOperand bop7("complex<float> ");
    ScalarOperand bop8("complex<double> ");
    ScalarOperand bop9("complex<long double> ");
    operand* boperands[numOperands];
    boperands[0] = &bop1;
    boperands[1] = &bop2;
    boperands[2] = &bop3;
    boperands[3] = &bop4;
    boperands[4] = &bop5;
    boperands[5] = &bop6;
    boperands[6] = &bop7;
    boperands[7] = &bop8;
    boperands[8] = &bop9;

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

    for (int j=0; j < numOperands; ++j)
    {
    for (int k=0; k < numOperands; ++k)
    {
        if (aoperands[j]->isScalar() && boperands[k]->isScalar())
            continue;

        if (ops[i].nonIntOperands == false)
        {
            if ((aoperands[j]->isScalar() && !aoperands[j]->isInteger())
             || (boperands[k]->isScalar() && !boperands[k]->isInteger()))
                continue;
        }

        ofs << endl;

        if ((j >= 6) || (k >= 6))
            ofs << "#ifdef BZ_HAVE_COMPLEX" << endl;

        // Matrix<P_numtype1, P_struct1> + _bz_MatExpr<P_expr2>

        aoperands[j]->setOperandNum(1);
        boperands[k]->setOperandNum(2);
        ofs << "// ";
        aoperands[j]->printName(ofs);
        ofs << " " << ops[i].opSymbol << " ";
        boperands[k]->printName(ofs);
        ofs << endl;

        // template<class T_numtype1, class T_expr2>
        int doneParm = 0;

        ofs << "template<";

        if (aoperands[j]->haveTemplate1())
        {
            ofs << "class ";
            aoperands[j]->printTemplate1(ofs);
            doneParm = 1;
        }

        if (aoperands[j]->haveTemplate2())
        {
            if (doneParm)
                ofs << ", ";
            ofs << "class ";
            aoperands[j]->printTemplate2(ofs);
            doneParm = 1;
        }

        if (boperands[k]->haveTemplate1())
        {
            if (doneParm)
                ofs << ", ";
            ofs << "class ";
            boperands[k]->printTemplate1(ofs);
            doneParm = 1;
        }

        if (boperands[k]->haveTemplate2())
        {
            if (doneParm)
                ofs << ", ";
            ofs << "class ";
            boperands[k]->printTemplate2(ofs);
            doneParm = 1;
        }

        ofs << ">" << endl;

        ofs << "inline" << endl;

        // _bz_MatrixExpr<_bz_MatExprOp<MatrixRef<T_numtype1, T_struct1>,
        //     _bz_MatrixExpr<T_expr2>, _bz_Add<T_numtype1, _bz_typename T_expr2::T_numtype> > >
        ofs << "_bz_MatExpr<_bz_MatExprOp<";
        aoperands[j]->printIterator(ofs);
        ofs << "," << endl << "    ";
        boperands[k]->printIterator(ofs);
        ofs << ", " << ops[i].opApplicName << "<";
        aoperands[j]->printNumtype(ofs);
        ofs << ", ";    
        boperands[k]->printNumtype(ofs);
        ofs << "> > >" << endl;
     
        // operator+(const Matrix<P_numtype1, P_struct1>& d1, 
        //     _bz_MatExpr<T_expr2> d2)
        ofs << "operator" << ops[i].opSymbol << "(";
        aoperands[j]->printArgument(ofs);
        ofs << ", ";
        boperands[k]->printArgument(ofs);
        ofs << ")" << endl << "{" << endl;

        // typedef _bz_MatExprOp<VectorIterConst<T_numtype1>,
        // _bz_MatExpr<T_expr2>, _bz_Add<T_numtype1, _bz_typename T_expr2::T_numtype> > T_expr;
        ofs << "    typedef _bz_MatExprOp<";
        aoperands[j]->printIterator(ofs);
        ofs << "," << endl << "      ";
        boperands[k]->printIterator(ofs);
        ofs << ", " << endl << "      " << ops[i].opApplicName << "<";
        aoperands[j]->printNumtype(ofs);
        ofs << ", ";
        boperands[k]->printNumtype(ofs);
        ofs << "> > T_expr;" << endl << endl;

        ofs << "    return _bz_MatExpr<T_expr>(T_expr(";
        aoperands[j]->printInitialization(ofs);
        ofs << ", " << endl << "        ";
        boperands[k]->printInitialization(ofs);
        ofs << "));" << endl << "}" << endl;


        if ((j >= 6) || (k >= 6))
            ofs << "#endif // BZ_HAVE_COMPLEX" << endl;

    }
    }
    
    }

    ofs << endl << "BZ_NAMESPACE_END" << endl << endl
        << "#endif // BZ_MATBOPS_H" << endl;
}

