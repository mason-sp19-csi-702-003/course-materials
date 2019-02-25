from libcpp.string cimport string

cdef extern from "common.hpp":
    cdef cppclass cli_parameters_t:
        cli_parameters_t() except +
        int number_particles
        string output_filename
        string summary_filename
        bint disable_checks
        string benchmark_mode


cdef extern from "serial.hpp" namespace "serial":
    string serial(cli_parameters_t &cli_parameters)