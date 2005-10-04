If you are interested in using Blitz with Microsoft's VS .NET 2003 C++
compiler, we have provided a Zip archive containing a Blitz configuration 
header file and project files for building the Blitz library and the 
Blitz testsuite codes.  First unpack the archive Blitz-VS.NET.zip into
the top-level blitz directory containing the archive file (i.e., unpack
it in place).  This will produce a Blitz-Library VS.NET solution file and
a sibling directory Blitz-Testsuite that contains the VS.NET project files 
for building the blitz testsuite codes.  Within the "blitz" subdirectory, 
you will also find a "ms" directory containing a Blitz configuration header 
file bzconfig.h that has been manually produced for the Microsoft VS.NET 2003 
C++ compiler.  Once these files have been unpacked, you should be able to 
open the Blitz-Library solution file using VS.NET 2003 and build the blitz 
library and testsuite codes.  The project files for the blitz testsuite codes 
should provide you with an example of how to create project files for your 
own application codes that use the blitz library.  In addition to the project
files for the blitz testsuite codes, we now also provide a Blitz-Examples 
VS.NET solution file and a directory Blitz-Examples with project files for 
building some of the Blitz sample applications in the examples subdirectory.
This additional solution file was kindly contributed by David L. Goldsmith
(David.L.Goldsmith@noaa.gov).  Please send any questions or comments to the 
blitz mailing list at blitz-support@lists.sourceforge.net.


Julian C. Cummings
10-03-05
