#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    next if /\A \# /x;
    chomp;
    my ($y, $doy, $dt) = split /,\s*/, $_;

    {
        my $got = dt_from_yd($y, $doy);
        is($got, $dt, "dt_from_yd($y, $doy)");
    }

    {
        my $got = sprintf '%.4d-%.3d', dt_to_yd($dt);
        my $exp = sprintf '%.4d-%.3d', $y, $doy;
        is($got, $exp, "dt_to_yd($dt)");
    }

    {
        my $got = dt_day_of_year($dt);
        is($got, $doy, "dt_day_of_year($dt)");
    }

    {
        my $got = dt_valid_yd($y, $doy);
        is($got, !0, "dt_valid_yd($y, $doy)");
    }
}

done_testing;

__DATA__
1970, 195, 719357
1971, 256, 719783
1972, 199, 720091
1973, 331, 720589
1974, 249, 720872
1975,  30, 721018
1976, 300, 721653
1977, 217, 721936
1978, 114, 722198
1979,  38, 722487
1980, 278, 723092
1981, 300, 723480
1982,  58, 723603
1983, 222, 724132
1984, 185, 724460
1985, 324, 724965
1986,  93, 725099
1987, 338, 725709
1988, 174, 725910
1989, 350, 726452
1990, 170, 726637
1991, 291, 727123
1992, 251, 727448
1993, 214, 727777
1994, 107, 728035
1995,  94, 728387
1996, 360, 729018
1997, 164, 729188
1998,  45, 729434
1999, 360, 730114
2000, 341, 730460
2001, 133, 730618
2002, 140, 730990
2003, 140, 731355
2004, 233, 731813
2005,  22, 731968
2006,  80, 732391
2007, 340, 733016
2008, 365, 733406
2009, 254, 733661
2010, 116, 733888
2011, 301, 734438
2012, 143, 734645
2013, 106, 734974
2014, 102, 735335
2015, 347, 735945
2016, 210, 736173
2017, 277, 736606
2018, 139, 736833
2019,  99, 737158
2020, 282, 737706
