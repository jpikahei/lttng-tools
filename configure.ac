AC_INIT([lttng-tools],[2.4.0-pre1],[dgoulet@efficios.com],[],[http://lttng.org])
AC_CONFIG_AUX_DIR([config])
AC_CANONICAL_TARGET
AC_CANONICAL_HOST
AC_CONFIG_MACRO_DIR([config])
AM_INIT_AUTOMAKE([foreign dist-bzip2 no-dist-gzip])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Compute minor/major/patchlevel version numbers
AC_PROG_SED
major_version=$(echo AC_PACKAGE_VERSION | sed 's/^\([[0-9]]\)*\.[[0-9]]*\.[[0-9]]*.*$/\1/')
minor_version=$(echo AC_PACKAGE_VERSION | sed 's/^[[0-9]]*\.\([[0-9]]*\)\.[[0-9]]*.*$/\1/')
patchlevel_version=$(echo AC_PACKAGE_VERSION | sed 's/^[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\).*$/\1/')
AC_SUBST([MAJOR_VERSION], [$major_version])
AC_SUBST([MINOR_VERSION], [$minor_version])
AC_SUBST([PATCHLEVEL_VERSION], [$patchlevel_version])
AC_DEFINE_UNQUOTED([VERSION_MAJOR], $major_version, [LTTng-Tools major version number])
AC_DEFINE_UNQUOTED([VERSION_MINOR], $minor_version, [LTTng-Tools minor version number])
AC_DEFINE_UNQUOTED([VERSION_PATCHLEVEL], $patchlevel_version, [LTTng-Tools patchlevel version number])

version_name="Dominus Vobiscum"
version_description="A very succulent line-up of beers brewed at Microbrasserie Charlevoix. Elaborated starting from special malts and fermented with a Belgian yeast. These beers are refermented in bottle and will make you discover the richness of wheat, amber and triple styles."

AC_DEFINE_UNQUOTED([VERSION_NAME], ["$version_name"], "")
AC_DEFINE_UNQUOTED([VERSION_DESCRIPTION], ["$version_description"], "")

AC_CONFIG_HEADERS([include/config.h])

AC_PROG_GREP
# libtool link_all_deplibs fixup. See http://bugs.lttng.org/issues/321.
AC_ARG_ENABLE(libtool-linkdep-fixup,
	AS_HELP_STRING([--disable-libtool-linkdep-fixup],
			[disable the libtool fixup for linking all dependent libraries (link_all_deplibs)]),
	libtool_fixup=$enableval,
	libtool_fixup=yes)

AS_IF([test "x$libtool_fixup" = "xyes"],
	    [
	    libtool_m4="$srcdir/config/libtool.m4"
	    libtool_flag_pattern=".*link_all_deplibs\s*,\s*\$1\s*)"
	    AC_MSG_CHECKING([for occurence(s) of link_all_deplibs = no in $libtool_m4])
	    libtool_flag_pattern_count=$(grep -c "$libtool_flag_pattern\s*=\s*no" $libtool_m4)
	    AS_IF([test $libtool_flag_pattern_count -ne 0],
	    [
		  AC_MSG_RESULT([$libtool_flag_pattern_count])
		  AC_MSG_WARN([the detected libtool will not link all dependencies, forcing link_all_deplibs = unknown])
		  sed -i "s/\($libtool_flag_pattern\)\s*=\s*no/\1=unknown/g" $libtool_m4
		  ],
		  [
		  AC_MSG_RESULT([none])
		  ])
	    ])

AM_CONDITIONAL([NO_SHARED], [test x$enable_shared = xno])

AC_CHECK_HEADERS([ \
	sys/types.h unistd.h fcntl.h string.h pthread.h limits.h \
	signal.h stdlib.h sys/un.h sys/socket.h stdlib.h stdio.h \
	getopt.h sys/ipc.h sys/shm.h popt.h grp.h \
])

# Babeltrace viewer check
AC_ARG_WITH([babeltrace-bin],
	AS_HELP_STRING([--with-babeltrace-bin],
	[Location of the babeltrace viewer executable (including the filename)]),
	[BABELTRACE_BIN="$withval"],
	[BABELTRACE_BIN=''])
AC_SUBST([BABELTRACE_BIN])

# lttv-gui
AC_ARG_WITH([lttv-gui-bin],
	AS_HELP_STRING([--with-lttv-gui-bin],
   [Location of the lttv GUI viewer executable (including the filename)]),
   [LTTV_GUI_BIN="$withval"],
   [LTTV_GUI_BIN=''])
AC_SUBST([LTTV_GUI_BIN])

AC_ARG_WITH([consumerd32-bin],
	AS_HELP_STRING([--with-consumerd32-bin],
	[Location of the 32-bit consumerd executable (including the filename)]),
	[CONSUMERD32_BIN="$withval"],
	[CONSUMERD32_BIN=''])
AC_SUBST([CONSUMERD32_BIN])

AC_ARG_WITH([consumerd64-bin],
	AS_HELP_STRING([--with-consumerd64-bin],
	[Location of the 64-bit consumerd executable (including the filename)]),
	[CONSUMERD64_BIN="$withval"],
	[CONSUMERD64_BIN=''])
AC_SUBST([CONSUMERD64_BIN])

AC_ARG_WITH([consumerd32-libdir],
	AS_HELP_STRING([--with-consumerd32-libdir],
	[Directory containing the 32-bit consumerd libraries]),
	[CONSUMERD32_LIBDIR="$withval"],
	[CONSUMERD32_LIBDIR=''])
AC_SUBST([CONSUMERD32_LIBDIR])

AC_ARG_WITH([consumerd64-libdir],
	AS_HELP_STRING([--with-consumerd64-libdir],
	[Directory containing the 64-bit consumerd libraries]),
	[CONSUMERD64_LIBDIR="$withval"],
	[CONSUMERD64_LIBDIR=''])
AC_SUBST([CONSUMERD64_LIBDIR])

AC_ARG_WITH([sessiond-bin],
	AS_HELP_STRING([--with-sessiond-bin],
	[Location of the sessiond executable (including the filename)]),
	[SESSIOND_BIN="$withval"],
	[SESSIOND_BIN=''])
AC_SUBST([SESSIOND_BIN])

AC_ARG_WITH([lttng-system-rundir],
	AS_HELP_STRING([--with-lttng-system-rundir],
	[Location of the system directory where the system-wide lttng-sessiond runtime files are kept. The default is "/var/run/lttng".]),
	[LTTNG_SYSTEM_RUNDIR="$withval"],
	[LTTNG_SYSTEM_RUNDIR="/var/run/lttng"])
AC_SUBST([LTTNG_SYSTEM_RUNDIR])

AC_DEFINE_UNQUOTED([CONFIG_CONSUMERD32_BIN], "$CONSUMERD32_BIN", [Location of the 32-bit consumerd executable.])
AC_DEFINE_UNQUOTED([CONFIG_CONSUMERD64_BIN], "$CONSUMERD64_BIN", [Location of the 64-bit consumerd executable])
AC_DEFINE_UNQUOTED([CONFIG_CONSUMERD32_LIBDIR], "$CONSUMERD32_LIBDIR", [Search for consumerd 32-bit libraries in this location.])
AC_DEFINE_UNQUOTED([CONFIG_CONSUMERD64_LIBDIR], "$CONSUMERD64_LIBDIR", [Search for consumerd 64-bit libraries in this location.])
AC_DEFINE_UNQUOTED([CONFIG_BABELTRACE_BIN], "$BABELTRACE_BIN", [Location of the babeltrace viewer executable.])
AC_DEFINE_UNQUOTED([CONFIG_LTTV_GUI_BIN], "$LTTV_GUI_BIN", [Location of the lttv GUI viewer executable.])
AC_DEFINE_UNQUOTED([CONFIG_SESSIOND_BIN], "$SESSIOND_BIN", [Location of the sessiond executable.])
AC_DEFINE_UNQUOTED([CONFIG_LTTNG_SYSTEM_RUNDIR], ["$LTTNG_SYSTEM_RUNDIR"], [LTTng system runtime directory])

# Check for pthread
AC_CHECK_LIB([pthread], [pthread_create], [],
	[AC_MSG_ERROR([Cannot find libpthread. Use [LDFLAGS]=-Ldir to specify its location.])]
)

# Check libpopt
AC_CHECK_LIB([popt], [poptGetContext], [],
	[AC_MSG_ERROR([Cannot find libpopt. Use [LDFLAGS]=-Ldir to specify its location.])]
)

# Check for libuuid
AC_CHECK_LIB([uuid], [uuid_generate],
[
	AC_DEFINE_UNQUOTED([LTTNG_HAVE_LIBUUID], 1, [Has libuuid support.])
	have_libuuid=yes
],
[
	# libuuid not found, check for uuid_create in libc.
	AC_CHECK_LIB([c], [uuid_create],
	[
		AC_DEFINE_UNQUOTED([LTTNG_HAVE_LIBC_UUID], 1, [Has libc uuid support.])
		have_libc_uuid=yes
	],
	[
		AC_MSG_ERROR([Cannot find libuuid uuid_generate nor libc uuid_create. Use [LDFLAGS]=-Ldir to specify their location.])
	])
]
)
AM_CONDITIONAL([LTTNG_BUILD_WITH_LIBUUID], [test "x$have_libuuid" = "xyes"])
AM_CONDITIONAL([LTTNG_BUILD_WITH_LIBC_UUID], [test "x$have_libc_uuid" = "xyes"])

# URCU library version needed or newer
liburcu_version=">= 0.7.2"

# Check liburcu needed function calls
AC_CHECK_DECL([cds_list_add], [],
	[AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu/list.h>]]
)
AC_CHECK_DECL([cds_wfq_init], [],
	[AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu/wfqueue.h>]]
)
AC_CHECK_DECL([cds_wfq_dequeue_blocking], [],
    [AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu/wfqueue.h>]]
)
AC_CHECK_DECL([futex_async], [],
	[AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu/futex.h>]]
)
AC_CHECK_DECL([rcu_thread_offline], [],
	[AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu.h>]]
)
AC_CHECK_DECL([rcu_thread_online], [],
	[AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu.h>]]
)
AC_CHECK_DECL([caa_likely], [],
	[AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu.h>]]
)
#Function added in urcu 0.7.0
AC_CHECK_DECL([cmm_smp_mb__before_uatomic_or], [],
        [AC_MSG_ERROR([liburcu $liburcu_version or newer is needed])], [[#include <urcu.h>]]
)

AC_ARG_WITH(lttng-ust-prefix,
  AS_HELP_STRING([--with-lttng-ust-prefix=PATH],
                 [Specify the installation prefix of the lttng-ust library.
	          Headers must be in PATH/include; libraries in PATH/lib.]),
		  [
		    CPPFLAGS="$CPPFLAGS -I${withval}/include"
		    LDFLAGS="$LDFLAGS -L${withval}/lib64 -L${withval}/lib"
		  ])

# Check liblttng-ust-ctl library
AC_ARG_ENABLE(lttng-ust,
	AS_HELP_STRING([--disable-lttng-ust],[build without LTTng-UST (Userspace Tracing) support]),
	lttng_ust_support=$enableval, lttng_ust_support=yes)

AS_IF([test "x$lttng_ust_support" = "xyes"], [
	AC_CHECK_LIB([lttng-ust-ctl], [ustctl_recv_channel_from_consumer],
		[
			AC_DEFINE([HAVE_LIBLTTNG_UST_CTL], [1], [has LTTng-UST control support])
			lttng_ust_ctl_found=yes
		],
		[AC_MSG_ERROR([Cannot find LTTng-UST >= 2.2.x. Use --with-lttng-ust-prefix=PREFIX to specify its location, or specify --disable-lttng-ust to build lttng-tools without LTTng-UST support.])],
		[-lurcu-common -lurcu-bp -lurcu-cds -lrt]
	)
])
AM_CONDITIONAL([HAVE_LIBLTTNG_UST_CTL], [test "x$lttng_ust_ctl_found" = xyes])
AC_CHECK_FUNCS([sched_getcpu sysconf sync_file_range])

# check for dlopen
AC_CHECK_LIB([dl], [dlopen],
[
	have_libdl=yes
],
[
	#libdl not found, check for dlopen in libc.
	AC_CHECK_LIB([c], [dlopen],
	[
		have_libc_dl=yes
	],
	[
		AC_MSG_ERROR([Cannot find dlopen in libdl nor libc. Use [LDFLAGS]=-Ldir to specify their location.])
	])
])
AM_CONDITIONAL([LTTNG_TOOLS_BUILD_WITH_LIBDL], [test "x$have_libdl" = "xyes"])
AM_CONDITIONAL([LTTNG_TOOLS_BUILD_WITH_LIBC_DL], [test "x$have_libc_dl" = "xyes"])

# Check for fmemopen
AC_CHECK_LIB([c], [fmemopen],
[
	AC_DEFINE_UNQUOTED([LTTNG_HAVE_FMEMOPEN], 1, [Has fmemopen support.])
]
)

# Check for open_memstream
AC_CHECK_LIB([c], [open_memstream],
[
	AC_DEFINE_UNQUOTED([LTTNG_HAVE_OPEN_MEMSTREAM], 1, [Has open_memstream support.])
]
)

# For Python
# SWIG version needed or newer:
swig_version=2.0.0

AC_ARG_ENABLE([python-bindings],
              [AC_HELP_STRING([--enable-python-bindings],
                              [compile Python bindings])],
              [enable_python=yes], [enable_python=no])

AM_CONDITIONAL([USE_PYTHON], [test "x${enable_python:-yes}" = xyes])

if test "x${enable_python:-yes}" = xyes; then
  AX_PKG_SWIG($swig_version, [], [ AC_MSG_ERROR([SWIG $swig_version or newer is needed]) ])
  AM_PATH_PYTHON

  AC_ARG_VAR([PYTHON_INCLUDE], [Include flags for python, bypassing python-config])
  AC_ARG_VAR([PYTHON_CONFIG], [Path to python-config])
  AS_IF([test -z "$PYTHON_INCLUDE"], [
    AS_IF([test -z "$PYTHON_CONFIG"], [
      AC_PATH_PROGS([PYTHON_CONFIG],
                    [python$PYTHON_VERSION-config python-config],
                    [no],
                    [`dirname $PYTHON`])
      AS_IF([test "$PYTHON_CONFIG" = no], [AC_MSG_ERROR([cannot find python-config for $PYTHON. Do you have python-dev installed?])])
    ])
    AC_MSG_CHECKING([python include flags])
    PYTHON_INCLUDE=`$PYTHON_CONFIG --includes`
    AC_MSG_RESULT([$PYTHON_INCLUDE])
  ])

else
    AC_MSG_NOTICE([You may configure with --enable-python-bindings ]dnl
[if you want Python bindings.])

fi

# Option to only build the consumer daemon and its libraries
AC_ARG_WITH([consumerd-only],
	AS_HELP_STRING([--with-consumerd-only],[Only build the consumer daemon [default=no]]),
	[consumerd_only=$withval],
	[consumerd_only=no])
AM_CONDITIONAL([BUILD_CONSUMERD_ONLY], [test "x$consumerd_only" = "xyes"])

# Epoll check. If not present, the build will fallback on poll() API
AX_HAVE_EPOLL(
	[AX_CONFIG_FEATURE_ENABLE(epoll)],
	[AX_CONFIG_FEATURE_DISABLE(epoll)]
)
AX_CONFIG_FEATURE(
	[epoll], [This platform supports epoll(7)],
	[HAVE_EPOLL], [This platform supports epoll(7).],
	[enable_epoll="yes"], [enable_epoll="no"]
)
AM_CONDITIONAL([COMPAT_EPOLL], [ test "$enable_epoll" = "yes" ])

AC_SYS_LARGEFILE
AC_PROG_CC
LT_INIT
AC_PROG_YACC
AC_PROG_LEX

if test ! -f "$srcdir/src/lib/lttng-ctl/filter/filter-parser.h"; then
	if test x"$YACC" != "xbison -y"; then
		AC_MSG_ERROR([[bison not found and is required when building from git.
		Please install bison]])
	fi
fi

if test ! -f "$srcdir/src/lib/lttng-ctl/filter/filter-lexer.c"; then
	if test x"$LEX" != "xflex"; then
		AC_MSG_ERROR([[flex not found and is required when building from git.
		Please install flex]])
	fi
fi

CFLAGS="-Wall $CFLAGS -g -fno-strict-aliasing"

DEFAULT_INCLUDES="-I\$(top_srcdir) -I\$(top_builddir) -I\$(top_builddir)/src -I\$(top_builddir)/include -include config.h"

lttngincludedir="${includedir}/lttng"

AC_SUBST(lttngincludedir)
AC_SUBST(DEFAULT_INCLUDES)

lttnglibexecdir="${libdir}/lttng/libexec"
AC_SUBST(lttnglibexecdir)

AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	doc/man/Makefile
	include/Makefile
	extras/Makefile
	extras/bindings/Makefile
	extras/bindings/swig/Makefile
	extras/bindings/swig/python/Makefile
	extras/core-handler/Makefile
	src/Makefile
	src/common/Makefile
	src/common/kernel-ctl/Makefile
	src/common/kernel-consumer/Makefile
	src/common/ust-consumer/Makefile
	src/common/hashtable/Makefile
	src/common/sessiond-comm/Makefile
	src/common/compat/Makefile
	src/common/relayd/Makefile
	src/common/testpoint/Makefile
	src/common/index/Makefile
	src/common/health/Makefile
	src/lib/Makefile
	src/lib/lttng-ctl/Makefile
	src/lib/lttng-ctl/filter/Makefile
	src/lib/lttng-ctl/lttng-ctl.pc
	src/bin/Makefile
	src/bin/lttng-consumerd/Makefile
	src/bin/lttng-sessiond/Makefile
	src/bin/lttng-relayd/Makefile
	src/bin/lttng/Makefile
	tests/Makefile
	tests/regression/Makefile
	tests/regression/kernel/Makefile
	tests/regression/tools/Makefile
	tests/regression/tools/streaming/Makefile
	tests/regression/tools/filtering/Makefile
	tests/regression/tools/health/Makefile
	tests/regression/tools/tracefile-limits/Makefile
	tests/regression/tools/snapshots/Makefile
	tests/regression/tools/live/Makefile
	tests/regression/ust/Makefile
	tests/regression/ust/nprocesses/Makefile
	tests/regression/ust/high-throughput/Makefile
	tests/regression/ust/low-throughput/Makefile
	tests/regression/ust/before-after/Makefile
	tests/regression/ust/buffers-pid/Makefile
	tests/regression/ust/periodical-metadata-flush/Makefile
	tests/regression/ust/multi-session/Makefile
	tests/regression/ust/overlap/Makefile
	tests/regression/ust/overlap/demo/Makefile
	tests/regression/ust/linking/Makefile
	tests/regression/ust/daemon/Makefile
	tests/regression/ust/exit-fast/Makefile
	tests/regression/ust/fork/Makefile
	tests/regression/ust/libc-wrapper/Makefile
	tests/stress/Makefile
	tests/unit/Makefile
	tests/utils/Makefile
	tests/utils/tap/Makefile
	tests/utils/testapp/Makefile
	tests/utils/testapp/gen-ust-events/Makefile
	tests/utils/testapp/gen-ust-nevents/Makefile
])

AC_OUTPUT

#
# Mini-report on what will be built
#
AS_ECHO()

AS_ECHO("Version name: $version_name")
AS_ECHO("$version_description")

AS_ECHO()

# Target architecture we're building for
target_arch=$host_cpu
[
for f in $CFLAGS; do
        if test $f = "-m32"; then
			target_arch="32-bit"
        elif test $f = "-m64"; then
			target_arch="64-bit"
        fi
done
]
AS_ECHO_N("Target architecture: ")
AS_ECHO($target_arch)

# LTTng-UST enabled/disabled
AS_ECHO_N("Lttng-UST support: ")
AS_IF([test "x$lttng_ust_support" = "xyes"],[
	AS_ECHO("Enabled")
],[
	AS_ECHO("Disabled")
])

#Python binding enabled/disabled
AS_ECHO_N("Python binding: ")
AS_IF([test "x${enable_python:-yes}" = xyes], [
	AS_ECHO("Enabled")
],[
	AS_ECHO("Disabled")
])

# Do we build only the consumerd, or everything
AS_IF([test "x$consumerd_only" = "xyes"],[
	AS_ECHO("Only the consumerd daemon will be built.")
],[
	AS_ECHO("All binaries will be built.")
])

# Print the bindir and libdir this `make install' will install into.
AS_ECHO()
AS_ECHO_N("Binaries will be installed in:  ")
AS_ECHO("`eval eval echo $bindir`")
AS_ECHO_N("Libraries will be installed in: ")
AS_ECHO("`eval eval echo $libdir`")

# If we build the sessiond, print the paths it will use
AS_IF([test "x$consumerd_only" = "xno"],[
	AS_ECHO()
	AS_ECHO_N("The lttng command will look for the lttng-sessiond executable at: ")
	AS_IF([test "$SESSIOND_BIN" = ""],[
		AS_ECHO_N("`eval eval echo $bindir`")
		AS_ECHO("/lttng-sessiond")
	],[
		AS_ECHO("$SESSIOND_BIN")
	])

	AS_ECHO()
	AS_ECHO("The sessiond daemon will look in the following directories: ")
	AS_ECHO_N("32-bit consumerd executable at: ")
	AS_IF([test "$CONSUMERD32_BIN" = ""],[
		AS_ECHO_N("`eval eval echo $lttnglibexecdir`")
		AS_ECHO("/lttng-consumerd")
	],[
		AS_ECHO("$CONSUMERD32_BIN")
	])

	AS_ECHO_N("32-bit consumer libraries in:   ")
	AS_IF([test "$CONSUMERD32_LIBDIR" = ""],[
		AS_ECHO("`eval eval echo $libdir`")
	],[
		AS_ECHO("$CONSUMERD32_LIBDIR")
	])

	AS_ECHO_N("64-bit consumerd executable at: ")
	AS_IF([test "$CONSUMERD64_BIN" = ""],[
		AS_ECHO_N("`eval eval echo $lttnglibexecdir`")
		AS_ECHO("/lttng-consumerd")
	],[
		AS_ECHO("$CONSUMERD64_BIN")
	])

	AS_ECHO_N("64-bit consumer libraries in:   ")
	AS_IF([test "$CONSUMERD64_LIBDIR" = ""],[
		AS_ECHO("`eval eval echo $libdir`")
	],[
		AS_ECHO("$CONSUMERD64_LIBDIR")
	])
])

AS_ECHO()

