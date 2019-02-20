// DESCRIPTION
//
//   Check for baseline language coverage in the compiler for the C++0x
//   standard.
//   In sync with AC_CXX_COMPILE_STDCXX_0X (2008-04-17).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Benjamin Kosnik <bkoz@redhat.com>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

template <typename T>
struct check {
    static_assert(sizeof(int) <= sizeof(T), "not big enough");
};

typedef check<check<bool>> right_angle_brackets;

int a;
decltype(a) b;

typedef check<int> check_type;
check_type c;
check_type&& cr = c;

int main() { }
