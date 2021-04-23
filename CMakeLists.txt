cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

project(cdt)

set (CDT_SOURCE_FILES
        dt_accessor.c
        dt_arithmetic.c
        dt_char.c
        dt_core.c
        dt_dow.c
        dt_easter.c
        dt_length.c
        dt_navigate.c
        dt_parse_iso.c
        dt_search.c
        dt_tm.c
        dt_util.c
        dt_valid.c
        dt_weekday.c
        dt_workday.c
        dt_zone.c
)

add_library(cdt STATIC ${CDT_SOURCE_FILES})

target_include_directories(cdt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
