#!/bin/bash -x

PREFIX="$1"
test -z "$PREFIX" && PREFIX=$HOME/opt/rokko
echo "PREFIX = $PREFIX"

mkdir -p $HOME/build
cd $HOME/build
rm -rf scalapack-2.0.2
if test -f $HOME/source/scalapack-2.0.2.tgz; then
  tar zxf $HOME/source/scalapack-2.0.2.tgz
else
  wget -O - http://www.netlib.org/scalapack/scalapack-2.0.2 | tar zxf -
fi

rm -rf scalapack-2.0.2-build && mkdir -p scalapack-2.0.2-build && cd scalapack-2.0.2-build
cmake -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_C_COMPILER=openmpicc -DCMAKE_Fortran_COMPILER=openmpif90 -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DCMAKE_INSTALL_NAME_DIR=$PREFIX/lib $HOME/build/scalapack-2.0.2

make -j4
make install