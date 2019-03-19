#include <common.hpp>

#include <sys/time.h>
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <random>
#include <string>
#include <vector>

double size;

//
// Tuned constants
//
const double density = 0.0005;
const double mass = 0.01;
const double cutoff = 0.01;
const double min_r = (cutoff / 100);
const double dt = 0.0005;

//
// Timing routines
//
std::chrono::time_point<std::chrono::high_resolution_clock> read_timer() {
  auto get_time = std::chrono::high_resolution_clock::now();
  return get_time;
}

//
// Keep density constant
//
void set_size(const int &n) { size = sqrt(density * n); }

//
// Initialize the particle positions and velocities
//
void init_particles(const int &n, std::vector<particle_t> &p) {
  // Use Mersenne twister engine to generate pseudo-random numbers.
  std::random_device rd;
  std::mt19937 engine(rd());

  // Filter MT engine's output to generate pseudo-random double values uniformly
  // distributed on the closed interval [-1, 1] (Note that the range is
  // [inclusive, inclusive]).
  std::uniform_real_distribution<double> vel_dist(-1.0, 1.0);

  // Constrain the box dimensions
  auto sx = static_cast<int>(ceil(sqrt(static_cast<double>(n))));
  int sy = (n + sx - 1) / sx;

  // Shuffle the particle positions so that they're not spatially sorted
  std::vector<int> shuffle(static_cast<unsigned long>(n));

  // Fills shuffle vector from 0 to n
  std::iota(std::begin(shuffle), std::end(shuffle), 0);

  // Shuffles the shuffle vector using the Mersenne twister RNG
  std::shuffle(std::begin(shuffle), std::end(shuffle), engine);

  for (int i = 0; i < n; i++) {
    // Make sure particles are not spatially sorted
    int k = shuffle[i];

    // Distribute particles evenly to ensure proper spacing
    p[i].x = size * (1. + (k % sx)) / (1 + sx);
    p[i].y = size * (1. + (k / sx)) / (1 + sy);

    // Assign random velocities within bound [-1, 1]
    p[i].vx = vel_dist(engine);
    p[i].vy = vel_dist(engine);
  }
}

//
// Interact two particles
//
void apply_force(
    particle_t &particle, particle_t &neighbor, double &dmin, double &davg, int &navg) {
  double dx = neighbor.x - particle.x;
  double dy = neighbor.y - particle.y;
  double r2 = dx * dx + dy * dy;

  if (r2 > cutoff * cutoff) {
    return;
  } else {
    if (r2 != 0) {
      if (r2 / (cutoff * cutoff) < dmin * dmin) {
        dmin = sqrt(r2) / cutoff;
      }
      davg += sqrt(r2) / cutoff;
      navg++;
    }
  }

  r2 = fmax(r2, min_r * min_r);
  double r = sqrt(r2);

  // Very simple short-range repulsive force
  double coef = (1 - cutoff / r) / r2 / mass;
  particle.ax += coef * dx;
  particle.ay += coef * dy;
}

//
// Integrate the ODE
//
void move(particle_t &p) {
  // Slightly simplified Velocity Verlet integration that conserves energy
  // better
  // than the explicit Euler method
  p.vx += p.ax * dt;
  p.vy += p.ay * dt;
  p.x += p.vx * dt;
  p.y += p.vy * dt;

  // Bounce from the walls
  while (p.x < 0 || p.x > size) {
    p.x = p.x < 0 ? -p.x : 2 * size - p.x;
    p.vx = -p.vx;
  }
  while (p.y < 0 || p.y > size) {
    p.y = p.y < 0 ? -p.y : 2 * size - p.y;
    p.vy = -p.vy;
  }
}

//
// I/O routines
//

// Save the summary or particle positions to a file.
void save(std::ofstream &f, const int &n, const std::vector<particle_t> &p) {
  static bool first = true;
  if (first) {
    f << n << " " << size << "\n";
    first = false;
  }
  for (int i = 0; i < n; i++) {
    f << p[i].x << " " << p[i].y << "\n";
  }
}

//
// Utility routines
//

// Define min/max functions
int min(const int &a, const int &b) { return a < b ? a : b; }

int max(const int &a, const int &b) { return a > b ? a : b; }
