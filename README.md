# Reproducible BLAS v2.1.0

## Installation:

  0. Download the latest version of source code from `bebop.cs.berkeley.edu/reproblas/download.html`
  1. Un-compress the downloaded zip or tar file to `$(ReproBLAS_ROOT)` folder
  2. Change directory to `$(ReproBLAS_ROOT)`
  3. Check that all of the settings in config.mk are correct. Most importantly, check that the install locations are correct. If you want to use MPI, be sure to set the `BUILD_MPI` flag and to supply the proper MPI compiling and linking flags.
  4. Python is recommended for installation. If python is installed, ReproBLAS will use code generation during installation. If python is not installed, ReproBLAS will use pre-generated files and you can skip to step 6.
  5. If python is installed: from `$(ReproBLAS_ROOT)`, type `make update`. This will make all of the configuration settings available to the python generators.
  6. From `$(ReproBLAS_ROOT)`, type `make`.
  7. From `$(ReproBLAS_ROOT)`, type `make install`.
  8. To verify installation, try compiling the examples. From `$(ReproBLAS_ROOT)/examples`, type `make`. Then, run the example with `./sum_sine`

## Documentation:

  0. Read the examples in `$(ReproBLAS_ROOT)/examples`
  1. Browse the installed documentation at the location specified by the `DOC_DIR` variable in `config.mk`. Your can browse it in website form or as a pdf. To view the documentation online, visit `http://bebop.cs.berkeley.edu/reproblas/documentation.php`
  2. Consult the header files in `$(ReproBLAS_ROOT)/include`

## Usage:

  ReproBLAS libraries depend on each other. What follows is a graph where a forward edge represents inclusion:

    ```
    libreproBLAS.a
         |
         v
    libbinnedBLAS.a  libbinnedMPI.a
         |              |
         +-----+  +-----+
               |  |
               v  v
             libbinned.a
    ```

  All ReproBLAS libraries require you to link to libm.a. Therefore, your link string should include some subset of:

    ```
    -lbinned -lbinnedBLAS -lreproBLAS -lbinnedMPI
    ```

  Followed by:

    ```
    -lm
    ```

## Advanced Usage:
  ReproBLAS uses a custom build system. It is based off of the nonrec-make project. The build system encodes information not in the Makefile, but in a separate file in each directory called Rules.mk. The default make target builds all files in the subtree rooted at the current directory. If you want to build all files, type `make all`. If you want to make just the files in the current directory, type `make dir`. There are corresponding targets `clean_tree`, `clean_all`, `clean_dir`. Check `$(ReproBLAS_ROOT)/config.mk` for many more options. The make system lives in `$(ReproBLAS_ROOT)/mk`. The built files go in `$(ReproBLAS_ROOT)/build`.

  If you have python, you can run the tests. To run the benchmarks, type `make bench`. To run the checks, type `make check`. To run the accuracy test, type `make acc`. By following the example of `$(ReproBLAS_ROOT)/tests/checks/check.py`, `$(ReproBLAS_ROOT)/tests/benchs/bench.py`, and `$(ReproBLAS_ROOT)/tests/accs/acc.py`, the user can build their own tests composed of subsets of the available tests in `$(ReproBLAS_ROOT)/tests/checks/checks.py`, `$(ReproBLAS_ROOT)/tests/benchs/benchs.py`, and `$(ReproBLAS_ROOT)/tests/accs/accs.py`.

  Several configuration options are available in `$(ReproBLAS_ROOT)/config.py`, `$(ReproBLAS_ROOT)/config.mk`, and `$(ReproBLAS_ROOT)/config.h`.

## Frequently Asked Questions:
  0. What is the "fold?"

      The goal of using binned types is to obtain either more accurate or reproducible summation of floating point numbers. In reproducible summation, floating point numbers are split into several slices along predefined boundaries in the exponent range. The space between two boundaries is called a bin. Binned types are composed of several accumulators, each accumulating the slices in a particular bin. The accumulators correspond to the largest consecutive nonzero bins seen so far.

      The parameter fold describes how many accumulators are used in the binned types supplied to a subroutine (an binned type with `k` accumulators is `k`-fold). The default value for this parameter can be set in `config.h`. If you are unsure of what value to use for fold, we recommend 3. Note that the fold of binned types must be the same for all binned types that interact with each other. Operations on more than one binned type assume all binned types being operated upon have the same fold. Note that the fold of an binned type may not be changed once the type has been allocated. A common use case would be to set the value of fold as a global macro in your code and supply it to all binned functions that you use.

  1. What is the error bound of binned summation?

      The error bound of the returned binned sum can be queried for a specific sum and value for fold using the `binned_dbbound` or `binned_sbbound` functions in `binned.h`. The difference between the true sum `T` of `N` floating point numbers `x_0, ..., x_N-1` and the calculated sum `S` is approximately bounded by:

      ```
      |T - S| < N*2^(W(1 - fold))*max|x_j| + 7E|T|
      ```

      where `W = DBWIDTH = 40` and `E = 2^-53` in double precision and `W = SBWIDTH = 40` and `E = 2^-24` in single precision. For `fold >= 3`, reproducible summation is much more accurate than normal (recursive) summation.

  2. How do I sum numbers reproducibly using ReproBLAS?

      Check the examples for several different ways to sum numbers. Some of them are more modular than others (what if the numbers aren't in an array?). The fastest way to sum an array of numbers would be to use one of the following four methods in reproBLAS.h: `reproBLAS_dsum`, `reproBLAS_ssum`, `reproBLAS_zsum`, or`reproBLAS_csum`.
