<a href="http://dl.dropbox.com/u/2294525/scss.pdf">rough class heirarchy</a>

Results currently generated for T = 0 (pure MFT superconducting state) and T = Tp (pseudrogap state, pair formation temperature scale)

Developed on Ubuntu 10.10 / Mint 10.  Required packages:
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

C++ basic execution path:
    - build Controller from config file; this triggers buiding instances of 
        ConfigData, Environment, Logger, and State.
    - call selfConsistentCalc() on Controller, if it returns true it worked
    - logResults() and examine output

Spectrum is a big ball of static functions which take a State and some 
additional data, do some math, and emit results.

Tests for individual classes are built to test_(Class).out by make.
