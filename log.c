/* log.c
 *
 * Copyright (C) 2024 Ray Lee
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "log.h"

int loglevel = LOGLEVEL_WARNING;

void log_init(int level)
{
    if (level > 0 && level < LOGLEVEL_MAX)
        loglevel = level;
}

static void report(const char *prefix, const char *err, va_list params)
{
    char msg[1024];
    vsnprintf(msg, sizeof(msg), err, params);
    fprintf(stderr, "%s%s\n", prefix, msg);
}

static void debug_builtin(const char *debug, va_list params)
{
    report("[Debug] ", debug, params);
}

static void info_builtin(const char *info, va_list params)
{
    report("[Info] ", info, params);
}

static void warn_builtin(const char *warn, va_list params)
{
    report("[Warning] ", warn, params);
}

static void error_builtin(const char *err, va_list params)
{
    report("[Error] ", err, params);
}

static void die_builtin(const char *err, va_list params)
{
    report("[Fatal] ", err, params);
    exit(128);
}

void __pr_debug(const char *debug, ...)
{
    va_list params;

    if (loglevel < LOGLEVEL_DEBUG)
        return;

    va_start(params, debug);
    debug_builtin(debug, params);
    va_end(params);
}

void pr_info(const char *info, ...)
{
    va_list params;

    if (loglevel < LOGLEVEL_INFO)
        return;

    va_start(params, info);
    info_builtin(info, params);
    va_end(params);
}

void pr_warning(const char *warn, ...)
{
    va_list params;

    if (loglevel < LOGLEVEL_WARNING)
        return;

    va_start(params, warn);
    warn_builtin(warn, params);
    va_end(params);
}

void pr_err(const char *err, ...)
{
    va_list params;

    if (loglevel < LOGLEVEL_ERROR)
        return;

    va_start(params, err);
    error_builtin(err, params);
    va_end(params);
}

void die(const char *err, ...)
{
    va_list params;

    va_start(params, err);
    die_builtin(err, params);
    va_end(params);
}
