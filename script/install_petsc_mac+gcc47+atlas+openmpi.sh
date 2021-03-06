#!/bin/bash -x

PREFIX="$1"
test -z "$PREFIX" && PREFIX=$HOME/opt/rokko
echo "PREFIX = $PREFIX"

mkdir -p $HOME/build
cd $HOME/build
rm -rf petsc-3.3-p6
wget -O - http://ftp.mcs.anl.gov/pub/petsc/release-snapshots/petsc-3.3-p6.tar.gz | tar zxf -

cd petsc-3.3-p6
./configure --prefix="$PREFIX" --with-cc="openmpicc" --COPTFLAGS="-O3" --CXXOPTFLAGS="-O3" --FOPTFLAGS=-O3 --with-cxx="openmpicxx" --with-fc="openmpif77" --with-mpiexec="openmpiexec" --with-blas-lapack-lib="/opt/local/lib/liblapack.a -lptcblas -lptf77blas -latlas" --with-blacs-dir=$PREFIX --with-scalapack-dir=$PREFIX --with-c++-support=1 --with-debugging=0
make -j4
make install
