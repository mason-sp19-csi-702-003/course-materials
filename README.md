CSI 702 course materials
<img src="img/course-logo-semester-square-section-003.svg" align="right" height=150>
================
Spring 2019 semester

  - [Syllabus](#syllabus)
  - [Schedule](#schedule)
  - [Homeworks](#homeworks)
  - [Final project](#final-project)
  - [Resources and links](#resources-and-links)
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

| \# | Description                                                | Due date         |
| -: | :--------------------------------------------------------- | :--------------- |
|  0 | [Describing a Parallel Application](homework/homework0.md) | Feb-1 @ 11:59pm  |
|  1 | Optimize Matrix Multiplication                             | Feb-15 @ 11:59pm |
|  2 | Parallelizing a particle simulation (Part 1)               | Mar-8 @ 11:59pm  |
|  3 | Parallelizing a particle simulation (Part 2)               | Mar-22 @ 11:59pm |
|  4 | Parallelizing a particle simulation (Part 3)               | Apr-1 @ 4:00pm   |
|  5 | Parallelizing Genome Assembly                              | Apr-26 @ 11:59pm |

## Final project

| Description                  | Due date        |
| :--------------------------- | :-------------- |
| Final project proposal       | Apr-5 @ 11:59pm |
| Final project report w/ code | May-8 @ 11:59pm |
| Final project presentation   | May-13 @ 4:30pm |

## Resources and links

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

[CLion<br>![CLion](img/clion-logo.svg)](https://jetbrains.com/clion)

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

[GitHub Desktop<br>![GitHub Desktop](img/github-desktop-logo.svg)](https://desktop.github.com)

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

</tbody>

</table>

## License

[![Creative Commons License](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-sa/4.0/)

Unless otherwise noted, the course materials in this repository are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
