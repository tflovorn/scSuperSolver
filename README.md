<a href="http://dl.dropbox.com/u/2294525/scss.pdf">rough class heirarchy</a>

Current implementation follows zero-temperature mean field theory results.

Plan on incorporating results at T = Tc (strong hole binding)
    and T = Tp (weak hole binding) also.

Top-level usage:
    - build Controller from config file; this triggers buiding instances of 
        ConfigData, Environment, Logger, and State.
    - call selfConsistentCalc() on Controller, if it returns true it worked
    - logResults() and examine output

Spectrum is a big ball of static functions which take a State and some 
additional data, do some math, and emit results.

Tests for individual classes are built to test_(Class).out by make.

Built on Ubuntu 10.10.  Required packages:
build-essential
libgsl0ldbl
libgsl0-dev
gsl-bin
libblas-dev
libboost-dev
python-matplotlib

For building on Fedora 14 need the following:
make
gcc
gcc-g++
gsl
gsl-devel
blas
blas-devel
(--boost?--)
(--matplotlib?--)