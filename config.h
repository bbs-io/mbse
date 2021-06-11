/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  */
/* $Id: config.h.in,v 1.49 2007/08/25 21:01:03 mbse Exp $ */

#define SHORTRIGHT "Copyright (C) 1997-2021 MBSE DevTm"
#define COPYRIGHT "Copyright (C) 1997-2021 MBSE Development Team, All Rights Reserved"
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_REVISION 7.22
#define VERSION "1.0.7.22"

/* According to Sun we MUST define this in the source */
#define _REENTRANT 1

/* Compile experimental code (may not be present) */
/* #undef USE_EXPERIMENT */

/* Compile full newsgate */
/* #undef USE_NEWSGATE */

/* Has strcasestr function  */
#define HAVE_STRCASESTR 1

/* If you have gettimeofday function  */
/* #undef HAVE_DECLARED_TIMEZONE */
/* #undef HAVE_TM_GMTOFF */

/* From unix: */
#define SHADOW_PASSWORD 1
/* #undef AGING */
/* #undef ATT_AGE */
/* #undef ATT_COMMENT */
/* #undef AUTH_METHODS */
/* #undef CKDEFS */
/* #undef DOUBLESIZE */

/* Defined if you have libcrack.  */
/* #undef HAVE_LIBCRACK */

/* Defined if you have the ts&szs cracklib.  */
/* #undef HAVE_LIBCRACK_HIST */

/* Defined if it includes *Pw functions.  */
/* #undef HAVE_LIBCRACK_PW */

/* Defined if you have libutil.h */
/* #undef HAVE_LIBUTIL_H */

/* Defined if you have util.h */
/* #undef HAVE_UTIL_H */

/* Defined if you have sys/types.h */
#define HAVE_SYS_TYPES_H 1

/* Defined if it includes *Pw functions.  */
/* #undef HAVE_LIBCRACK_PW */

/* #undef KEEP_NIS_AT_END */

/* Define to support the MD5-based password hashing algorithm.  */
/* #undef MD5_CRYPT */
/* #undef PAM */

/* Define to support OPIE one-time password logins.  */
/* #undef OPIE */
/* #undef SW_CRYPT */

/* Define to 1 if NLS is requested.  */
/* #undef ENABLE_NLS */

/* Path for lastlog file.  */
#define LASTLOG_FILE "/var/log/lastlog"

/* Define to support /etc/login.access login access control.  */
/* #undef LOGIN_ACCESS */

/* Path to vpopmail.  */
/* #undef _VPOPMAIL_PATH */

/* Path for wtmp file.  */
#define _WTMP_FILE "/var/log/wtmp"

/* Define if you have the updwtmp function.  */
#define HAVE_UPDWTMP 1

/* Define if you have the updwtmpx function.  */
#define HAVE_UPDWTMPX 1

/* Define if you have the <lastlog.h> header file.  */
#define HAVE_LASTLOG_H 1

/* Define if you have the initgroups function.  */
#define HAVE_INITGROUPS 1

/* Define if you have ut_host in struct utmp.  */
/* #undef UT_HOST */

/* Path for utmp file.  */
#define _UTMP_FILE "/var/run/utmp"

/* Define if you have the `a64l' function. */
#define HAVE_A64L 1

/* Define if you have the `c64i' function. */
/* #undef HAVE_C64I */

/* Define if you have the <dirent.h> header file, and it defines `DIR'. */
#define HAVE_DIRENT_H 1

/* Define if you have the `fchmod' function. */
#define HAVE_FCHMOD 1

/* Define if you have the `fchown' function. */
#define HAVE_FCHOWN 1

/* Define if you have the `fdatasync' function. */
#define HAVE_FDATASYNC 1

/* Define if you have the `fsync' function. */
#define HAVE_FSYNC 1

/* Define if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the <gshadow.h> header file. */
#define HAVE_GSHADOW_H 1

/* Define if you have the `lckpwdf' function. */
#define HAVE_LCKPWDF 1

/* Define if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define if you have the `putpwent' function. */
#define HAVE_PUTPWENT 1

/* Define if you have the putspent function.  */
/* #undef HAVE_PUTSPENT */

/* Define if you have the putgrent function.  */
/* #undef HAVE_PUTGRENT */

/* Define if you have the <shadow.h> header file. */
#define HAVE_SHADOW_H 1

/* Define if `tm_zone' is member of `struct tm'. */
#define HAVE_STRUCT_TM_TM_ZONE 1

/* Define if you have the <sys/dir.h> header file, and it defines `DIR'. */
/* #undef HAVE_SYS_DIR_H */

/* Define if you have the <sys/ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_SYS_NDIR_H */

/* Define if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/vfs.h> header file. */
#define HAVE_SYS_VFS_H 1

/* Define if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define if you have the <sys/termio.h> header file.  */
/* #undef HAVE_SYS_TERMIO_H */

/* Define if you have the <sys/termios.h> header file.  */
#define HAVE_SYS_TERMIOS_H 1

/* Define if you have the <termios.h> header file.  */
#define HAVE_TERMIO_H 1

/* Define if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if you have the <usersec.h> header file. */
/* #undef HAVE_USERSEC_H */

/* Define if you have the <sgtty.h> header file.  */
#define HAVE_SGTTY_H 1

/* Define if you have the <utmp.h> header file.  */
#define HAVE_UTMP_H 1

/* Define if you have the <utmpx.h> header file.  */
#define HAVE_UTMPX_H 1

/* Define if you have the memcpy function.  */
/* #undef HAVE_MEMCPY */

/* Define if you have the memset function.  */
/* #undef HAVE_MEMSET */

/* Name of package */
/* #undef PACKAGE */

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define if you have the statfs function */
#define HAVE_STATFS 1

/* Define if you have the statvfs function */
#define HAVE_STATVFS 1

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define if `lex' declares `yytext' as a `char *' by default, not a `char[]'.  */
/* #undef YYTEXT_POINTER */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `long' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef ssize_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */

/* Define if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define if you have the <bzlib.h> header file. */
#define HAVE_BZLIB_H 1

/* Define if machine is bigendian */
/* #undef WORDS_BIGENDIAN */

/* Define if Del != 207 */
#define GBK_DEL 0

/* Define if you have the <crypt.h> header file. */
#define HAVE_CRYPT_H 1

/* Define if you have the <iconv.h> header file. */
#define HAVE_ICONV_H 1

/* Define if you have the <GeoIP.h> header file. */
#define HAVE_GEOIP_H 1

