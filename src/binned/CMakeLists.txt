add_library(binned OBJECT)
target_sources(binned PRIVATE
	cballoc.c      cmsetzero.c   dmdmadd.c     sindex.c      zbrenorm.c
	cbcadd.c       cmsmset.c     dmdmaddsq.c   smbins.c      zbsetzero.c
	cbcbadd.c      cmsrescale.c  dmdmset.c     smdenorm.c    zbsize.c
	cbcbaddv.c     cmsupdate.c   dmdrescale.c  smindex0.c    zbzadd.c
	cbcbset.c      dballoc.c     dmdupdate.c   smindex.c     zbzbadd.c
	cbcconv.c      dbbound.c     dmindex0.c    smnegate.c    zbzbaddv.c
	cbcdeposit.c   dbdadd.c      dmindex.c     smprint.c     zbzbset.c
	cbcupdate.c    dbdbadd.c     dmnegate.c    smrenorm.c    zbzconv.c
	cbnegate.c     dbdbaddsq.c   dmprint.c     smsadd.c      zbzdeposit.c
	cbnum.c        dbdbaddv.c    dmrenorm.c    smsconv.c     zbzupdate.c
	cbprint.c      dbdbset.c     dmsetzero.c   smsdeposit.c  zmdenorm.c
	cbrenorm.c     dbdconv.c     dscale.c      smsetzero.c   zmdmset.c
	cbsbset.c      dbddeposit.c  sballoc.c     smsmadd.c     zmdrescale.c
	cbsetzero.c    dbdupdate.c   sbbound.c     smsmaddsq.c   zmdupdate.c
	cbsize.c       dbnegate.c    sbnegate.c    smsmset.c     zmnegate.c
	cbsupdate.c    dbnum.c       sbnum.c       smsrescale.c  zmprint.c
	ccbconv_sub.c  dbprint.c     sbprint.c     smsupdate.c   zmrenorm.c
	ccmconv_sub.c  dbrenorm.c    sbrenorm.c    ssbconv.c     zmsetzero.c
	cmcadd.c       dbsetzero.c   sbsadd.c      sscale.c      zmzadd.c
	cmcconv.c      dbsize.c      sbsbadd.c     ssmconv.c     zmzconv.c
	cmcdeposit.c   ddbconv.c     sbsbaddsq.c   ufp.c         zmzdeposit.c
	cmcmadd.c      ddmconv.c     sbsbaddv.c    ufpf.c        zmzmadd.c
	cmcmset.c      dindex.c      sbsbset.c     zballoc.c     zmzmset.c
	cmcupdate.c    dmbins.c      sbsbze.c      zbdbset.c     zmzupdate.c
	cmdenorm.c     dmdadd.c      sbsconv.c     zbdupdate.c   zzbconv_sub.c
	cmnegate.c     dmdconv.c     sbsdeposit.c  zbnegate.c    zzmconv_sub.c
	cmprint.c      dmddeposit.c  sbsetzero.c   zbnum.c
	cmrenorm.c     dmdenorm.c    sbsupdate.c   zbprint.c)
