// const_cast<T>


int main()
{
    int x = 0;
    const int& y = x;

    int& z = const_cast<int&>(y);
    z = 3;
    if (x == 3)
        return 0;

    return 1;
}

