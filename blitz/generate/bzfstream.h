#include <fstream.h>
#include <iomanip.h>
#include <iostream.h>

class bzofstream : public ofstream {

public:
    bzofstream(const char* filename, const char* description,
        const char* sourceFile, const char* mnemonic)
        : ofstream(filename)
    {
        (*this) << 
"/***************************************************************************\n"
" * blitz/" << filename << "\t" << description << endl <<
" *\n"
" * $Id$\n"
" *\n"
" * This program is free software; you can redistribute it and/or\n"
" * modify it under the terms of the GNU General Public License\n"
" * as published by the Free Software Foundation; either version 2\n"
" * of the License, or (at your option) any later version.\n"
" *\n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" *\n"
" * Suggestions:          blitz-suggest@cybervision.com\n"
" * Bugs:                 blitz-bugs@cybervision.com\n"
" *\n"
" * For more information, please see the Blitz++ Home Page:\n"
" *    http://seurat.uwaterloo.ca/blitz/\n"
" *\n"
" ***************************************************************************\n"
" * $Log$
" * Revision 1.1  2000/06/19 13:02:47  tveldhui
" * Initial source check-in; added files not usually released in the
" * distribution.
" *\n"
" */ " 
       << endl << endl
       << "// Generated source file.  Do not edit. " << endl
       << "// " << sourceFile << " " << __DATE__ << " " << __TIME__ 
       << endl << endl
       << "#ifndef " << mnemonic << endl
       << "#define " << mnemonic << endl << endl;
    }

    void include(const char* filename)
    {
        (*this) << "#include <blitz/" << filename << ">" << endl;
    }

    void beginNamespace()
    {
        (*this) << "BZ_NAMESPACE(blitz)" << endl << endl;
    }

    ~bzofstream()
    {
        (*this) << "BZ_NAMESPACE_END" << endl << endl
                << "#endif" << endl;
    }

};

