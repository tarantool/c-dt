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
#include <stddef.h>
#include "dt_core.h"
#include "dt_valid.h"

static size_t
count_digits(const unsigned char * const p, size_t i, const size_t len) {
    const size_t n = i;

    for(; i < len; i++) {
        const unsigned char c = p[i] - '0';
        if (c > 9)
            break;
    }
    return i - n;
}

static int
parse_number(const unsigned char * const p, size_t i, const size_t len) {
    int v = 0;

    switch (len) {
        case 9: v += (p[i++] - '0') * 100000000;
        case 8: v += (p[i++] - '0') * 10000000;
        case 7: v += (p[i++] - '0') * 1000000;
        case 6: v += (p[i++] - '0') * 100000;
        case 5: v += (p[i++] - '0') * 10000;
        case 4: v += (p[i++] - '0') * 1000;
        case 3: v += (p[i++] - '0') * 100;
        case 2: v += (p[i++] - '0') * 10;
        case 1: v += (p[i++] - '0');
    }
    return v;
}

static const int pow_10[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
};

/*
 *  fffffffff
 */

static size_t
parse_fraction_digits(const unsigned char *p, size_t i, size_t len, int *fp) {
    size_t n, ndigits;

    ndigits = n = count_digits(p, i, len);
    if (ndigits < 1)
        return 0;
    if (ndigits > 9)
        ndigits = 9;
    if (fp)
        *fp = parse_number(p, i, ndigits) * pow_10[9 - ndigits];
    return n;
}

/*
 *  hh
 *  hhmm
 *  hhmmss
 *  hhmmss.fffffffff
 *  hhmmss,fffffffff
 */

size_t
dt_parse_iso_time_basic(const char *str, size_t len, int *sp, int *fp) {
    const unsigned char *p;
    int h, m, s, f;
    size_t n;

    p = (const unsigned char *)str;
    n = count_digits(p, 0, len);
    m = s = f = 0;
    switch (n) {
        case 2: /* hh */
            h = parse_number(p, 0, 2);
            goto hms;
        case 4: /* hhmm */
            h = parse_number(p, 0, 2);
            m = parse_number(p, 2, 2);
            goto hms;
        case 6: /* hhmmss */
            h = parse_number(p, 0, 2);
            m = parse_number(p, 2, 2);
            s = parse_number(p, 4, 2);
            break;
        default:
            return 0;
    }

    /* hhmmss.fffffffff */
    if (n < len && (p[n] == '.' || p[n] == ',')) {
        size_t r = parse_fraction_digits(p, ++n, len, &f);
        if (!r)
            return 0;
        n += r;
    }

  hms:
    if (h > 23 || m > 59 || s > 59) {
        if (!(h == 24 && m == 0 && s == 0 && f == 0))
            return 0;
    }

    if (sp)
        *sp = h * 3600 + m * 60 + s;
    if (fp)
        *fp = f;
    return n;
}

/*
 *  Z
 *  ±hh
 *  ±hhmm
 */

size_t
dt_parse_iso_zone_basic(const char *str, size_t len, int *op) {
    const unsigned char *p;
    int o, h, m, sign;
    size_t n;

    if (len < 1)
        return 0;

    p = (const unsigned char *)str;
    switch (*p) {
        case 'Z':
            o = 0;
            n = 1;
            goto zulu;
        case '+':
            sign = 1;
            break;
        case '-':
            sign = -1;
            break;
        default:
            return 0;
    }

    if (len < 3)
        return 0;

    n = count_digits(p, 1, len);
    m = 0;
    switch (n) {
        case 2: /* ±hh */
            h = parse_number(p, 1, 2);
            n = 3;
            break;
        case 4: /* ±hhmm */
            h = parse_number(p, 1, 2);
            m = parse_number(p, 3, 2);
            n = 5;
            break;
        default:
            return 0;
    }

    if (h > 23 || m > 59)
        return 0;
    o = sign * (h * 60 + m);
#ifdef DT_PARSE_ISO_STRICT
    if (o == 0 && sign < 0)
        return 0;
#endif

 zulu:
    if (op)
        *op = o;
    return n;
}

/*
 *  hh
 *  hh:mm
 *  hh:mm:ss
 *  hh:mm:ss.fffffffff
 *  hh:mm:ss,fffffffff
 */

size_t
dt_parse_iso_time_extended(const char *str, size_t len, int *sp, int *fp) {
    const unsigned char *p;
    int h, m, s, f;
    size_t n;

    p = (const unsigned char *)str;
    if (count_digits(p, 0, len) != 2)
        return 0;

    h = parse_number(p, 0, 2);
    m = s = f = 0;
    n = 2;
    
    if (len < 3 || p[2] != ':')
        goto hms;

    if (count_digits(p, 3, len) != 2)
        return 0;

    m = parse_number(p, 3, 2);
    n = 5;

    if (len < 6 || p[5] != ':')
        goto hms;

    if (count_digits(p, 6, len) != 2)
        return 0;

    s = parse_number(p, 6, 2);
    n = 8;

    /* hh:mm:ss.fffffffff */
    if (n < len && (p[n] == '.' || p[n] == ',')) {
        size_t r = parse_fraction_digits(p, ++n, len, &f);
        if (!r)
            return 0;
        n += r;
    }

  hms:
    if (h > 23 || m > 59 || s > 59) {
        if (!(h == 24 && m == 0 && s == 0 && f == 0))
            return 0;
    }

    if (sp)
        *sp = h * 3600 + m * 60 + s;
    if (fp)
        *fp = f;
    return n;
}

/*
 *  Z
 *  ±hh
 *  ±hh:mm
 */

size_t
dt_parse_iso_zone_extended(const char *str, size_t len, int *op) {
    const unsigned char *p;
    int o, h, m, sign;
    size_t n;

    if (len < 1)
        return 0;

    p = (const unsigned char *)str;
    switch (*p) {
        case 'Z':
            o = 0;
            n = 1;
            goto zulu;
        case '+':
            sign = 1;
            break;
        case '-':
            sign = -1;
            break;
        default:
            return 0;
    }

    if (len < 3 || count_digits(p, 1, len) != 2)
        return 0;

    h = parse_number(p, 1, 2);
    m = 0;
    n = 3;

    if (len < 4 || p[3] != ':')
        goto hm;

    if (count_digits(p, 4, len) != 2)
        return 0;

    m = parse_number(p, 4, 2);
    n = 6;

 hm:
    if (h > 23 || m > 59)
        return 0;
    o = sign * (h * 60 + m);
#ifdef DT_PARSE_ISO_STRICT
    if (o == 0 && sign < 0)
        return 0;
#endif

 zulu:
    if (op)
        *op = o;
    return n;
}

/*
 *  z
 *  Z
 *  GMT
 *  GMT±h
 *  GMT±hhmm
 *  GMT±h:mm
 *  GMT±hh:mm
 *  UTC
 *  UTC±h
 *  UTC±hhmm
 *  UTC±h:mm
 *  UTC±hh:mm
 *  ±h
 *  ±hh
 *  ±hhmm
 *  ±h:mm
 *  ±hh:mm
 */

size_t
dt_parse_iso_zone_lenient(const char *str, size_t len, int *op) {
    const unsigned char *p;
    int o, h, m, sign;
    size_t n;

    if (len < 1)
        return 0;

    p = (const unsigned char *)str;
    switch (*p) {
        case 'z':
        case 'Z':
            o = 0;
            n = 1;
            goto zulu;
        case 'G':
            if (len < 3 || p[1] != 'M' || p[2] != 'T')
                return 0;
            if (len > 3 && (p[3] == '+' || p[3] == '-')) {
                if (!(n = dt_parse_iso_zone_lenient(str + 3, len - 3, op)))
                    return 0;
                return n + 3;
            }
            o = 0;
            n = 3;
            goto zulu;
        case 'U':
            if (len < 3 || p[1] != 'T' || p[2] != 'C')
                return 0;
            if (len > 3 && (p[3] == '+' || p[3] == '-')) {
                if (!(n = dt_parse_iso_zone_lenient(str + 3, len - 3, op)))
                    return 0;
                return n + 3;
            }
            o = 0;
            n = 3;
            goto zulu;
        case '+':
            sign = 1;
            break;
        case '-':
            sign = -1;
            break;
        default:
            return 0;
    }

    if (len < 2)
        return 0;

    n = count_digits(p, 1, len);
    m = 0;
    switch (n) {
        case 1: /* ±h */
            h = parse_number(p, 1, 1);
            n = 2;
            break;
        case 2: /* ±hh */
            h = parse_number(p, 1, 2);
            n = 3;
            break;
        case 4: /* ±hhmm */
            h = parse_number(p, 1, 2);
            m = parse_number(p, 3, 2);
            n = 5;
            goto hm;
        default:
            return 0;
    }
    
    if (len < n + 1 || p[n] != ':')
        goto hm;

    if (count_digits(p, ++n, len) != 2)
        return 0;

    m = parse_number(p, n, 2);
    n += 2;

 hm:
    if (h > 23 || m > 59)
        return 0;
    o = sign * (h * 60 + m);

 zulu:
    if (op)
        *op = o;
    return n;
}

#ifdef DT_PARSE_ISO_TNT
/*
 * Count number of delimiting dashes, Ws or Qs in date string like
 *  5879611-07-11, or 2012-Q4-85, or 10000W521
 * Allows both ISO8601 and extended Tarantool datetime formats
 */
static size_t
count_delims(const unsigned char *p, size_t i, size_t len) {
    size_t n = 0;

    for (; i < len; i++) {
        switch (p[i]) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            continue;
        case 'Q': case 'W':
        case '-':
            n++;
            continue;
        }
        break;
    }
    return n;
}
#endif
/*
 *  Basic      Extended
 *  20121224   2012-12-24   Calendar date   (ISO 8601)
 *  2012359    2012-359     Ordinal date    (ISO 8601)
 *  2012W521   2012-W52-1   Week date       (ISO 8601)
 *  2012Q485   2012-Q4-85   Quarter date
 *
 *  Tarantool extended ranges
 * #ifdef DT_PARSE_ISO_TNT
 *  -001-12-31      0000-01-01
 *  -5879610-06-22  5879611-07-11
 * #endif
 */
size_t
dt_parse_iso_date(const char *str, size_t len, dt_t *dtp) {
    const unsigned char *p = (const unsigned char *)str;
    int y, x, d;
    size_t n;
    dt_t dt;
    int head_n;
#ifdef DT_PARSE_ISO_TNT
    int sign = +1;
    int dashes_n;

    if (p[0] == '-') {
        sign = -1;
        p++;
        len--;
    }
    dashes_n = count_delims(p, 0, len);
#endif

    head_n = n = count_digits(p, 0, len);
    switch (n) {
#ifdef DT_PARSE_ISO_TNT
        case 3: /* -001-01-01 | 100W521 (extended Tarantool range) */
            if (!dashes_n)
                return 0;
            y = parse_number(p, 0, 3);
            break;
        case 4: /* -2001 (extended Tarantool range) | 2001-01-01 | 1000W521 */
            y = parse_number(p, 0, 4);
            break;
        case 5: /* 10000-01-01 | 10000W521 (extended Tarantool range) */
        case 6: /* 109000-01-01 | 109000W521 (extended Tarantool range) */
            if (!dashes_n)
                return 0;
            y = parse_number(p, 0, n);
            break;
        case 7: /* 5879611-07-11 | 1000000W521 (extended Tarantool range) */
            if (dashes_n > 0) {
                y = parse_number(p, 0, 7);
                break;
            }
            /* 2012359 (basic ordinal date) */
            y = parse_number(p, 0, 4);
            d = parse_number(p, 4, 3);
            p += 7;
            goto yd;
#else
        case 4: /* 2012 (year) */
            y = parse_number(p, 0, 4);
            break;
        case 7: /* 2012359 (basic ordinal date) */
            y = parse_number(p, 0, 4);
            d = parse_number(p, 4, 3);
            p += 7;
            goto yd;
#endif
        case 8: /* 20121224 (basic calendar date) */
            y = parse_number(p, 0, 4);
            x = parse_number(p, 4, 2);
            d = parse_number(p, 6, 2);
            p += 8;
            goto ymd;
        default:
            return 0;
    }

    if (len < (n + 4))
        return 0;

    p += n;
    n = count_digits(p, 1, len);
    switch (p[0]) {
        case '-': /* 2012-359 | 2012-12-24 | 2012-W52-1 | 2012-Q4-85 */
            break;
#ifndef DT_PARSE_ISO_STRICT
        case 'Q': /* 2012Q485 */
            if (n != 3)
                return 0;
            x = parse_number(p, 1, 1);
            d = parse_number(p, 2, 2);
            p += 4;
            goto yqd;
#endif
        case 'W': /* 2012W521 */
            if (n != 3)
                return 0;
            x = parse_number(p, 1, 2);
            d = parse_number(p, 3, 1);
            p += 4;
            goto ywd;
        default:
            return 0;
    }

    switch (n) {
        case 0: /* 2012-Q4-85 | 2012-W52-1 */
            break;
        case 2: /* 2012-12-24 */
            if (p[3] != '-' || count_digits(p, 4, len) != 2)
                return 0;
            x = parse_number(p, 1, 2);
            d = parse_number(p, 4, 2);
            p += 6;
            goto ymd;
        case 3: /* 2012-359 */
            d = parse_number(p, 1, 3);
            p += 4;
            goto yd;
        default:
            return 0;
    }

    if (len < (head_n + 6))
        return 0;

    n = count_digits(p, 2, len);
    switch (p[1]) {
#ifndef DT_PARSE_ISO_STRICT
        case 'Q': /* 2012-Q4-85 */
            if (n != 1 || p[3] != '-' || count_digits(p, 4, len) != 2)
                return 0;
            x = parse_number(p, 2, 1);
            d = parse_number(p, 4, 2);
            p += 6;
            goto yqd;
#endif
        case 'W': /* 2012-W52-1 */
            if (n != 2 || p[4] != '-' || count_digits(p, 5, len) != 1)
                return 0;
            x = parse_number(p, 2, 2);
            d = parse_number(p, 5, 1);
            p += 6;;
            goto ywd;
        default:
            return 0;
    }

  yd:
#ifdef DT_PARSE_ISO_TNT
    if (!dt_from_yd_checked(sign * y, d, &dt))
        return 0;
#else
    if (!dt_valid_yd(y, d))
        return 0;
    dt = dt_from_yd(y, d);
#endif
    goto finish;

  ymd:
#ifdef DT_PARSE_ISO_TNT
    if (!dt_from_ymd_checked(sign * y, x, d, &dt))
        return 0;;
#else
    if (!dt_valid_ymd(y, x, d))
        return 0;
    dt = dt_from_ymd(y, x, d);
#endif
    goto finish;

#ifndef DT_PARSE_ISO_STRICT
  yqd:
#ifdef DT_PARSE_ISO_TNT
    if (!dt_from_yqd_checked(sign * y, x, d, &dt))
        return 0;
#else
    if (!dt_valid_yqd(y, x, d))
        return 0;
    dt = dt_from_yqd(y, x, d);
#endif
    goto finish;
#endif

  ywd:
#ifdef DT_PARSE_ISO_TNT
    if (!dt_from_ywd_checked(sign * y, x, d, &dt))
        return 0;
#else
    if (!dt_valid_ywd(y, x, d))
        return 0;
    dt = dt_from_ywd(y, x, d);
#endif

  finish:
#ifndef DT_PARSE_ISO_YEAR0
    if (y < 1)
        return 0;
#endif
    if (dtp)
        *dtp = dt;
    return (p - (const unsigned char *)str);
}

/*
 *  Basic               Extended
 *  T12                 N/A
 *  T1230               T12:30
 *  T123045             T12:30:45
 *  T123045.123456789   T12:30:45.123456789
 *  T123045,123456789   T12:30:45,123456789
 *
 *  The time designator [T] may be omitted.
 */

size_t
dt_parse_iso_time(const char *str, size_t len, int *sod, int *nsec) {
    size_t n, r;

    if (len < 2)
        return 0;

    if (str[0] == 'T')
        r = 1, ++str, --len;
    else
        r = 0;

    if (len < 2 || str[2] == ':')
        n = dt_parse_iso_time_extended(str, len, sod, nsec);
    else
        n = dt_parse_iso_time_basic(str, len, sod, nsec);

    if (!n)
        return 0;
    return r + n;
}

/* 
 *  Basic    Extended
 *  Z        N/A
 *  ±hh      N/A
 *  ±hhmm    ±hh:mm
 */

size_t
dt_parse_iso_zone(const char *str, size_t len, int *offset) {
    if (len < 3 || str[3] == ':')
        return dt_parse_iso_zone_extended(str, len, offset);
    else
        return dt_parse_iso_zone_basic(str, len, offset);
}

