/*
 * Copyright 2021, Tarantool AUTHORS, please see AUTHORS file.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __DT_RENAME_H__
#define __DT_RENAME_H__

#ifdef DT_NAMESPACE
#  define DT_CONCAT(A,B) A##B
#  define DT_NAME(A,B) DT_CONCAT(A,B)
#  define dt_from_rdn DT_NAME(DT_NAMESPACE, dt_from_rdn)
#  define dt_dow DT_NAME(DT_NAMESPACE, dt_dow)
#  define dt_from_rdn DT_NAME(DT_NAMESPACE, dt_from_rdn)
#  define dt_from_struct_tm DT_NAME(DT_NAMESPACE, dt_from_struct_tm)
#  define dt_from_yd DT_NAME(DT_NAMESPACE, dt_from_yd)
#  define dt_from_ymd DT_NAME(DT_NAMESPACE, dt_from_ymd)
#  define dt_from_yqd DT_NAME(DT_NAMESPACE, dt_from_yqd)
#  define dt_from_ywd DT_NAME(DT_NAMESPACE, dt_from_ywd)
#  define dt_parse_iso_date DT_NAME(DT_NAMESPACE, dt_parse_iso_date)
#  define dt_parse_iso_time_basic DT_NAME(DT_NAMESPACE, dt_parse_iso_time_basic)
#  define dt_parse_iso_time_extended DT_NAME(DT_NAMESPACE, dt_parse_iso_time_extended)
#  define dt_parse_iso_time DT_NAME(DT_NAMESPACE, dt_parse_iso_time)
#  define dt_parse_iso_zone_basic DT_NAME(DT_NAMESPACE, dt_parse_iso_zone_basic)
#  define dt_parse_iso_zone_extended DT_NAME(DT_NAMESPACE, dt_parse_iso_zone_extended)
#  define dt_parse_iso_zone_lenient DT_NAME(DT_NAMESPACE, dt_parse_iso_zone_lenient)
#  define dt_parse_iso_zone DT_NAME(DT_NAMESPACE, dt_parse_iso_zone)
#  define dt_rdn DT_NAME(DT_NAMESPACE, dt_rdn)
#  define dt_to_struct_tm DT_NAME(DT_NAMESPACE, dt_to_struct_tm)
#  define dt_to_yd DT_NAME(DT_NAMESPACE, dt_to_yd)
#  define dt_to_ymd DT_NAME(DT_NAMESPACE, dt_to_ymd)
#  define dt_to_yqd DT_NAME(DT_NAMESPACE, dt_to_yqd)
#  define dt_to_ywd DT_NAME(DT_NAMESPACE, dt_to_ywd)
#  define dt_add_years DT_NAME(DT_NAMESPACE, dt_add_years)
#  define dt_add_quarters DT_NAME(DT_NAMESPACE, dt_add_quarters)
#  define dt_add_months DT_NAME(DT_NAMESPACE, dt_add_months)
#endif // DT_NAMESPACE

#endif // __DT_RENAME_H__
