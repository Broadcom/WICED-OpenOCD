/***************************************************************************
 *   Copyright (C) 2015 by Evan Hunter                                     *
 *   ehunter@broadcom.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program;                                              *
 ***************************************************************************/

#ifndef MINGW_COMPAT_H
#define MINGW_COMPAT_H


/* Only needed for MinGW32  */
#ifndef __MINGW64__

#pragma GCC system_header

/* This file makes MinGW use C99 compatible definitions for STDIO functions */


#ifdef __USE_MINGW_ANSI_STDIO



/* These definition of these functions cause MinGW GCC to parse
 * the format string using MSVCRT format specifiers
 * So rename the definitions.
 */
#define fprintf(...)   alternate_fprintf(__VA_ARGS__)
#define printf(...)    alternate_printf(__VA_ARGS__)
#define sprintf(...)   alternate_sprintf(__VA_ARGS__)
#define snprintf(...)  alternate_snprintf(__VA_ARGS__)

#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>


/* If using standard MinGW (i.e. not MinGW-w64 32-bit ) */
#ifndef __MINGW64_VERSION_MAJOR

/* Now remove the macros - junking the names */
#undef fprintf
#undef printf
#undef sprintf
#undef snprintf

/* Now declare the functions using the attribute with "gnu_printf" to force GNU format specifier parsing */
static inline int fprintf(FILE * __stream, const char *__format, ...)  __attribute__ ((format (gnu_printf, 2, 3)));
static inline int printf(const char *__format, ...)                   __attribute__ ((format (gnu_printf, 1, 2)));
static inline int sprintf(char *__stream, const char *__format, ...)  __attribute__ ((format (gnu_printf, 2, 3)));
static inline int snprintf(char *__stream, size_t size, const char *__format, ...)
																	__attribute__ ((format (gnu_printf, 3, 4)));

/* Finally - Make definitions of the functions */

static inline int fprintf(FILE *__stream, const char *__format, ...)
{
	register int __retval;
	__builtin_va_list __local_argv; __builtin_va_start(__local_argv, __format);
	__retval = __mingw_vfprintf(__stream, __format, __local_argv);
	__builtin_va_end(__local_argv);
	return __retval;
}

static inline int printf(const char *__format, ...)
{
	register int __retval;
	__builtin_va_list __local_argv; __builtin_va_start(__local_argv, __format);
	__retval = __mingw_vprintf(__format, __local_argv);
	__builtin_va_end(__local_argv);
	return __retval;
}

static inline int sprintf(char *__stream, const char *__format, ...)
{
	register int __retval;
	__builtin_va_list __local_argv; __builtin_va_start(__local_argv, __format);
	__retval = __mingw_vsprintf(__stream, __format, __local_argv);
	__builtin_va_end(__local_argv);
	return __retval;
}

static inline int snprintf(char *__stream, size_t size, const char *__format, ...)
{
	register int __retval;
	__builtin_va_list __local_argv; __builtin_va_start(__local_argv, __format);
	__retval = __mingw_vsnprintf(__stream, size, __format, __local_argv);
	__builtin_va_end(__local_argv);
	return __retval;
}

/* MinGW implementation of these is broken when __USE_MINGW_ANSI_STDIO is defined */
#undef  PRIx64
#undef  PRId64
#undef  PRIi64
#undef  PRIu64
#define PRIx64 "llx"
#define PRId64 "lld"
#define PRIi64 "lli"
#define PRIu64 "llu"

#endif /* ifndef __MINGW64_VERSION_MAJOR */

#endif /* ifdef __USE_MINGW_ANSI_STDIO */

#endif /* ifndef __MINGW64__ */



/* To achieve C99 printf compatibility in MinGW, gnu_printf should be
 * used for __attribute__((format( ... ))), with GCC v4.4 or later
 */
#if (((__GNUC__ << 16) + __GNUC_MINOR__) >= 0x00040004)

#define PRINTF_ATTRIBUTE_FORMAT gnu_printf
#endif

#endif	/* MINGW_COMPAT_H */
