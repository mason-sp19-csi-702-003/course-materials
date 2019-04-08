CSI 702 course materials
<img src="img/course-logo-semester-square-section-003.svg" align="right" height=150>
================
Spring 2019 semester

  - [Syllabus](#syllabus)
  - [Schedule](#schedule)
  - [Homeworks](#homeworks)
  - [Final project](#final-project)
  - [Resources and links](#resources-and-links)
      - [Links](#links)
      - [Guides](#guides)
      - [Software](#software)
  - [License](#license)

## Syllabus

The syllabus is available as a Google Doc: <https://docs.google.com/document/d/14qsCAP9Dei89EobiOC-nGDpM-ER4hlDY9fGw-Ylau3k>

## Schedule

| Week | Date Range      | Lecture | Video Topic                                                                                                                                    |
| ---: | :-------------- | ------: | :--------------------------------------------------------------------------------------------------------------------------------------------- |
|    1 | Jan-28 – Feb-1  |       1 | [Introduction](https://youtu.be/o7DQd8FkA6M)                                                                                                   |
|      |                 |       2 | [Single Processor Machines](https://youtu.be/UeVNYwtLJ_s)                                                                                      |
|    2 | Feb-4 – Feb-8   |       3 | [Optimizing Matrix Multiply (cont), Introduction to Data Parallelism](https://youtu.be/-RegO-8WF88)                                            |
|      |                 |       4 | [Shared-Memory Programming](https://youtu.be/PR-98tVHFVg)                                                                                      |
|    3 | Feb-11 – Feb-15 |       5 | [Roofline and Performance Modeling](https://youtu.be/hX8KjB3fJ3M)                                                                              |
|      |                 |       6 | Sources of Parallelism and Locality in Simulation (Part 1)<br>[Video 1](https://youtu.be/p51sY0QcXvM), [Video 2](https://youtu.be/EAIHzh0SjaE) |
|    4 | Feb-18 – Feb-22 |       7 | [Sources of Parallelism and Locality in Simulation (Part 2)](https://youtu.be/5Ol5cNZ9dKM)                                                     |
|      |                 |       8 | [An Introduction to GPGPU Programming](https://youtu.be/2R5R0nXm3xc)                                                                           |
|    5 | Feb-25 – Mar-1  |       9 | [Distributed Memory Machines and Programming](https://youtu.be/mKsjQGMllac)                                                                    |
|      |                 |      10 | [Advanced MPI and Collective Communication Algorithms](https://youtu.be/Wy33f9J2CWo)                                                           |
|    6 | Mar-4 – Mar-8   |      11 | [UPC and UPC++](https://youtu.be/Urem3J7Mzkc)                                                                                                  |
|      |                 |      12 | [Cloud Computing and Big Data Processing](https://youtu.be/1IFVS3vS96g)                                                                        |
|    7 | Mar-18 – Mar-22 |      13 | [Dense Linear Algebra (Part 1)](https://youtu.be/vt4085N6Qy8)                                                                                  |
|      |                 |      14 | [Dense Linear Algebra (Part 2)](https://youtu.be/W4sKkol45e0)                                                                                  |
|    8 | Mar-25 – Mar-29 |      15 | [Graph Partitioning](https://youtu.be/r4lmLPvU-9s)                                                                                             |
|      |                 |      16 | [Automatic Performance Tuning and Sparse-Matrix-Vector-Multiplication (Part 1)](https://youtu.be/3iMGuSyM-_U)                                  |
|    9 | Apr-1 – Apr-5   |      17 | [Automatic Performance Tuning and Sparse-Matrix-Vector-Multiplication (Part 2)](https://youtu.be/9_yS2ovXTZc)                                  |
|      |                 |      18 | [Structured Grids](https://youtu.be/m6HJqolCfTQ)                                                                                               |
|   10 | Apr-8 – Apr-12  |      19 | [Parallel Graph Algorithms](https://youtu.be/i7DIr5ZgydY)                                                                                      |
|      |                 |      20 | [Fast Fourier Transform](https://youtu.be/iYSaWRLrGQA)                                                                                         |
|   11 | Apr-15 – Apr-19 |      21 | [Sorting and Searching](https://youtu.be/U8Gx63SHa5A)                                                                                          |
|      |                 |      22 | [Dynamic Load Balancing](https://youtu.be/rwy95KHOoqQ)                                                                                         |
|   12 | Apr-22 – Apr-26 |      23 | [Hierarchical Methods for the N-Body Problem (Part 1)](https://youtu.be/QKK28AxwJLE)                                                           |
|      |                 |      24 | [Hierarchical Methods for the N-Body Problem (Part 2) and Communication-Optimal Algorithms and Lower Bounds](https://youtu.be/UC9H7KP7ntw)     |

## Homeworks

| \# | Description                                                                             | Due date         |
| -: | :-------------------------------------------------------------------------------------- | :--------------- |
|  0 | [Describing a Parallel Application](homework/homework0.md)                              | Feb-1 @ 11:59pm  |
|  1 | [Optimize Matrix Multiplication](homework/homework1.md)                                 | Feb-23 @ 11:59pm |
|  2 | [Parallelizing a particle simulation (Part A)](homework/homework2a.md)                  | Mar-9 @ 11:59pm  |
|  3 | [Parallelizing a particle simulation (Part B)](https://classroom.github.com/g/gEjswJXz) | Apr-6 @ 11:59pm  |
|  4 | [Parallelizing a particle simulation (Part C)](homework/homework2c.md)                  | Apr-28 @ 11:59pm |

## Final project

| Description                                                                                               | Due date        |
| :-------------------------------------------------------------------------------------------------------- | :-------------- |
| [Final project proposal](https://docs.google.com/document/d/1-mP0LZY0a5m3WhI7J1Yj_RWD8aPpTjU4-v1d5Lu2hIM) | Apr-7 @ 11:59pm |
| Final project report w/ code                                                                              | May-8 @ 11:59pm |
| Final project presentation                                                                                | May-13 @ 4:30pm |

## Resources and links

### Links

  - [Blackboard page for CSI 702 (Spring 2019)](https://mymasonportal.gmu.edu/webapps/blackboard/execute/courseMain?course_id=_355479_1) - The Blackboard page for this course.
  - [Slack workspace for CSI 702 (Spring 2019)](https://sp19-masoncsi702.slack.com/) - The Slack workspace for this course.
  - [XSEDE Course on Moodle](https://moodle.xsede.org) - The platform used to distribute the online components of this course.
  - [CS267 — Applications of Parallel Computers (Spring 2019)](https://sites.google.com/lbl.gov/cs267-spr2019/) - Course website for the Spring 2019 semester of UC Berkeley’s Applications of Parallel Computers course.
    The online XSEDE Moodle course is based on this course.

### Guides

  - [HOWTO — Setting up your virtual machine](/guides/howto_provision_virtual_machine.md) - How to provision a virtual machine to use as your development environment in CSI 702.

### Software

<table>

<thead>

<tr>

<th style="text-align:left;">

Software

</th>

<th style="text-align:left;">

OS

</th>

<th style="text-align:left;">

Description

</th>

</tr>

</thead>

<tbody>

<tr>

<td style="text-align:left;">

[Slack<br>(standalone app)<br>![Slack](/img/slack.svg)](https://slack.com/downloads)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux<br>iOS<br>Android

</td>

<td style="text-align:left;">

Slack is the primary communication medium for the course, replacing email and serving as a general-purpose discussion board.

</td>

</tr>

<tr>

<td style="text-align:left;">

[CLion<br>![CLion](/img/clion.png)](https://jetbrains.com/clion)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux

</td>

<td style="text-align:left;">

A cross-platform integrated development environment (IDE) designed specifically for programming in C++. Comes with many useful features enabled and also has a plugin ecosystem. There are [introductory tutorial videos available](https://www.jetbrains.com/clion/documentation/). As a current student, you get a free professional license for the editor if you [fill out and submit this form](https://www.jetbrains.com/shop/eform/students).

</td>

</tr>

<tr>

<td style="text-align:left;">

[GitHub Desktop<br>![GitHub Desktop](/img/github-desktop-logo.svg)](https://desktop.github.com)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux

</td>

<td style="text-align:left;">

A graphical interface for interacting with GitHub, built by GitHub. [The Linux-compatible version is available on GitHub](https://github.com/shiftkey/desktop/releases). User documentation from GitHub is available:

<ul>

<li>

<a href='https://help.github.com/desktop/guides/getting-started-with-github-desktop/'>Getting Starting with GitHub Desktop</a>

</li>

<li>

<a href='https://help.github.com/desktop/guides/contributing-to-projects/'>Contributing to projects with GitHub Desktop</a>

</li>

</ul>

</td>

</tr>

<tr>

<td style="text-align:left;">

[Virtualbox<br>![Virtualbox](/img/virtualbox.png)](https://www.virtualbox.org/wiki/Downloads)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux

</td>

<td style="text-align:left;">

VirtualBox is a cross-platform virtualization application that allows you to run multiple OSes, inside multiple virtual machines, at the same time.

</td>

</tr>

<tr>

<td style="text-align:left;">

[Vagrant<br>![Vagrant](/img/vagrant.svg)](https://www.vagrantup.com/downloads.html)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux

</td>

<td style="text-align:left;">

Vagrant is a tool for building and managing virtual machine environments in a single workflow using simple configuration files. We will use it to provision Virtualbox-based virtual machines.

</td>

</tr>

<tr>

<td style="text-align:left;">

[Intel MKL<br>![MKL](/img/intel.png)](https://software.intel.com/en-us/mkl/choose-download)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux

</td>

<td style="text-align:left;">

A library that features highly optimized, threaded, and vectorized math functions that maximize performance on each processor family. It uses industry-standard C and Fortran APIs for compatibility with popular BLAS, LAPACK, and FFTW functions.

</td>

</tr>

<tr>

<td style="text-align:left;">

[NVIDIA CUDA Toolkit<br>![MKL](/img/nvidia_cuda.png)](https://developer.nvidia.com/cuda-downloads)

</td>

<td style="text-align:left;">

Windows<br>macOS<br>Linux

</td>

<td style="text-align:left;">

A toolkit for developing, optimizing and deploying your applications on GPU-accelerated embedded systems, desktop workstations, enterprise data centers, cloud-based platforms and HPC supercomputers. Includes GPU-accelerated libraries, debugging and optimization tools, a C/C++ compiler and a runtime library to deploy your application.

</td>

</tr>

</tbody>

</table>

## License

[![Creative Commons License](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-sa/4.0/)

Unless otherwise noted, the course materials in this repository are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
