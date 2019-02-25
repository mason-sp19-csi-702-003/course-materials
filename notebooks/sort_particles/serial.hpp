#ifndef APC_HW2_SERIAL_HPP
#define APC_HW2_SERIAL_HPP

#include <string>

#include <common.hpp>

namespace serial {
double benchmark_naive(
    const int &n, std::vector<particle_t> &particles, int &navg, int &nabsavg,
    double &absmin, double &absavg, double &davg, double &dmin,
    const bool &disable_checks, std::ofstream &fsave);
double benchmark_sort(
    const int &n, std::vector<particle_t> &particles, int &navg, int &nabsavg,
    double &absmin, double &absavg, double &davg, double &dmin,
    const bool &disable_checks, std::ofstream &fsave);
std::string serial(cli_parameters_t &cli_parameters);
}   // namespace serial

#endif   // APC_HW2_SERIAL_HPP
