Homework 1 — Optimize Matrix Multiplication
================
Due: February 23, 2019 @ 11:59pm

[GitHub classroom repository: click here to get your starter files](https://classroom.github.com/a/MlPbfw3T)

<table>

<tr>

<td>

The code in this repository is a C++11 refactoring of the code distributed on the Moodle site.
If you have only worked with C before, you will find that the most notable change is the lack of `malloc()` and `free()` functions; instead we use the C++11 STL object `std::vector<double>` to allocate and manage memory for the matrices.
`std::vector` implements a kind of “garbage collection” and frees its memory once it goes out of scope.

</td>

</tr>

</table>

## Problem statement

Your task in this assignment is to write an optimized [matrix multiplication](http://en.wikipedia.org/wiki/Matrix_multiplication) function for XSEDE’s [Bridges](https://portal.xsede.org/psc-bridges) supercomputer.
We will give you a generic matrix multiplication code (also called matmul or dgemm), and it will be your job to tune our code to run efficiently on Bridge’s processors.
We are asking you to write an optimized single-threaded matrix multiply kernel.
This will run on only one core.

We consider a special case of matmul:

    C := C + A * B

where `A`, `B`, and `C` are *n* ⨉ *n* matrices.
This can be performed using 2*n*<sup>3</sup> floating point operations (*n*<sup>3</sup> adds, *n*<sup>3</sup> multiplies), as in the following pseudocode:

    for i = 1 to n
      for j = 1 to n
        for k = 1 to n
          C(i,j) = C(i,j) + A(i,k) * B(k,j)
        end
      end
    end

Other things to keep in mind are:

  - The target processor on the Bridges compute nodes is a Xeon Intel 14-Core 64-bit E5-processor running at 2.3GHz and supporting 8 floating-point operations per clock period with a peak performance of 42.9 GFLOPS/core.

  - Besides compiler intrinsic functions and built-ins, your code (`dgemm-blocked.cpp`) must only call into the C/C++ standard library.

  - Your code must use [double-precision](http://en.wikipedia.org/wiki/Double-precision_floating-point_format) to represent real numbers.
    A common reference implementation for

  - Your code should be based on the 2*n*<sup>3</sup> algorithm.
    Submissions that implement algorithms outside this restriction, such as the [Strassen](http://en.wikipedia.org/wiki/Strassen_algorithm) algorithm, will not be graded.

  - You may not use compiler flags that automatically detect `dgemm` kernels and replace them with BLAS calls, i.e. Intel’s [`-matmul`](http://software.intel.com/sites/products/documentation/hpc/composerxe/en-us/2011Update/fortran/win/copts/common_options/option_opt_matmul.htm) flag.

  - The matrices are all stored in [column-major order](https://en.wikipedia.org/wiki/Row-_and_column-major_order), i.e. C<sub>i,j</sub> `== C(i,j) == C[(i - 1) + (j - 1) * n]`, for `i = 1:n`, where `n` is the number of rows in `C`.
    Note that we use 1-based indexing when using mathematical symbols C<sub>i,j</sub> and MATLAB index notation `C(i,j)`, and 0-based indexing when using C index notation `C[(i - 1) + (j - 1) * n]`.

  - We will check correctness by the following componentwise error bound,
    
        ｜square_dgemm(n, A, B, 0) - A * B｜ <  ε * n * ｜A｜ * ｜B｜
    
    where ε = 2<sup>-52</sup> = 2.2 ⨉ 10<sup>-16</sup> is the [machine epsilon](http://en.wikipedia.org/wiki/Machine_epsilon).

## Optimizing

Now, it’s time to optimize\!
A few optimizations you might consider adding:

1.  Perform blocking. The dgemm-blocked.cpp already gets you started with this, although you’ll need to tune block sizes.

2.  Write a register-blocked kernel, either by writing an inner-level fixed-size matrix multiply and hoping (and maybe checking) that the compiler inlines it, writing AVX intrinsics, or even writing inline assembly instructions.

3.  Add manual prefetching.

You may, of course, proceed however you wish.
We recommend you look through the lecture notes as reference material to guide your optimization process, as well as the references at the bottom of this write-up.

## Report

In addition to your code, you are to submit an accompanying report for the homework assignment.
The report is to be written in a style appropriate for an academic journal with any relevant citations provided in a bibliography.
The report should only discuss the details of the final version of your submitted code.
The report is to contain the following:

1.  An introduction to the problem

2.  A section detailing how you optimized the code.
    This requires both a conceptual discussion of what you implemented (figures are helpful\!), and a code summary, where you explain each important step in your solution (this should be supported with code snippets).

3.  A benchmark section where you show how your code performs relative to the naive and blas implementations.
    Figures are very helpful when reporting this data\!
    Benchmark data should be taken from runs performed on Bridges, not your local computer or laptop.
    Make sure you discuss the reason for any odd behavior (e.g., dips) in the reported performance.

Your report should be converted to the PDF format prior to submission.
The filename should follow this format: `FirstNameLastName_hw1.pdf`.

## How to submit

Put your report file `FirstNameLastName_hw1.pdf` into the `doc/` directory in your GitHub repository, and save, commit, and push the report and the final version of your code into the master branch.
Do not push the `benchmark` binary or any temporary files (such as `.o` files) to GitHub (the `.gitignore` file is meant to help prevent this).
After everything is pushed and up-to-date, do the following:

1.  Upload your report PDF to the Homework 1 assignment posted on Blackboard.

2.  Navigate to your repository on the GitHub website, click the green `Clone or download` button, and click **Download ZIP**.
    Rename the zipfile to `FirstNameLastName_hw1.zip` (replace `FirstNameLastName` with your first and last name) and upload it to the [Moodle](https://moodle.xsede.org) site.

## Logging in to Bridges

The easiest way to access the machines is to login directly with your own ssh client to **login.xsede.org** and from there **gsissh** into the correct machine.
You need to set up two-factor authentication with Duo in order to use the single sign-on hub.
More information on is available here on the [single login system](https://portal.xsede.org/web/xup/single-sign-on-hub).

An example of logging on to XSEDE would be to first connect to the single sign-on hub:

    ssh XSEDE-username@login.xsede.org

Enter your password and complete the 2-factor authentication request.
Then, run the following to hop over to Bridges:

    gsissh bridges

Another way to login to XSEDE resources is via the [Accounts tab](https://portal.xsede.org/group/xup/accounts) in XSEDE User Portal.
To reach this page login to XSEDE User Portal, navigate to MY XSEDE tab and from there select the Accounts page.
All machines you have access to will have a **login** option next to them that will launch OpenSSH via a Java Applet.

Please be aware that most XSEDE resources are not available via direct ssh and all requests must go through the XSEDE single login system.

To clone the files from your Github copy, use the following command:

    git clone git@github.com:mason-sp19-csi-702-003/homework-1-YOURUSERNAME.git

## Compiling the code

Instead of a regular Makefile, compilation is handled via CMake.
For your convenience, a simple script file named `make.sh` is included that will automatically compile your code on Bridges.
From the root directory of this repository, simply run:

    ./make.sh

Your code should compile, and the compiled binary will be placed into a folder called `bin/`.
Running this after you make a change to the code will recompile the changed file and update the binary.

If you are developing on your local computer using the virtual machine, you can compile the code by running:

    ./make.sh vm

If you aren’t using the virtual machine, then the wrapper script might not work and you’ll need to run CMake manually.
If you are unfamiliar with how to use CMake, you can open `make.sh` with your text editor to get an idea of how to use it.

## Submitting and running the code

The jobs queue on Bridges is managed via the [SLURM scheduler](https://slurm.schedmd.com/documentation.html).
To submit a job, use the `sbatch` command like so:

    sbatch job-blocked

To check the status of your running jobs you can use the following command:

    squeue -u $USER

Append a `-l` flag will print additional information about the running jobs.
If you want even more information, consider using the `sacct` command, for example:

    sacct -j $JOBID --format JobID,ReqMem,MaxRSS,TotalCPU,State

where `$JOBID` is the ID number of the job.

If you want to cancel a job, run:

    scancel $JOBID

If you would like to receive emails for job submissions add the following lines to the submission scripts.
This sometimes helps tracking down issues.

    #SBATCH --mail-type=ALL
    #SBATCH --mail-user=youremailaddress

For more details on SLURM commands please see [Bridges documentation page](https://portal.xsede.org/psc-bridges#jobs).

Finally, there is an interactive mode that allows you to request computing nodes, but maintain a command line.
This is ideal for prototyping and debugging purposes.
To activate this mode, type

    interact -N 1

The `interact.sh` script included in the repository provides you with a reminder on how to activate the interactive session.
For additional information, [read the documentation on interactive sessions](https://portal.xsede.org/psc-bridges#jobs:interactive).

## CLI interface

When testing the code on a local computer or within an interactive session on Bridges, you will use a simple command-line interface to select which benchmark you want to run.
There are three available benchmark modes: “naive”, “blocked”, and “blas”.
The “blocked” mode is the default.

To benchmark the “naive” mode, you would type:

    ./benchmark naive

To benchmark the “blas” mode, you would type:

    ./benchmark blas

The benchmark results will both print to stdout and be written to a CSV file named `benchmark_MODE.csv` by default (replace `MODE` with the benchmarking mode).
If you want to change the name of the output file, use the `-o` flag, for example:

    benchmark -o benchmark1.csv blocked

To read about other features you can set on the command line, such as changing the “max speed” variable (for example, if you want to benchmark on your own computer), run:

    ./benchmark --help

## File transfer

When copying files to and from Bridges, [you can use `scp` in conjunction with `data.bridges.psc.edu`](https://portal.xsede.org/psc-bridges#transfer:tfa) to avoid having to copy your files to Single Site Login node first.
**This will work with the Two-Factor Authentication setup.**
Try running the following to copy files directly to Bridges:

    scp -P 2222 myfile XSEDE-username@data.bridges.psc.edu:/path/to/file

To copy from Bridges:

    scp -P 2222 XSEDE-username@data.bridges.psc.edu:/path/to/file myfile

## Hints

  - Please carefully read this section for implementation details and hints.
    Stay tuned to [Moodle](https://moodle.xsede.org/mod/forum/view.php?id=35) for updates and clarifications, as well as discussion.
    If you are new to optimizing numerical codes, we recommend reading the papers in the [references](#references) section.

  - The GNU and Intel compilers can let you take advantage of Bridges’ Intel(R) Xeon(R) CPU E5-2695 v3 @ 2.30GHz processors’ [support for AVX2, AVX, SSE4.2, SSE4.1, SSSE3, SSE2, and SSE](https://software.intel.com/en-us/node/523351) intrinsic instructions.
    [Click here for a broad overview of what these various definitions mean](https://software.intel.com/en-us/articles/performance-tools-for-software-developers-intel-compiler-options-for-sse-generation-and-processor-specific-optimizations).

  - To get good performance, you will need to manually vectorize your code using compiler intrinsics.
    [Intel provides a convenient applet containing an interactive, searchable list of all of the available intrinsics functions.](https://software.intel.com/sites/landingpage/IntrinsicsGuide/)

  - One possible optimization to consider for the multiple tuning parameters in an optimized Matrix Multiplication code is autotuning in order to find the optimal/best available value.
    Libraries like [OSKI](http://bebop.cs.berkeley.edu/oski/) and [ATLAS](http://math-atlas.sourceforge.net/) have shown that achieving the best performance sometimes can be done most efficiently by automatic searching over the parameter space.
    Some papers on this topic can be found on the [**Be**rkeley **B**enchmarking and **Op**timization (BeBOP) page](http://bebop.cs.berkeley.edu/)

### Other notes

  - You may use [any compiler available](https://portal.xsede.org/psc-bridges#programming) on Bridges.
    We recommend starting with the GNU C++ compiler (g++), which is what the `make.sh` script uses automatically.
    If you use a compiler other than gcc, you will have to change `src/CMakeLists.txt`, which uses gcc-specific flags.
    You can type “module list” to see which compiler wrapper you have loaded.
    Note that you may have to switch compilers using the module system.

  - Double-precision matrix multiplication is the [`dgemm`](http://www.netlib.org/blas/dgemm.f) (**d**ouble-precision **ge**neral **m**atrix-**m**atrix multiply) routine in the level-3 [BLAS](http://netlib.org/blas/index.html).
    We will compare your implementation with the tuned `dgemm` implementation available on Bridges, where we will compare with the Intel MKL implementation of `dgemm`.
    Note that `dgemm` has a more general interface than `square_dgemm::blocked`.
    An [optional](#optional) part of HW1 encourages you to explore this richer tuning space.

  - Once you have finished and are happy with your `square_dgemm::blocked` implementation you should consider this and other [optional](#optional) improvements for further coding practice but they will not be graded for HW1.

  - You may make use of C++11 features, such as the STL, if you find it useful, provided they do not implement optimal BLAS routines.

## Grading

Your final code grade will be determined by comparing your code’s sustained performance relative to the Intel MKL implementation (i.e. the “blas” running mode).

A quicker estimate of your code grade is outputted at the conclusion of each benchmarking run.
It is computed by comparing your code’s sustained performance on Bridges as a percentage of the theoretical peak performance.
From that estimate, you will receive a score as follows:

  - If your sustained performance is between 0% and 25% you will receive a score between 0 and 65 proportional to your sustained performance (Ex: 20% gives a score of 52)

  - If your sustained performance is between 25% and 40% you will receive a score between 65 and 80 proportional to your sustained performance (Ex: 35% gives a score of 75)

  - If your sustained performance is between 40% and 70% you will receive a score between 80 and 100 proportional to your sustained performance (Ex: 60% gives a score of 93)

  - If your sustained performance is above 70% you will receive 100

**VERY IMPORTANT\!** Your submission must pass the error bound test and cannot call BLAS for dgemm; any submissions that fail these tests this will receive a grade of 0.
For this reason, do not change **anything** in the `benchmark.cpp` file, otherwise you might deactivate this check and not realize your code is not behaving properly.

## Optional

These parts are not graded.
You should be satisfied with your `square_dgemm::blocked` results before beginning an optional part.

  - Implement Strassen matmul.
    Consider switching over to the three-nested-loops algorithm when the recursive subproblems are small enough.

  - Support the `dgemm` interface (ie, rectangular matrices, transposing, scalar multiples).

  - Try `float` (single-precision).
    This means you can use 8-way SIMD parallelism on Bridges.

  - Try complex numbers (single- and double-precision).
    [This forum thread](http://stackoverflow.com/questions/3211346/complex-mul-and-div-using-sse-instructions) gives advice on vectorizing complex multiplication with the conventional approach, but note that there are [other algorithms](http://en.wikipedia.org/wiki/Multiplication_algorithm#Gauss.27s_complex_multiplication_algorithm) for this operation.

  - Optimize your matmul for the case when the inputs are symmetric.
    Consider [conventional](http://www.netlib.org/lapack/lug/node122.html) and [packed](http://www.netlib.org/lapack/lug/node123.html) symmetric storage.

  - Run the optimized code on one of the other supercomputers available and check relative performance and what optimizations need to change or become more relevant

## References

Here are some references that you can use to get started.
The PDFs are included in the `references/` folder for your convenience.

  - Goto, K., and van de Geijn, R. A. 2008. [Anatomy of High-Performance Matrix Multiplication](/references/Goto_2008_Anatomy_of_High-performance_Matrix_Multiplication.pdf), *ACM Transactions on Mathematical Software 34*, 3, Article 12.
    
    **Note:** explains the design decisions for the GotoBLAS `dgemm` implementation, which also apply to your code.

  - Chellappa, S., Franchetti, F., and Püschel, M. 2008. [How To Write Fast Numerical Code: A Small Introduction](/references/Chellappa_2008_How_to_Write_Fast_Numerical_Code.pdf), *Lecture Notes in Computer Science 5235*, 196-259.
    
    **Note:** how to write C code for modern compilers and memory hierarchies, so that it runs fast.
    Recommended reading, especially for newcomers to code optimization.

  - Bilmes, *et. al.* [The PHiPAC (Portable High Performance ANSI C) Page for BLAS3 Compatible Fast Matrix Matrix Multiply](/references/Bilmes_1998_The_PHiPAC_v1.0_Matrix-Multiply_Distribution.pdf).
    
    **Note:** PHiPAC is a code-generating autotuner for matmul that started as a submission for this HW in a previous semester of CS267.
    Also see [ATLAS](http://math-atlas.sourceforge.net/); both are good examples if you are considering code generation strategies.

  - Lam, M. S., Rothberg, E. E, and Wolf, M. E. 1991. [The Cache Performance and Optimization of Blocked Algorithms](/references/Lam_1991_The_Cache_Performance_and_Optimizations_of_Blocked_Algorithms.pdf), *ASPLOS’91*, 63-74.
    
    **Note:** clearly explains cache blocking, supported by with performance models.

  - [Notes](/references/homework1notes_bvs.pdf) on vectorizing with SSE intrinsics and a short [video](https://www.cac.cornell.edu/vw/apc6/NotesOnHomework1.mp4) by Brian Van Straalen.
    **Please ignore the due date on the last slide**

## Documentation:

  - [Bridges computing environment](https://portal.xsede.org/psc-bridges) documentation

  - [Intel Xeon Processor E5-2695 v3, 2.3GHz, 35M Cache](https://ark.intel.com/products/81057/Intel-Xeon-Processor-E5-2695-v3-35M-Cache-2_30-GHz) documentation.

You are also welcome to learn from the source code of state-of-art BLAS implementations such as [GotoBLAS](http://www.tacc.utexas.edu/tacc-projects/gotoblas2).
However, you should not reuse those codes in your submission.
