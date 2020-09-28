add_library(binnedBLAS OBJECT)
target_sources(binnedBLAS PRIVATE
	cbcdotc.c  dbdasum.c  dbdsum.c   sbcasum.c  sbsdot.c  zbzdotc.c
	cbcdotu.c  dbddot.c   dbzasum.c  sbcssq.c   sbsssq.c  zbzdotu.c
	cbcsum.c   dbdssq.c   dbzssq.c   sbsasum.c  sbssum.c  zbzsum.c)
