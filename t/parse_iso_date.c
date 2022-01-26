#include "dt.h"
#include "tap.h"
#include <string.h>

const struct good_t {
    int ey;
    int em;
    int ed;
    const char *str;
    size_t elen;
} good[] = {
    {2012, 12, 24, "20121224",                   8 },
    {2012, 12, 24, "20121224  Foo bar",          8 },
    {2012, 12, 24, "2012-12-24",                10 },
    {2012, 12, 24, "2012-12-24 23:59:59",       10 },
    {2012, 12, 24, "2012-12-24T00:00:00+00:00", 10 },
    {2012, 12, 24, "2012359",                    7 },
    {2012, 12, 24, "2012359T235959+0130",        7 },
    {2012, 12, 24, "2012-359",                   8 },
    {2012, 12, 24, "2012W521",                   8 },
    {2012, 12, 24, "2012-W52-1",                10 },
    {2012, 12, 24, "2012Q485",                   8 },
    {2012, 12, 24, "2012-Q4-85",                10 },
    {   1,  1,  1, "0001-Q1-01",                10 },
    {   1,  1,  1, "0001-W01-1",                10 },
    {   1,  1,  1, "0001-01-01",                10 },
    {   1,  1,  1, "0001-001",                   8 },
    {9999, 12, 31, "9999-12-31",                10 },
#ifdef DT_PARSE_ISO_YEAR0
    {   0,  1,  1, "0000-Q1-01",                10 },
    {   0,  1,  3, "0000-W01-1",                10 },
    {   0,  1,  1, "0000-01-01",                10 },
    {   0,  1,  1, "0000-001",                   8 },
#endif
#ifdef DT_PARSE_ISO_TNT
    {-200, 12, 31, "-200-12-31",                10 },
    {-1000,12, 31, "-1000-12-31",               11 },
    {-10000,12,31, "-10000-12-31",              12 },
    {-5879610,6,22,"-5879610-06-22",            14 },
    {-5879610,12,27,"-5879610W521",             12 },
    {10000, 1,  1, "10000-01-01",               11 },
    {5879611,7, 1, "5879611-07-01",             13 },
    {5879611,1, 1, "5879611Q101",               11 },
#endif
};

const struct bad_t {
    const char *str;
} bad[] = {
    {"20121232"     },  /* Invalid day of month */
    {"2012-12-310"  },  /* Invalid day of month */
    {"2012-13-24"   },  /* Invalid month */
    {"2012367"      },  /* Invalid day of year */
    {"2012-000"     },  /* Invalid day of year */
    {"2012W533"     },  /* Invalid week of year */
    {"2012-W52-8"   },  /* Invalid day of week */
    {"2012Q495"     },  /* Invalid day of quarter */
    {"2012-Q5-85"   },  /* Invalid quarter */
    {"20123670"     },  /* Trailing digit */
    {"201212320"    },  /* Trailing digit */
    {"2012-12"      },  /* Reduced accuracy */
    {"2012-Q4"      },  /* Reduced accuracy */
    {"2012-Q42"     },  /* Invalid */
    {"2012-Q1-1"    },  /* Invalid day of quarter */
    {"2012Q--420"   },  /* Invalid */
    {"2012-Q-420"   },  /* Invalid */
    {"2012Q11"      },  /* Incomplete */
    {"2012Q1234"    },  /* Trailing digit */
    {"2012W12"      },  /* Incomplete */
    {"2012W1234"    },  /* Trailing digit */
    {"2012W-123"    },  /* Invalid */
    {"2012-W12"     },  /* Incomplete */
    {"2012-W12-12"  },  /* Trailing digit */
    {"2012U1234"    },  /* Invalid */
    {"2012-1234"    },  /* Invalid */
    {"2012-X1234"   },  /* Invalid */
#ifndef DT_PARSE_ISO_YEAR0
    {"0000-Q1-01"   },  /* Year less than 0001 */
    {"0000-W01-1"   },  /* Year less than 0001 */
    {"0000-01-01"   },  /* Year less than 0001 */
    {"0000-001"     },  /* Year less than 0001 */
#endif
#ifndef DT_PARSE_ISO_TNT
    {"-200-12-31"   },  /* Year less than 0001 */
    {"-1000-12-31"  },  /* Year less than 0001 */
    {"-10000-12-31" },  /* Year less than 0001 */
    {"-5879610-06-01"}, /* Year less than 0001 */
    {"10000-01-01", },  /* Year greater than 9999 */
    {"5879611-07-01"},  /* Year greater than 9999 */
#endif
    /* fail both for standard and TNT parsing mode */
    {"-5879611-01-01"}, /* Year less than 5879610-06-22 */
    {"-5879611W011" },  /* Year less than 5879610-06-22 */
    {"5879612-01-01"},  /* Year greater than 5879611-07-11 */
    {"5879612W521"  },  /* Year greater than 5879611-07-11 */
};

int 
main() {
    int i, ntests;

    ntests = sizeof(good) / sizeof(*good);
    for (i = 0; i < ntests; i++) {
        const struct good_t t = good[i];

        {
            dt_t got = 0, exp = 0;
            size_t glen;

            glen = dt_parse_iso_date(t.str, strlen(t.str), &got);
            ok(glen == t.elen, "dt_parse_iso_date(%s) size_t: %d", t.str, (int)glen);
            exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_parse_iso_date(%s)", t.str);
        }
    }

    ntests = sizeof(bad) / sizeof(*bad);
    for (i = 0; i < ntests; i++) {
        const struct bad_t t = bad[i];

        {
            dt_t got = 0;
            size_t glen;

            glen = dt_parse_iso_date(t.str, strlen(t.str), &got);
            ok(glen == 0, "dt_parse_iso_date(%s) size_t: %d", t.str, (int)glen);
        }
    }
    done_testing();
}

