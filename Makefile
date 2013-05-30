CC      = cc
GCOV    = gcov
CFLAGS  = $(DCFLAGS) -Wall -I. -I..
LDFLAGS += -lc $(DLDFLAGS)

HARNESS_OBJS = \
	t/add_years.o \
	t/add_quarters.o \
	t/add_months.o \
	t/add_weekdays.o \
	t/add_workdays.o \
	t/days_in_month.o \
	t/days_in_quarter.o \
	t/days_in_year.o \
	t/delta_weekdays.o \
	t/delta_workdays.o \
	t/delta_yd.o \
	t/delta_ymd.o \
	t/delta_yqd.o \
	t/easter_orthodox.o \
	t/easter_western.o \
	t/first_day_of_month.o \
	t/first_day_of_quarter.o \
	t/first_day_of_week.o \
	t/first_day_of_year.o \
	t/is_holiday.o \
	t/is_workday.o \
	t/last_day_of_month.o \
	t/last_day_of_quarter.o \
	t/last_day_of_week.o \
	t/last_day_of_year.o \
	t/next_day_of_week.o \
	t/next_weekday.o \
	t/nth_day_of_week.o \
	t/parse_string.o \
	t/prev_day_of_week.o \
	t/prev_weekday.o \
	t/tm.o \
	t/yd.o \
	t/ymd.o \
	t/ymd_epochs.o \
	t/yqd.o \
	t/ywd.o \

HARNESS_EXES = \
	t/yd.t \
	t/ymd.t \
	t/ymd_epochs.t \
	t/yqd.t \
	t/ywd.t \
	t/tm.t \
	t/easter_western.t \
	t/easter_orthodox.t \
	t/days_in_year.t \
	t/days_in_month.t \
	t/days_in_quarter.t \
	t/first_day_of_year.t \
	t/first_day_of_quarter.t \
	t/first_day_of_month.t \
	t/first_day_of_week.t \
	t/last_day_of_year.t \
	t/last_day_of_quarter.t \
	t/last_day_of_month.t \
	t/last_day_of_week.t \
	t/next_day_of_week.t \
	t/prev_day_of_week.t \
	t/next_weekday.t \
	t/prev_weekday.t \
	t/nth_day_of_week.t \
	t/add_years.t \
	t/add_quarters.t \
	t/add_months.t \
	t/add_weekdays.t \
	t/delta_yd.t \
	t/delta_ymd.t \
	t/delta_yqd.t \
	t/delta_weekdays.t \
	t/parse_string.t \
	t/add_workdays.t \
	t/delta_workdays.t \
	t/is_holiday.t \
	t/is_workday.t

HARNESS_DEPS = \
	dt.o \
	dt_easter.o \
	dt_parse.o \
	dt_search.o \
	dt_weekday.o \
	dt_workday.o \
	t/tap.o

.SUFFIXES:
.SUFFIXES: .o .c .t

.PHONY: all check-asan harness test gcov cover clean

.o.t:
	$(CC) $(LDFLAGS) $< dt.o dt_easter.o dt_parse.o dt_search.o dt_weekday.o dt_workday.o t/tap.o -o $@

dt.o: \
	dt_config.h dt.h dt.c

dt_easter.o: \
	dt_easter.h dt_easter.c

dt_parse.o: \
	dt_parse.h dt_parse.c

dt_search.o: \
	dt_search.h dt_search.c

dt_weekday.o: \
	dt_weekday.h dt_weekday.c

dt_workday.o: \
	dt_workday.h dt_workday.c

t/tap.o: \
	t/tap.h t/tap.c

t/add_years.o: \
	$(HARNESS_DEPS) t/add_years.c
t/add_quarters.o: \
	$(HARNESS_DEPS) t/add_quarters.c
t/add_months.o: \
	$(HARNESS_DEPS) t/add_months.c t/add_months.h
t/add_weekdays.o: \
	$(HARNESS_DEPS) t/add_weekdays.c
t/add_workdays.o: \
	$(HARNESS_DEPS) t/add_workdays.c
t/days_in_month.o: \
	$(HARNESS_DEPS) t/days_in_month.c
t/days_in_quarter.o: \
	$(HARNESS_DEPS) t/days_in_quarter.c
t/days_in_year.o: \
	$(HARNESS_DEPS) t/days_in_year.c
t/delta_weekdays.o: \
	$(HARNESS_DEPS) t/delta_weekdays.c
t/delta_workdays.o: \
	$(HARNESS_DEPS) t/delta_workdays.c
t/delta_yd.o: \
	$(HARNESS_DEPS) t/delta_yd.c
t/delta_ymd.o: \
	$(HARNESS_DEPS) t/delta_ymd.c
t/delta_yqd.o: \
	$(HARNESS_DEPS) t/delta_yqd.c
t/easter_orthodox.o: \
	$(HARNESS_DEPS) t/easter_orthodox.c t/easter_orthodox.h
t/easter_western.o: \
	$(HARNESS_DEPS) t/easter_western.c t/easter_western.h
t/first_day_of_month.o: \
	$(HARNESS_DEPS) t/first_day_of_month.c t/first_day_of_month.h
t/first_day_of_quarter.o: \
	$(HARNESS_DEPS) t/first_day_of_quarter.c t/first_day_of_quarter.h
t/first_day_of_week.o: \
	$(HARNESS_DEPS) t/first_day_of_week.c
t/first_day_of_year.o: \
	$(HARNESS_DEPS) t/first_day_of_year.c
t/is_holiday.o: \
	$(HARNESS_DEPS) t/is_holiday.c
t/is_workday.o: \
	$(HARNESS_DEPS) t/is_workday.c
t/last_day_of_month.o: \
	$(HARNESS_DEPS) t/last_day_of_month.c t/last_day_of_month.h
t/last_day_of_quarter.o: \
	$(HARNESS_DEPS) t/last_day_of_quarter.c t/last_day_of_quarter.h
t/last_day_of_week.o: \
	$(HARNESS_DEPS) t/last_day_of_week.c
t/last_day_of_year.o: \
	$(HARNESS_DEPS) t/last_day_of_year.c
t/next_day_of_week.o: \
	$(HARNESS_DEPS) t/next_day_of_week.c
t/next_weekday.o: \
	$(HARNESS_DEPS) t/next_weekday.c
t/nth_day_of_week.o: \
	$(HARNESS_DEPS) t/nth_day_of_week.c t/nth_day_of_week.h
t/parse_string.o: \
	$(HARNESS_DEPS) t/parse_string.c
t/prev_day_of_week.o: \
	$(HARNESS_DEPS) t/prev_day_of_week.c
t/prev_weekday.o: \
	$(HARNESS_DEPS) t/prev_weekday.c
t/tm.o: \
	$(HARNESS_DEPS) t/tm.c
t/yd.o: \
	$(HARNESS_DEPS) t/yd.c
t/ymd.o: \
	$(HARNESS_DEPS) t/ymd.c
t/ymd_epochs.o: \
	$(HARNESS_DEPS) t/ymd_epochs.c
t/yqd.o: \
	$(HARNESS_DEPS) t/yqd.c
t/ywd.o: \
	$(HARNESS_DEPS) t/ywd.c t/ywd.h


all: \
	test

harness: \
	$(HARNESS_EXES)

test: harness 
	@prove $(HARNESS_EXES)

check-asan:
	@$(MAKE) DCFLAGS="-O1 -g -faddress-sanitizer -fno-omit-frame-pointer" \
			 DLDFLAGS="-g -faddress-sanitizer" test

gcov:
	@$(MAKE) DCFLAGS="-O0 -g -coverage" DLDFLAGS="-coverage" test
	@$(GCOV) dt.c dt_easter.c dt_parse.c dt_search.c dt_weekday.c dt_workday.c 

cover:
	@$(MAKE) DCFLAGS="-O0 -g --coverage" DLDFLAGS="-coverage" test
	@$(GCOV) -abc dt_easter.c dt_parse.c dt_search.c dt_weekday.c dt_workday.c 
	@gcov2perl *.gcov
	@cover --no-gcov

clean:
	rm -f $(HARNESS_DEPS) $(HARNESS_OBJS) $(HARNESS_EXES) *.gc{ov,da,no} t/*.gc{ov,da,no}

