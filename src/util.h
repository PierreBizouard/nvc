//
//  Copyright (C) 2011-2016  Nick Gasson
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _UTIL_H
#define _UTIL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "prim.h"

#ifdef HAVE_FUNC_ATTRIBUTE_RETURNS_NONNULL
#define RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#define RETURNS_NONNULL
#endif

#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000       \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#else
#define GCC_VERSION 0
#endif

#if GCC_VERSION > 40600
#define STATIC_ASSERT(x) _Static_assert((x), "Static assertion failed");
#else
#define STATIC_ASSERT(x)
#endif

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

void *xmalloc(size_t size) RETURNS_NONNULL;
void *xcalloc(size_t size) RETURNS_NONNULL;
void *xrealloc(void *ptr, size_t size) RETURNS_NONNULL;
char *xstrdup(const char *str) RETURNS_NONNULL;

char *xvasprintf(const char *fmt, va_list ap) RETURNS_NONNULL;
char *xasprintf(const char *fmt, ...)
   __attribute__((format(printf, 1, 2))) RETURNS_NONNULL;

int color_printf(const char *fmt, ...)
   __attribute__((format(printf, 1, 2)));

void errorf(const char *fmt, ...)
   __attribute__((format(printf, 1, 2)));
void warnf(const char *fmt, ...)
   __attribute__((format(printf, 1, 2)));
void notef(const char *fmt, ...)
   __attribute__((format(printf, 1, 2)));
void fatal(const char *fmt, ...)
   __attribute__((format(printf, 1, 2), noreturn));
void fatal_trace(const char *fmt, ...)
   __attribute__((format(printf, 1, 2), noreturn));
void fatal_errno(const char *fmt, ...)
   __attribute__((format(printf, 1, 2), noreturn));

#define likely(x) __builtin_expect(x, 1)
#define unlikely(x) __builtin_expect(x, 0)

// Error callback for use in unit tests.
typedef void (*error_fn_t)(const char *msg, const loc_t *loc);
error_fn_t set_error_fn(error_fn_t fn, bool want_color);

typedef void (*fatal_fn_t)(void);
void set_fatal_fn(fatal_fn_t fn);

void error_at(const loc_t *loc, const char *fmt, ...)
   __attribute__((format(printf, 2, 3)));
void warn_at(const loc_t *loc, const char *fmt, ...)
   __attribute__((format(printf, 2, 3)));
void note_at(const loc_t *loc, const char *fmt, ...)
   __attribute__((format(printf, 2, 3)));
void fatal_at(const loc_t *loc, const char *fmt, ...)
   __attribute__((format(printf, 2, 3), noreturn));
void error_at_v(const loc_t *loc, const char *fmt, va_list ap);

void fmt_loc(FILE *f, const loc_t *loc);

void show_stacktrace(void);
void register_trace_signal_handlers(void);
void register_gdb_signal_handlers(void);
bool is_debugger_running(void);

void term_init(void);

void opt_set_int(const char *name, int val);
void opt_set_str(const char *name, const char *val);
int opt_get_int(const char *name);
const char *opt_get_str(const char *name);

char *get_fmt_buf(size_t len);

int checked_sprintf(char *buf, int len, const char *fmt, ...)
   __attribute__((format(printf, 3, 4)));

int next_power_of_2(int n) __attribute__((pure));
int ilog2(int64_t n) __attribute__((pure));
int64_t ipow(int64_t x, int64_t y)  __attribute__((pure));

void *mmap_guarded(size_t sz, const char *tag);

typedef struct text_buf text_buf_t;

#define LOCAL_TEXT_BUF __attribute__((cleanup(_tb_cleanup))) text_buf_t *

text_buf_t *tb_new(void);
void tb_free(text_buf_t *tb);
void _tb_cleanup(text_buf_t **tb);
void tb_printf(text_buf_t *tb, const char *fmt, ...)
   __attribute__((format(printf, 2, 3)));
void tb_append(text_buf_t *tb, char ch);
const char *tb_get(text_buf_t *tb);
char *tb_claim(text_buf_t *tb);
void tb_rewind(text_buf_t *tb);

#define LOCAL __attribute__((cleanup(_local_free)))

void _local_free(void *ptr);

#define ARRAY_APPEND(array, item, count, max) do {      \
      if (unlikely(count == max)) {                     \
         max *= 2;                                      \
         array = xrealloc(array, max * sizeof(*array)); \
      }                                                 \
      array[count++] = item;                            \
   } while(0);

typedef enum {
   MESSAGE_FULL,
   MESSAGE_COMPACT
} message_style_t;

void set_message_style(message_style_t style);

typedef struct {
   unsigned rss;
   unsigned ms;
} nvc_rusage_t;

void nvc_rusage(nvc_rusage_t *ru);

#endif // _UTIL_H
