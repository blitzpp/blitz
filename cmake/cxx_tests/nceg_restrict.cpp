// DESCRIPTION
//
//   Test to check whether the C++ compiler supports the Numerical C Extensions Group restrict
//   keyword.
//
//   In sync with AC_CXX_NCEG_RESTRICT (2008-04-12).
//   !! Replaced by AC_C_RESTRICT in Autoconf 2.58.
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

void add(int length,double* restrict a,const double* restrict b,const double* restrict c) {
    for (int i=0;i<length;++i)
        a[i] = b[i]+c[i];
}

int main() {
    double a[10],b[10],c[10];
    for (int i=0;i<10;++i) {
        a[i] = 0.0;
        b[i] = 0.0;
        c[i] = 0.0;
    }
    add(10,a,b,c);
    return 0;
}
