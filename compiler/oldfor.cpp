// Old 'for' scoping rules

int main()
{
    long z = 0;

    for (int i=0; i < 10; ++i)
    {
        z = z + i;
    }

    z = i;

    return 0;
}

