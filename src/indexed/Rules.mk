TARGETS := libindexed.a foo$(EXE)
SUBDIRS :=

INSTALL_LIB := $(TARGETS)

LIBINDEXED := $(OBJPATH)/libindexed.a

libindexed.a_DEPS = diadd.o diconv.o diindex.o dimem.o dinegate.o diprint.o direnorm.o diupdate.o siadd.o siconv.o siindex.o simem.o sinegate.o siprint.o sirenorm.o siupdate.o dscale.o sscale.o dmdrescale.o zmdrescale.o smsrescale.o cmsrescale.o dmdmaddsq.o smsmaddsq.o ufp.o ufpf.o

foo$(EXE)_DEPS = foo.o $(LIBINDEXED)
