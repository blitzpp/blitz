/*
 * Example of reading an array from a file in text format.
 */

#include <fstream.h>
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    const char* inputFile = "input.data";
    ifstream ifs(inputFile);

    if (ifs.bad())
    {
        cerr << "Unable to open file: " << inputFile << endl;
        return 1;
    }

    int n, m;
    ifs >> n >> m;
    
    Array<int,2> A(n,m);
    Array<int,2>::iterator iter = A.begin(), end = A.end();

    while (iter != end) {
        if (ifs.eof())
        {
            cerr << "Premature end of file on " << inputFile << endl;
            return 2;
        }

        ifs >> (*iter);
        ++iter;
    }

    cout << "The array is: " << A << endl;

    return 0;
}

