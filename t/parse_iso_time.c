#include "dt.h"
#include "tap.h"
#include <string.h>

const struct good_t {
    int sod;
    int nsec;
    const char *str;
    size_t elen;
} good[] = {
    {     0,         0, "T00:00",                  6 },
    {     0,         0, "T00:00:00",               9 },
    {     0,         0, "T00:00:00.0",            11 },
    { 86400,         0, "T24:00",                  6 },
    { 86400,         0, "24:00",                   5 },
    { 86400,         0, "T24:00:00",               9 },
    { 86400,         0, "24:00:00",                8 },
    { 86400,         0, "T24:00:00.0",            11 },
    { 86400,         0, "24:00:00.0",             10 },
    { 86399,         0, "T23:59:59",               9 },
    { 86399,         0, "23:59:59",                8 },
    { 86340,         0, "T23:59",                  6 },
    { 86340,         0, "23:59",                   5 },
    {     0, 123456789, "T00:00:00.123456789",    19 },
    {     0, 123456780, "T00:00:00.12345678",     18 },
    {     0, 123456700, "T00:00:00.1234567",      17 },
    {     0, 123456000, "T00:00:00.123456",       16 },
    {     0, 123450000, "T00:00:00.12345",        15 },
    {     0, 123400000, "T00:00:00.1234",         14 },
    {     0, 123000000, "T00:00:00.123",          13 },
    {     0, 120000000, "T00:00:00.12",           12 },
    {     0, 100000000, "T00:00:00.1",            11 },
    {     0,  10000000, "T00:00:00.01",           12 },
    {     0,   1000000, "T00:00:00.001",          13 },
    {     0,    100000, "T00:00:00.0001",         14 },
    {     0,     10000, "T00:00:00.00001",        15 },
    {     0,      1000, "T00:00:00.000001",       16 },
    {     0,       100, "T00:00:00.0000001",      17 },
    {     0,        10, "T00:00:00.00000001",     18 },
    {     0,         1, "T00:00:00.000000001",    19 },
    {     0,         9, "T00:00:00.000000009",    19 },
    {     0,        90, "T00:00:00.00000009",     18 },
    {     0,       900, "T00:00:00.0000009",      17 },
    {     0,      9000, "T00:00:00.000009",       16 },
    {     0,     90000, "T00:00:00.00009",        15 },
    {     0,    900000, "T00:00:00.0009",         14 },
    {     0,   9000000, "T00:00:00.009",          13 },
    {     0,  90000000, "T00:00:00.09",           12 },
    {     0, 900000000, "T00:00:00.9",            11 },
    {     0, 990000000, "T00:00:00.99",           12 },
    {     0, 999000000, "T00:00:00.999",          13 },
    {     0, 999900000, "T00:00:00.9999",         14 },
    {     0, 999990000, "T00:00:00.99999",        15 },
    {     0, 999999000, "T00:00:00.999999",       16 },
    {     0, 999999900, "T00:00:00.9999999",      17 },
    {     0, 999999990, "T00:00:00.99999999",     18 },
    {     0, 999999999, "T00:00:00.999999999",    19 },
    {     0, 999999999, "T00:00:00.9999999999",   20 },
    {     0,         0, "T00:00:00.0",            11 },
    {     0,         0, "T00:00:00.00",           12 },
    {     0,         0, "T00:00:00.000",          13 },
    {     0,         0, "T00:00:00.0000",         14 },
    {     0,         0, "T00:00:00.00000",        15 },
    {     0,         0, "T00:00:00.000000",       16 },
    {     0,         0, "T00:00:00.0000000",      17 },
    {     0,         0, "T00:00:00.00000000",     18 },
    {     0,         0, "T00:00:00.000000000",    19 },
    {     0,         0, "T0000",                   5 },
    {     0,         0, "T000000",                 7 },
    {     0,         0, "T000000.0",               9 },
    { 86400,         0, "T2400",                   5 },
    { 86400,         0, "2400",                    4 },
    { 86400,         0, "T240000",                 7 },
    { 86400,         0, "240000",                  6 },
    { 86400,         0, "T240000.0",               9 },
    { 86399,         0, "T235959",                 7 },
    { 86399,         0, "235959",                  6 },
    { 86340,         0, "T2359",                   5 },
    { 86340,         0, "2359",                    4 },
    {     0, 123456789, "T000000.123456789",      17 },
    {     0, 123456780, "T000000.12345678",       16 },
    {     0, 123456700, "T000000.1234567",        15 },
    {     0, 123456000, "T000000.123456",         14 },
    {     0, 123450000, "T000000.12345",          13 },
    {     0, 123400000, "T000000.1234",           12 },
    {     0, 123000000, "T000000.123",            11 },
    {     0, 120000000, "T000000.12",             10 },
    {     0, 100000000, "T000000.1",               9 },
    {     0,  10000000, "T000000.01",             10 },
    {     0,   1000000, "T000000.001",            11 },
    {     0,    100000, "T000000.0001",           12 },
    {     0,     10000, "T000000.00001",          13 },
    {     0,      1000, "T000000.000001",         14 },
    {     0,       100, "T000000.0000001",        15 },
    {     0,        10, "T000000.00000001",       16 },
    {     0,         1, "T000000.000000001",      17 },
    {     0,         9, "T000000.000000009",      17 },
    {     0,        90, "T000000.00000009",       16 },
    {     0,       900, "T000000.0000009",        15 },
    {     0,      9000, "T000000.000009",         14 },
    {     0,     90000, "T000000.00009",          13 },
    {     0,    900000, "T000000.0009",           12 },
    {     0,   9000000, "T000000.009",            11 },
    {     0,  90000000, "T000000.09",             10 },
    {     0, 900000000, "T000000.9",               9 },
    {     0, 990000000, "T000000.99",             10 },
    {     0, 999000000, "T000000.999",            11 },
    {     0, 999900000, "T000000.9999",           12 },
    {     0, 999990000, "T000000.99999",          13 },
    {     0, 999999000, "T000000.999999",         14 },
    {     0, 999999900, "T000000.9999999",        15 },
    {     0, 999999990, "T000000.99999999",       16 },
    {     0, 999999999, "T000000.999999999",      17 },
    {     0, 999999999, "T000000.9999999999",     18 },
    {     0,         0, "T000000.0",               9 },
    {     0,         0, "T000000.00",             10 },
    {     0,         0, "T000000.000",            11 },
    {     0,         0, "T000000.0000",           12 },
    {     0,         0, "T000000.00000",          13 },
    {     0,         0, "T000000.000000",         14 },
    {     0,         0, "T000000.0000000",        15 },
    {     0,         0, "T000000.00000000",       16 },
    {     0,         0, "T000000.000000000",      17 },
};

const struct bad_t {
    const char *str;
} bad[] = {
    {"T"           },
    {"T00:0"       },
    {"T00:00:00."  },
    {"T0:00:00"    },
    {"T00:0:00"    },
    {"T00:00:0"    },
    {"T24:00:01"   },
    {"T24:59:59"   },
    {"T23:60:59"   },
    {"T23:59:60"   },
    {"T00"         },
    {"T000"        },
    {"T00000"      },
    {"T000000."    },
    {"T240001"     },
    {"T245959"     },
    {"T236059"     },
    {"T235960"     },
};

int 
main() {
    int i, ntests;

    ntests = sizeof(good) / sizeof(*good);
    for (i = 0; i < ntests; i++) {
        const struct good_t t = good[i];

        {
            int sod = 0, nsec = 0;
            size_t glen;

            glen = dt_parse_iso_time(t.str, strlen(t.str), &sod, &nsec);
            ok(glen == t.elen, "dt_parse_iso_time(%s) size_t: %d", t.str, (int)glen);
            cmp_ok(sod,  "==", t.sod,  "dt_parse_iso_time(%s) sod", t.str);
            cmp_ok(nsec, "==", t.nsec, "dt_parse_iso_time(%s) nsec", t.str);
        }
    }

    ntests = sizeof(bad) / sizeof(*bad);
    for (i = 0; i < ntests; i++) {
        const struct bad_t t = bad[i];

        {
            int sod = 0, nsec = 0;
            size_t glen;

            glen = dt_parse_iso_time(t.str, strlen(t.str), &sod, &nsec);
            ok(glen == 0, "dt_parse_iso_time(%s) size_t: %d", t.str, (int)glen);
        }
    }
    done_testing();
}

