#include <blitz/array.h>
#include <iostream.h>
#include <complex.h>

BZ_USING_NAMESPACE(blitz)


BZ_DECLARE_STENCIL2(footprint,A,B)
    B = stenciltoapply;
BZ_END_STENCIL


template<class T_stencil>
void dumpStencil(const T_stencil& stencil)
{
    const int maxN = 5;

    Array<double,2> A(Range(-maxN,maxN),Range(-maxN,maxN)),
     B(Range(-maxN,maxN), Range(-maxN, maxN));

    A = 0.0;
    A(0,0) = 1;

    B = 0.0;

    applyStencil(stencil, A, B);

    B.reverseSelf(firstDim);
    B.reverseSelf(secondDim);

    using namespace blitz::tensor;

    int minrow = first(sum(B != 0.0, j));
    int maxrow = last(sum(B != 0.0, j));
    int mincol = first(sum(B(j,i) != 0.0, j));
    int maxcol = last(sum(B(j,i) != 0.0, j));

    // Code to dump HTML
    cout << "htmlcommand(" << endl;
    cout << "<table cellpadding=2 rules=all>" << endl
         << "<tr align=right><td></td>";

    for (int j=mincol; j <= maxcol; ++j)
        cout << "<td>" << j << "</td>";

    cout << "</tr>";

    for (int i=minrow; i <= maxrow; ++i)
    {
        cout << "<tr align=right>";

        if (minrow != maxrow)
            cout << "<td>" << i << "</td>";
        else
            cout << "<td></td>";

        for (int j=mincol; j <= maxcol; ++j)
        {
            if (B(i,j) != 0.0)
            {
                if ((i == 0) && (j == 0))
                    cout << "<td bgcolor=\"#000060\">";
                else
                    cout << "<td bgcolor=\"#000000\">";
                cout << "<font color=\"#ffffff\">" << B(i,j) << "</font></td>";
            }
            else
                cout << "<td></td>";
        }

        cout << "</tr>" << endl;
    }
    cout << "</table>";
    cout << ")" << endl;


    // Code to dump LaTeX
    cout << "latexcommand(" << endl;
    cout << "\\begin{tabular}{r|";
    for (int j=mincol; j <= maxcol; ++j)
        cout << "r";
    cout << "}" << endl;
    cout << " & ";
    for (int j=mincol; j < maxcol; ++j)
        cout << j << " & " ;
    cout << maxcol << " \\\\ \\hline" << endl;
    for (int i=minrow; i <= maxrow; ++i)
    {
        if (minrow != maxrow)
            cout << i << " & ";
        else
            cout << " & ";
        for (int j=mincol; j <= maxcol; ++j)
        {
            if (B(i,j) != 0.0)
            {
                if ((i == 0) && (j == 0))
                    cout << "{\\bf " << B(i,j) << "} ";
                else
                    cout << " " << B(i,j) << " ";
            }
            if (j != maxcol)
                cout << " & ";
        }
        if (i != maxrow)
            cout << " \\\\  " << endl;
    }
    cout << endl << "\\end{tabular}" << endl;
    cout << ")" << endl;
}

int main()
{
    dumpStencil(footprint());
}

