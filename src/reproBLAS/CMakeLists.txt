add_library(reproBLAS)
target_sources(reproBLAS PRIVATE
	cdotc_sub.c  dnrm2.c       rdasum.c   rscasum.c     rzgemm.c     snrm2.c
	cdotu_sub.c  dsum.c        rddot.c    rscnrm2.c     rzgemv.c     ssum.c
	cgemm.c      dzasum.c      rdgemm.c   rsdot.c       rzsum_sub.c  zdotc_sub.c
	cgemv.c      dznrm2.c      rdgemv.c   rsgemm.c      sasum.c      zdotu_sub.c
	csum_sub.c   rcdotc_sub.c  rdnrm2.c   rsgemv.c      scasum.c     zgemm.c
	dasum.c      rcdotu_sub.c  rdsum.c    rsnrm2.c      scnrm2.c     zgemv.c
	ddot.c       rcgemm.c      rdzasum.c  rssum.c       sdot.c       zsum_sub.c
	dgemm.c      rcgemv.c      rdznrm2.c  rzdotc_sub.c  sgemm.c
	dgemv.c      rcsum_sub.c   rsasum.c   rzdotu_sub.c  sgemv.c)
