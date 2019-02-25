#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Autograder for HW2a."""

import argparse
import subprocess
import sys
from typing import NamedTuple, Tuple, Union

import numpy as np
import pandas as pd
import statsmodels.formula.api as smf


class Benchmarks(NamedTuple):
    """Container of simulation benchmarks."""

    serial: pd.DataFrame


def apply_grading_schema(slope: float) -> float:
    """Compute grade for a given scaling slope.

    Parameters
    ----------
    slope : float
        Slope (log-log) of scaling benchmarks.

    Returns
    -------
    float
        Grade as a percentage.
    """
    if slope < 1.4:
        return 100.0

    elif slope < 1.5:
        return 90.00 + 10.00 * (1.5 - slope) / 0.1

    elif slope < 2.0:
        return 90.00 * (2.0 - slope) / 0.5

    else:
        return 0.00


def read_summary_file(summary_file: str) -> Benchmarks:
    """Read simulation summary file data.

    Parameters
    ----------
    summary_file : str
        File containing particle counts and simulation run-times.

    Returns
    -------
    Benchmarks
        Container of benchmark runs.
    """
    summary_data: pd.DataFrame = pd.read_table(
        summary_file, sep="\s+", header=None, names=["particles", "runtime"]
    )

    return Benchmarks(serial=summary_data)


def find_loglog_slope(benchmarks: Benchmarks) -> float:
    """Apply log-log transformation and fit benchmarking data using linear regression.
    
    Parameters
    ----------
    benchmarks: Benchmarks
        Container of benchmark runs.

    Returns
    -------
    float
        Slope (log-log) of scaling benchmarks.
    """

    slope: float = smf.ols(
        "np.log10(runtime) ~ np.log10(particles)", data=benchmarks.serial
    ).fit().params[1]

    return slope


def plot_scaling_results(benchmarks: Benchmarks) -> str:
    """Generate ASCII-style scaling plots with gnuplot.
    
    Parameters
    ----------
    benchmarks: Benchmarks
        Container of benchmark runs.


    Returns
    -------
    str
        ASCII-formatted scaling plots.
    """
    benchmark_runs: np.array = benchmarks.serial.values

    gnuplot = subprocess.Popen(
        ["gnuplot"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=False
    )

    gnuplot.stdin.write(
        """set encoding utf8
        set term dumb size 130,22
        set multiplot layout 1,2 title 'Serial Scaling Plots'
        set lmargin 10
        set title 'Simulation time vs number of particles'
        unset key
        set tics nomirror scale 0.2
        set offsets graph 0.05, 0.05, 0.05, 0.05
        set xlabel 'Number of particles'
        set ylabel 'Sim. time (s)'
        plot '-' using 1:2 with points pt 15 notitle
        """.encode(
            "utf-8"
        )
    )

    for run in benchmark_runs:
        gnuplot.stdin.write("{0:f} {1:f}\n".format(run[0], run[1]).encode("utf-8"))

    gnuplot.stdin.write(
        """e
        set title 'Simulation time vs number of particles (log-log)'
        unset key
        set tics nomirror scale 0.2
        set offsets graph 0.05, 0.05, 0.05, 0.05
        set logscale xy 10
        set xlabel 'Number of particles'
        set ylabel 'Sim. time (s)'
        plot '-' using 1:2 with points pt 15 notitle
        """.encode(
            "utf-8"
        )
    )

    for run in benchmark_runs:
        gnuplot.stdin.write("{0:f} {1:f}\n".format(run[0], run[1]).encode("utf-8"))

    gnuplot.stdin.write("e\n" "unset multiplot\n".encode("utf-8"))

    gnuplot.stdin.flush()

    stdout = gnuplot.communicate()[0]

    return stdout.decode("utf-8")


def grade_runs(benchmarks: Benchmarks) -> float:
    """Grade runs and print results.

    Parameters
    ----------
    benchmarks: Benchmarks
        Container of benchmark runs.

    Return
    ------
    grade: float
        Grade for assignment.

    """
    slope: float = find_loglog_slope(benchmarks)
    grade: float = apply_grading_schema(slope)

    scaling_plot: str = plot_scaling_results(benchmarks)

    print("\nScaling results:")
    print(scaling_plot)
    print("O(n^m) log-log slope: m = {0:.4f}\n".format(round(slope, 4)))

    return grade


def autograde_hw2a(summary_file: str) -> None:
    """Autograde summary file.

    Parameters
    ----------
    summary_file : str
        File containing particle counts and simulation run-times.

    """
    benchmarks: Benchmarks = read_summary_file(summary_file)
    grade: float = grade_runs(benchmarks)

    print("Serial Grade = {0:.2f}\n".format(grade))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Autograder for Homework 2, Part A.")
    parser.add_argument(
        "summaryfile",
        type=str,
        help="Summary file for simulation runs over different particle counts.",
    )
    args = parser.parse_args()

    autograde_hw2a(summary_file=args.summaryfile)
