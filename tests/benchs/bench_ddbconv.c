#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <binnedBLAS.h>

#include "../common/test_opt.h"
#include "../common/test_time.h"
#include "../common/test_metric.h"

#include "../../config.h"

#include "bench_vecvec_fill_header.h"

static opt_option fold;

static void bench_ddbconv_options_initialize(void){
  fold._int.header.type       = opt_int;
  fold._int.header.short_name = 'k';
  fold._int.header.long_name  = "fold";
  fold._int.header.help       = "fold";
  fold._int.required          = 0;
  fold._int.min               = 2;
  fold._int.max               = binned_DBMAXFOLD;
  fold._int.value             = DIDEFAULTFOLD;
}

int bench_vecvec_fill_show_help(void){
  bench_ddbconv_options_initialize();

  opt_show_option(fold);

  return 0;
}

const char* bench_vecvec_fill_name(int argc, char** argv){
  (void)argc;
  (void)argv;
  static char name_buffer[MAX_LINE];

  bench_ddbconv_options_initialize();
  opt_eval_option(argc, argv, &fold);

  snprintf(name_buffer, MAX_LINE * sizeof(char), "Benchmark [ddbconv] (fold = %d)", fold._int.value);
  return name_buffer;
}

int bench_vecvec_fill_test(int argc, char** argv, int N, int FillX, double RealScaleX, double ImagScaleX, int incX, int FillY, double RealScaleY, double ImagScaleY, int incY, int trials){
  (void)argc;
  (void)argv;
  (void)FillY;
  (void)RealScaleY;
  (void)ImagScaleY;
  (void)incY;
  int rc = 0;
  int i;
  double res = 0.0;
  double_binned *ires;

  bench_ddbconv_options_initialize();
  opt_eval_option(argc, argv, &fold);

  util_random_seed();

  double *X = util_dvec_alloc(N, incX);

  //fill x
  util_dvec_fill(N, X, incX, FillX, RealScaleX, ImagScaleX);

  ires = binned_dballoc(fold._int.value);
  binned_dbsetzero(fold._int.value, ires);
  binnedBLAS_dbdsum(fold._int.value, N, X, incX, ires);
  time_tic();
  for(i = 0; i < trials; i++){
    res = binned_ddbconv(fold._int.value, ires);
  }
  time_toc();
  free(ires);

  metric_load_double("time", time_read());
  metric_load_double("res", res);
  metric_load_double("trials", (double)trials);
  metric_load_double("input", 1.0);
  metric_load_double("output", 1.0);
  metric_load_double("normalizer", 1.0);
  metric_dump();

  free(X);
  return rc;
}
