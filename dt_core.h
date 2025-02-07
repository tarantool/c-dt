/*
 * Copyright (c) 2012-2015 Christian Hansen <chansen@cpan.org>
 * <https://github.com/chansen/c-dt>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __DT_CORE_H__
#define __DT_CORE_H__
#include "dt_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DT_MON       = 1,
    DT_MONDAY    = 1,
    DT_TUE       = 2,
    DT_TUESDAY   = 2,
    DT_WED       = 3,
    DT_WEDNESDAY = 3,
    DT_THU       = 4,
    DT_THURSDAY  = 4,
    DT_FRI       = 5,
    DT_FRIDAY    = 5,
    DT_SAT       = 6,
    DT_SATURDAY  = 6,
    DT_SUN       = 7,
    DT_SUNDAY    = 7,
} dt_dow_t;

dt_t     dt_from_rdn     (int n);
dt_t     dt_from_yd      (int y, int d);
dt_t     dt_from_ymd     (int y, int m, int d);
dt_t     dt_from_yqd     (int y, int q, int d);
dt_t     dt_from_ywd     (int y, int w, int d);

void     dt_to_yd        (dt_t dt, int *y, int *d);
void     dt_to_ymd       (dt_t dt, int *y, int *m, int *d);
void     dt_to_yqd       (dt_t dt, int *y, int *q, int *d);
void     dt_to_ywd       (dt_t dt, int *y, int *w, int *d);

#ifdef DT_PARSE_ISO_TNT
bool     dt_from_yd_checked (int y, int d, dt_t *val);
bool     dt_from_ymd_checked(int y, int m, int d, dt_t *val);
bool     dt_from_yqd_checked(int y, int q, int d, dt_t *val);
bool     dt_from_ywd_checked(int y, int w, int d, dt_t *val);
#endif

int      dt_rdn          (dt_t dt);
dt_dow_t dt_dow          (dt_t dt);

#ifdef __cplusplus
}
#endif
#endif

