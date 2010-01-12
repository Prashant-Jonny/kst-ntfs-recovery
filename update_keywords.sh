#/bin/sh
cd src
SOURCE_KEYWORDS="Author Date  Rev HeadURL"
for i in *.{cpp,h} ; do
    echo svn propset svn:keywords ${SOURCE_KEYWORDS} $i
done
cd ..

