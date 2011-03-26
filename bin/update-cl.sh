#!/bin/sh

# Script to update ChangeLog file using the utility
# command cvs2cl if found on the current system

which cvs2cl &> /dev/null || exit 1

userfile=`mktemp`

echo creating temporary usermap $userfile

cat >> $userfile << EOF
patrick:'Patrick Guio <p.guio@ucl.ac.uk>'
patricg:'Patrick Guio <p.guio@ucl.ac.uk>'
patrickg:'Patrick Guio <patrick.guio@matnat.uio.no>'
pguio:'Patrick Guio <patrick.guio@matnat.uio.no>'
julianc:'Julian Cummings  <cummings@cacr.caltech.edu>'
papadop:'Theodore Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>'
grifgrif:'Patrik Jonsson <code@familjenjonsson.org>'
EOF


cvs2cl --prune --no-times --no-common-dir --utc \
	-f ChangeLog -U $userfile -l "-d>2009-12-31"

echo removing temporary usermap $userfile
rm -rf $userfile
