// -*- C++ -*-
/***************************************************************************
 * blitz/prettyprint.h      Format object for pretty-printing of
 *                          array expressions
 *
 * $Id$
 *
 * Copyright (C) 1997-2011 Todd Veldhuizen <tveldhui@acm.org>
 *
 * This file is a part of Blitz.
 *
 * Blitz is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Blitz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with Blitz.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Suggestions:          blitz-devel@lists.sourceforge.net
 * Bugs:                 blitz-support@lists.sourceforge.net    
 *
 * For more information, please see the Blitz++ Home Page:
 *    https://sourceforge.net/projects/blitz/
 *
 ***************************************************************************/

#ifndef BZ_PRETTYPRINT_H
#define BZ_PRETTYPRINT_H

#include <blitz/blitz.h>

namespace blitz {

class prettyPrintFormat {

public:
    prettyPrintFormat(const bool terse = false)
        : tersePrintingSelected_(terse) 
    {
        arrayOperandCounter_ = 0;
        scalarOperandCounter_ = 0;
        dumpArrayShapes_ = false;
    }

    void setDumpArrayShapesMode()  { dumpArrayShapes_ = true; }
    char nextArrayOperandSymbol()  
    { 
        return static_cast<char>('A' + ((arrayOperandCounter_++) % 26)); 
    }
    char nextScalarOperandSymbol() 
    { 
        return static_cast<char>('s' + ((scalarOperandCounter_++) % 26)); 
    }

    bool tersePrintingSelected() const { return tersePrintingSelected_; }
    bool dumpArrayShapesMode()   const { return dumpArrayShapes_; }

private:
    bool tersePrintingSelected_;
    bool dumpArrayShapes_;
    int arrayOperandCounter_;
    int scalarOperandCounter_;
};

}

#endif // BZ_PRETTYPRINT_H
