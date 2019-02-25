#include <serial.hpp>

#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

#include <common.hpp>

//
// Benchmarking program
//

namespace serial {
double benchmark_sort(
    const int &n, std::vector<particle_t> &particles, int &navg, int &nabsavg,
    double &absmin, double &absavg, double &davg, double &dmin,
    const bool &disable_checks, std::ofstream &fsave) {
  //
  // Simulate a number of time steps
  //
  
  struct {
    bool operator()(const particle_t &a, const particle_t &b) const
    {   
      return a.x < b.x;
    }   
  } particles_x_sort;
  
  auto timer = read_timer();

  for (int step = 0; step < NSTEPS; step++) {
    navg = 0;
    davg = 0.0;
    dmin = 1.0;
    
    std::sort(particles.begin(), particles.end(), particles_x_sort);

    //
    // Compute forces
    //
    for (int i = 0; i < n; i++) {
      int j_forwards = i + 1;
      int j_backwards = i - 1;
      double x_pos_forwards = particles[i].x + 0.01;
      double x_pos_backwards = particles[i].x - 0.01;
      
      particles[i].ax = 0.0;
      particles[i].ay = 0.0;
      
      if (j_forwards < n) {
        while (j_forwards < n && x_pos_forwards > particles[j_forwards].x) {
          apply_force(particles[i], particles[j_forwards], dmin, davg, navg);
          j_forwards++;
        }
      }
      
      if (j_backwards >= 0) {
        while (j_backwards >= 0 && particles[j_backwards].x > x_pos_backwards) {
          apply_force(particles[i], particles[j_backwards], dmin, davg, navg);
          j_backwards--;
        }
      }
    }

    //
    // Move particles
    //
    for (int i = 0; i < n; i++) {
      move(particles[i]);
    }

    if (!disable_checks) {
      //
      // Computing statistical data
      //
      if (navg) {
        absavg += davg / navg;
        nabsavg++;
      }
      if (dmin < absmin) {
        absmin = dmin;
      }

      //
      // Save if necessary
      //
      if (fsave && (step % SAVEFREQ) == 0) {
        save(fsave, n, particles);
      }
    }
  }

  auto simulation_time =
      std::chrono::duration<double, std::micro>(read_timer() - timer).count() / 1e6;

  return simulation_time;
}
double benchmark_naive(
    const int &n, std::vector<particle_t> &particles, int &navg, int &nabsavg,
    double &absmin, double &absavg, double &davg, double &dmin,
    const bool &disable_checks, std::ofstream &fsave) {
  //
  // Simulate a number of time steps
  //
  auto timer = read_timer();

  for (int step = 0; step < NSTEPS; step++) {
    navg = 0;
    davg = 0.0;
    dmin = 1.0;

    //
    // Compute forces
    //
    for (int i = 0; i < n; i++) {
      particles[i].ax = 0.0;
      particles[i].ay = 0.0;
      for (int j = 0; j < n; j++)
        apply_force(particles[i], particles[j], dmin, davg, navg);
    }

    //
    // Move particles
    //
    for (int i = 0; i < n; i++) {
      move(particles[i]);
    }

    if (!disable_checks) {
      //
      // Computing statistical data
      //
      if (navg) {
        absavg += davg / navg;
        nabsavg++;
      }
      if (dmin < absmin) {
        absmin = dmin;
      }

      //
      // Save if necessary
      //
      if (fsave && (step % SAVEFREQ) == 0) {
        save(fsave, n, particles);
      }
    }
  }

  auto simulation_time =
      std::chrono::duration<double, std::micro>(read_timer() - timer).count() / 1e6;

  return simulation_time;
}
//
// Serial implementation of simulation
//
std::string serial(cli_parameters_t &cli_parameters) {
  int navg;
  int nabsavg = 0;
  double davg;
  double dmin;
  double absmin = 1.0;
  double absavg = 0.0;

  // Check number of particles for simulation
  int n = cli_parameters.number_particles;

  // Check if output files should be saved.
  std::string save_filename = cli_parameters.output_filename;
  std::string summary_filename = cli_parameters.summary_filename;

  // Open files (if specified)
  std::ofstream fsave;
  if (save_filename.empty()) {
    fsave.open(nullptr);
  } else {
    fsave.open(save_filename);
  }

  std::ofstream fsum;
  if (summary_filename.empty()) {
    fsum.open(nullptr);
  } else {
    fsum.open(summary_filename, std::ios::app);
  }

  // Initialize particles for simulation
  std::vector<particle_t> particles(static_cast<unsigned long>(n));
  set_size(n);
  init_particles(n, particles);

  // Disable checks and outputs?
  bool disable_checks = cli_parameters.disable_checks;

  double simulation_time;
  if (cli_parameters.benchmark_mode == "naive") {
    simulation_time = benchmark_naive(
        n, particles, navg, nabsavg, absmin, absavg, davg, dmin, disable_checks, fsave);
  } else if (cli_parameters.benchmark_mode == "sort") {
    simulation_time = benchmark_sort(
        n, particles, navg, nabsavg, absmin, absavg, davg, dmin, disable_checks, fsave);
  } else {
    return "Not a mode!";
  }

  std::ostringstream results_stdout;

  results_stdout << "n = " << n << ", simulation time = " << simulation_time
                 << " seconds";

  if (!disable_checks) {
    if (nabsavg) {
      absavg /= nabsavg;
    }
    // - the minimum distance absmin between 2 particles during the run of
    //   the simulation
    // - A Correct simulation will have particles stay at greater than 0.4
    //   (of cutoff) with typical values between .7-.8
    // - A simulation were particles don't interact correctly will be less
    //   than 0.4 (of cutoff) with typical values between .01-.05
    // - The average distance absavg is ~.95 when most particles are
    //   interacting correctly and ~.66 when no particles are interacting
    results_stdout << ", absmin = " << absmin << ", absavg = " << absavg;
    if (absmin < 0.4) {
      results_stdout << "\nThe minimum distance is below 0.4 meaning that some "
                        "particle is not interacting";
    }
    if (absavg < 0.8) {
      results_stdout << "\nThe average distance is below 0.8 meaning that most "
                        "particles are not interacting";
    }
  }
  results_stdout << "\n";
  std::string results_string = results_stdout.str();

  // std::cout << results_string;

  //
  // Printing summary data
  //
  if (fsum) {
    fsum << n << " " << simulation_time << "\n";
  }

  return results_string;
}
}   // namespace serial
