// Templates as template arguments
// BZ_TEMPLATES_AS_TEMPLATE_ARGUMENTS

template<class T>
class allocator {
public:
    allocator() { };
};

template<class X, template<class Y> class T_alloc>
class foo {
public:
   foo() { }
 
private:
   T_alloc<X> alloc_; 
};

int main()
{
    foo<double, allocator> x;
    return 0;
}

