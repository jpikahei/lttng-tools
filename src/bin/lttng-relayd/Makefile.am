AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src \
			  -DINSTALL_BIN_PATH=\""$(lttnglibexecdir)"\" \
			  -DINSTALL_LIB_PATH=\""$(libdir)"\"

AM_CFLAGS = -fno-strict-aliasing

bin_PROGRAMS = lttng-relayd

lttng_relayd_SOURCES = main.c lttng-relayd.h utils.h utils.c cmd.h \
                       index.c index.h live.c live.h ctf-trace.c ctf-trace.h \
                       cmd-generic.c cmd-generic.h \
                       cmd-2-1.c cmd-2-1.h \
                       cmd-2-2.c cmd-2-2.h \
                       cmd-2-4.c cmd-2-4.h \
                       health-relayd.c health-relayd.h

# link on liblttngctl for check if relayd is already alive.
lttng_relayd_LDADD = -lrt -lurcu-common -lurcu \
		$(top_builddir)/src/lib/lttng-ctl/liblttng-ctl.la \
		$(top_builddir)/src/common/sessiond-comm/libsessiond-comm.la \
		$(top_builddir)/src/common/hashtable/libhashtable.la \
		$(top_builddir)/src/common/libcommon.la \
		$(top_builddir)/src/common/compat/libcompat.la \
		$(top_builddir)/src/common/index/libindex.la \
		$(top_builddir)/src/common/health/libhealth.la
