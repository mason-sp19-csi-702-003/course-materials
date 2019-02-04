#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include <x86intrin.h>

typedef union {
  __m256d v;
  double d[4];
} v4df_t;

std::chrono::time_point<std::chrono::high_resolution_clock> read_timer();
double sum_naive(const int &n, const std::vector<double> &a);
double sum_vectorized(const int &n, const std::vector<double> &a);

std::chrono::time_point<std::chrono::high_resolution_clock> read_timer() {
  auto get_time = std::chrono::high_resolution_clock::now();
  return get_time;
}

double sum_naive(const int &n, double *a) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += a[i];
  }

  return sum;
}

double sum_vectorized(const int &n, double *a) {
  v4df_t sum_i0_i1_i2_i3_vreg, sum_i4_i5_i6_i7_vreg, sum_i8_i9_i10_i11_vreg,
      sum_i12_i13_i14_i15_vreg, sum_i16_i17_i18_i19_vreg, sum_i20_i21_i22_i23_vreg,
      sum_i24_i25_i26_i27_vreg, sum_i28_i29_i30_i31_vreg, a_i0_i1_i2_i3_vreg,
      a_i4_i5_i6_i7_vreg, a_i8_i9_i10_i11_vreg, a_i12_i13_i14_i15_vreg,
      a_i16_i17_i18_i19_vreg, a_i20_i21_i22_i23_vreg, a_i24_i25_i26_i27_vreg,
      a_i28_i29_i30_i31_vreg;
  double sum = 0.0;

  sum_i0_i1_i2_i3_vreg.v = _mm256_setzero_pd();
  sum_i4_i5_i6_i7_vreg.v = _mm256_setzero_pd();
  sum_i8_i9_i10_i11_vreg.v = _mm256_setzero_pd();
  sum_i12_i13_i14_i15_vreg.v = _mm256_setzero_pd();
  sum_i16_i17_i18_i19_vreg.v = _mm256_setzero_pd();
  sum_i20_i21_i22_i23_vreg.v = _mm256_setzero_pd();
  sum_i24_i25_i26_i27_vreg.v = _mm256_setzero_pd();
  sum_i28_i29_i30_i31_vreg.v = _mm256_setzero_pd();

  int k_unroll_end = n / 32;

  int k = 0;
  for (; k < k_unroll_end; k++) {
    int a_shift = 32 * k;
    a_i0_i1_i2_i3_vreg.v = _mm256_load_pd(a + a_shift);
    a_i4_i5_i6_i7_vreg.v = _mm256_load_pd(a + a_shift + 4);
    a_i8_i9_i10_i11_vreg.v = _mm256_load_pd(a + a_shift + 8);
    a_i12_i13_i14_i15_vreg.v = _mm256_load_pd(a + a_shift + 12);
    a_i16_i17_i18_i19_vreg.v = _mm256_load_pd(a + a_shift + 16);
    a_i20_i21_i22_i23_vreg.v = _mm256_load_pd(a + a_shift + 20);
    a_i24_i25_i26_i27_vreg.v = _mm256_load_pd(a + a_shift + 24);
    a_i28_i29_i30_i31_vreg.v = _mm256_load_pd(a + a_shift + 28);

    sum_i0_i1_i2_i3_vreg.v = _mm256_add_pd(sum_i0_i1_i2_i3_vreg.v, a_i0_i1_i2_i3_vreg.v);
    sum_i4_i5_i6_i7_vreg.v = _mm256_add_pd(sum_i4_i5_i6_i7_vreg.v, a_i4_i5_i6_i7_vreg.v);
    sum_i8_i9_i10_i11_vreg.v =
        _mm256_add_pd(sum_i8_i9_i10_i11_vreg.v, a_i8_i9_i10_i11_vreg.v);
    sum_i12_i13_i14_i15_vreg.v =
        _mm256_add_pd(sum_i12_i13_i14_i15_vreg.v, a_i12_i13_i14_i15_vreg.v);
    sum_i16_i17_i18_i19_vreg.v =
        _mm256_add_pd(sum_i16_i17_i18_i19_vreg.v, a_i16_i17_i18_i19_vreg.v);
    sum_i20_i21_i22_i23_vreg.v =
        _mm256_add_pd(sum_i20_i21_i22_i23_vreg.v, a_i20_i21_i22_i23_vreg.v);
    sum_i24_i25_i26_i27_vreg.v =
        _mm256_add_pd(sum_i24_i25_i26_i27_vreg.v, a_i24_i25_i26_i27_vreg.v);
    sum_i28_i29_i30_i31_vreg.v =
        _mm256_add_pd(sum_i28_i29_i30_i31_vreg.v, a_i28_i29_i30_i31_vreg.v);

    // NOTE: The above eight _mm256_add_pd() functions can be replaced with the following
    // with no loss in performance:
    //
    // sum_i0_i1_i2_i3_vreg.v += a_i0_i1_i2_i3_vreg.v;
    // sum_i4_i5_i6_i7_vreg.v += a_i4_i5_i6_i7_vreg.v;
    // sum_i8_i9_i10_i11_vreg.v += a_i8_i9_i10_i11_vreg.v;
    // sum_i12_i13_i14_i15_vreg.v += a_i12_i13_i14_i15_vreg.v;
    // sum_i16_i17_i18_i19_vreg.v += a_i16_i17_i18_i19_vreg.v;
    // sum_i20_i21_i22_i23_vreg.v += a_i20_i21_i22_i23_vreg.v;
    // sum_i24_i25_i26_i27_vreg.v += a_i24_i25_i26_i27_vreg.v;
    // sum_i28_i29_i30_i31_vreg.v += a_i28_i29_i30_i31_vreg.v;
  }

  sum_i0_i1_i2_i3_vreg.v =
      _mm256_add_pd(sum_i0_i1_i2_i3_vreg.v, sum_i16_i17_i18_i19_vreg.v);
  sum_i4_i5_i6_i7_vreg.v =
      _mm256_add_pd(sum_i4_i5_i6_i7_vreg.v, sum_i20_i21_i22_i23_vreg.v);
  sum_i8_i9_i10_i11_vreg.v =
      _mm256_add_pd(sum_i8_i9_i10_i11_vreg.v, sum_i24_i25_i26_i27_vreg.v);
  sum_i12_i13_i14_i15_vreg.v =
      _mm256_add_pd(sum_i12_i13_i14_i15_vreg.v, sum_i28_i29_i30_i31_vreg.v);

  sum_i0_i1_i2_i3_vreg.v =
      _mm256_add_pd(sum_i0_i1_i2_i3_vreg.v, sum_i8_i9_i10_i11_vreg.v);
  sum_i4_i5_i6_i7_vreg.v =
      _mm256_add_pd(sum_i4_i5_i6_i7_vreg.v, sum_i12_i13_i14_i15_vreg.v);

  sum_i0_i1_i2_i3_vreg.v = _mm256_add_pd(sum_i0_i1_i2_i3_vreg.v, sum_i4_i5_i6_i7_vreg.v);

  sum += sum_i0_i1_i2_i3_vreg.d[0] + sum_i0_i1_i2_i3_vreg.d[1] +
         sum_i0_i1_i2_i3_vreg.d[2] + sum_i0_i1_i2_i3_vreg.d[3];

  int n_fringe = k_unroll_end * 32;

  for (; n_fringe < n; n_fringe++) {
    sum += a[n_fringe];
  }

  return sum;
}

int main(int argc, char **argv) {
  std::mt19937 generator(7802);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  // Perform summation on vector with one million elements
  int n = 1000000;

  // Repeat summation 1000 times to reduce noise
  int n_iterations = 1000;

  // Store summations as sanity check
  double sum1 = 0;
  double sum2 = 0;
  double sum3 = 0;
  double sum4 = 0;

  // Declare and initialize variables to save how long the benchmark took to run
  double seconds_naive = -1.0;
  double seconds_vectorized = -1.0;
  double seconds_naive_aligned = -1.0;
  double seconds_vectorized_aligned = -1.0;

  // Allocate memory for test vector, one of which is memory aligned using _mm_malloc()
  std::vector<double> test_vector(n);
  const size_t size_test_vector = sizeof(double) * n;
  auto *test_vector_aligned = static_cast<double *>(_mm_malloc(size_test_vector, 32));

  // Fill test vector with random values
  for (int i = 0; i < n; i++) {
    double vector_element = distribution(generator);
    test_vector[i] = vector_element;
    test_vector_aligned[i] = vector_element;
  }

  // Benchmark naive sum
  auto timer = read_timer();
  for (int it = 0; it < n_iterations; ++it) {
    sum1 = sum_naive(n, test_vector.data());
  }
  seconds_naive =
      std::chrono::duration<double, std::micro>(read_timer() - timer).count() / 1e6;

  // Benchmark vectorized sum
  timer = read_timer();
  for (int it = 0; it < n_iterations; ++it) {
    sum2 = sum_vectorized(n, test_vector.data());
  }
  seconds_vectorized =
      std::chrono::duration<double, std::micro>(read_timer() - timer).count() / 1e6;

  // Benchmark naive sum (aligned memory)
  timer = read_timer();
  for (int it = 0; it < n_iterations; ++it) {
    sum3 = sum_naive(n, test_vector_aligned);
  }
  seconds_naive_aligned =
      std::chrono::duration<double, std::micro>(read_timer() - timer).count() / 1e6;

  // Benchmark vectorized sum (memory aligned)
  timer = read_timer();
  for (int it = 0; it < n_iterations; ++it) {
    sum4 = sum_vectorized(n, test_vector_aligned);
  }
  seconds_vectorized_aligned =
      std::chrono::duration<double, std::micro>(read_timer() - timer).count() / 1e6;

  // Report results
  std::cout << "Benchmark results\nNaive summation: " << seconds_naive
            << " seconds\nVectorized summation: " << seconds_vectorized
            << " seconds\nNaive summation (aligned memory): " << seconds_naive_aligned
            << " seconds\nVectorized summation (aligned memory): "
            << seconds_vectorized_aligned << " seconds\n\n";

  std::cout << "Consistency check\nValue of naive summation: " << sum1
            << "\nValue of vectorized summation: " << sum2
            << "\nValue of naive summation (aligned memory): " << sum3
            << "\nValue of vectorized summation (aligned memory): " << sum4 << "\n";

  // Free memory
  _mm_free(test_vector_aligned);

  return 0;
}
