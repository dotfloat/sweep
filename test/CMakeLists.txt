cmake_minimum_required (VERSION 2.6)
project (SweepTest)

include_directories (${CMAKE_SOURCE_DIR}/../include/)

add_executable (sweep_test test.c)
