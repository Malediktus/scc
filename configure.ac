AC_INIT([scc], [1.0])
AC_PREREQ([2.71])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([foreign dist-xz 1.16])

AC_PROG_CC
AC_MSG_CHECKING(checking for getopt.h... )
AC_CHECK_HEADERS([getopt.h], [], [AC_MSG_ERROR(getopt.h was not found, [1])])
AC_MSG_CHECKING(checking for getopt_long... )
AC_CHECK_FUNC(getopt_long, [], [AC_MSG_ERROR(getopt_long was not found, [exit-status = 1])])

AC_OUTPUT