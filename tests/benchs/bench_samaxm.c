#include <rblas.h>
#include <IndexedFP.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../common/test_opt.h"
#include "../common/test_time.h"
#include "../common/test_perf.h"
#include <rblas.h>
#include <IndexedFP.h>

#include "vecvec_fill_bench_header.h"

int vecvec_fill_bench_desc(void){
  char *op_names[] = {"s_mul", "s_cmp", "s_orb"};
  int op_counts[] = {1, 1, 1};
  perf_output_desc(3, op_names, op_counts);
  return 0;
}

int vecvec_fill_bench_show_help(void){
  return 0;
}

const char* vecvec_fill_bench_name(int argc, char** argv){
  static char name_buffer[MAX_LINE];
  snprintf(name_buffer, MAX_LINE * sizeof(char), "Benchmark [samaxm]");
  return name_buffer;
}

int vecvec_fill_bench_test(int argc, char** argv, int N, int incx, int incy, int type, double scale, double cond, int trials){
  int rc = 0;
  float res;
  I_float Ires;
  float *x = svec_alloc(N, incx);
  float *y = svec_alloc(N, incy);

  util_random_seed();

  //fill empty space with random data to check increment
  svec_fill(N * incx, x, 1, vec_fill_RAND, 1.0, 1.0);
  svec_fill(N * incy, y, 1, vec_fill_RAND, 1.0, 1.0);

  //fill x
  svec_fill(N, x, incx, type, scale, cond);

  //fill y with 1 where necessary
  svec_fill(N, y, incy, vec_fill_CONSTANT, 1.0, 1.0);

  time_tic();
  for(int i = 0; i < trials; i++){
    res = samaxm(N, x, incx, y, incy);
  }
  time_toc();

  perf_output_perf(time_read(), N, trials);

  free(x);
  free(y);
  return rc;
}
