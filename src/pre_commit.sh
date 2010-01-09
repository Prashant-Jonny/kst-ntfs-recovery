#/bin/bash
# $Header$
#
INDENT_PARAMS="-nbad -bap  -cdb -sc -br -ce -cs -bs -di20 -bc -bls \
-lp -ip5 -l75 -bbo -bl -bli2 -ncdb -nce -cp1  \
-nfc1 -nfca -hnl   -pcs -nprs -saf -sai \
-saw -nsc -nsob -i2 -nbfde -nbfda -sob -ut -npsl -nlps  "


for i  in ./*.cpp; do indent ${INDENT_PARAMS} $i ; done
for i  in ./*.h; do indent ${INDENT_PARAMS} $i ; done
rm ./*~
svn propset svn:keywords Header *.cpp
svn propset svn:keywords Header *.h
svn propset svn:keywords Header $0
svn propset svn:executtable true $0
