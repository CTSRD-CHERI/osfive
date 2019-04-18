OSDIR ?= ${CURDIR}/osfive
OBJDIR ?= ${CURDIR}/obj
OSOBJDIR = ${OBJDIR}/${OSDIR}

include ${OSDIR}/lib/libaeabi/Makefile.inc
include ${OSDIR}/lib/libc/Makefile.inc
include ${OSDIR}/lib/libfdt/Makefile.inc
include ${OSDIR}/lib/libfont/Makefile.inc
include ${OSDIR}/lib/libFLAC/Makefile.inc
include ${OSDIR}/lib/mbedtls/Makefile.inc
include ${OSDIR}/lib/md5/Makefile.inc
include ${OSDIR}/lib/tinycrypt/Makefile.inc
include ${OSDIR}/lib/xz-embedded/Makefile.inc

include ${OSDIR}/mk/binutils.mk
include ${OSDIR}/mk/clean.mk
include ${OSDIR}/mk/compile.mk
include ${OSDIR}/mk/host.mk
include ${OSDIR}/mk/info.mk
include ${OSDIR}/mk/kernel.mk
include ${OSDIR}/mk/library.mk
include ${OSDIR}/mk/link.mk
include ${OSDIR}/mk/machine.mk
include ${OSDIR}/mk/user.mk