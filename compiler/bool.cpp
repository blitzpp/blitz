// bool treated as distinct type
// BZ_BOOL

int foo(int x)
{
    return 1;
}

int foo(char x)
{
    return 1;
}

int foo(bool x)
{
    return 0;
}

int main()    
{
    bool c = true;
    return foo(c);
}

