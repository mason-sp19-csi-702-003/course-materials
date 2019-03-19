#ifndef APC_HW2_COMMON_HPP
#define APC_HW2_COMMON_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

//
// Saving parameters
//
const int NSTEPS = 1000;
const int SAVEFREQ = 10;

//
// min/max functions
//
int min(const int &a, const int &b);
int max(const int &a, const int &b);

//
// CLI Parameters data structure
//
struct cli_parameters_t {
  int number_particles;
  std::string output_filename;
  std::string summary_filename;
  bool disable_checks;
  std::string benchmark_mode;
};

//
// Particle data structure
//
struct particle_t {
  double x;
  double y;
  double vx;
  double vy;
  double ax;
  double ay;
};

//
// Timing routines
//
std::chrono::time_point<std::chrono::high_resolution_clock> read_timer();

//
// Simulation routines
//
void set_size(const int &n);
void init_particles(const int &n, std::vector<particle_t> &p);
void apply_force(
    particle_t &particle, particle_t &neighbor, double &dmin, double &davg, int &navg);
void move(particle_t &p);

//
// I/O routines
//
void save(std::ofstream &f, const int &n, const std::vector<particle_t> &p);
#endif   // APC_HW2_COMMON_HPP
