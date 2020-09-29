add_library(binnedBLAS OBJECT)
set(generated_srcs
	camaxm_sub.ccog  damax.ccog    dmdsum.ccog   smcasum.ccog     zamax_sub.ccog
	camax_sub.ccog   damaxm.ccog   dmzasum.ccog  smcssq.ccog      zbzgemm.ccog
	cbcgemm.ccog     dbdgemm.ccog  dmzssq.ccog   smsasum.ccog     zbzgemv.ccog
	cbcgemv.ccog     dbdgemv.ccog  samax.ccog    smsdot.ccog      zmzdotc.ccog
	cmcdotc.ccog     dmdasum.ccog  samaxm.ccog   smsssq.ccog      zmzdotu.ccog
	cmcdotu.ccog     dmddot.ccog   sbsgemm.ccog  smssum.ccog      zmzsum.ccog
	cmcsum.ccog      dmdssq.ccog   sbsgemv.ccog  zamaxm_sub.ccog)
set_source_files_properties(${generated_srcs} PROPERTIES
	LANGUAGE C
	COMPILE_OPTIONS $<IF:$<C_COMPILER_ID:MSVC>,/TC,-xc>)
target_sources(binnedBLAS PRIVATE ${generated_srcs}
	cbcdotc.c  dbdasum.c  dbdsum.c   sbcasum.c  sbsdot.c  zbzdotc.c
	cbcdotu.c  dbddot.c   dbzasum.c  sbcssq.c   sbsssq.c  zbzdotu.c
	cbcsum.c   dbdssq.c   dbzssq.c   sbsasum.c  sbssum.c  zbzsum.c)
