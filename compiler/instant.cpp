// Explicit template instantiation
// BZ_EXPLICIT_TEMPLATE_INSTANTIATION

template<class T>
class Vector {
public:
    Vector() { }
};

template class Vector<int>;

int main()
{
    return 0;
}

