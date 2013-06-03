cmake_minimum_required (VERSION 2.6)
project (Sweep)

include_directories (include)

option (BUILD_LIBSWEEP "Build the actual sweep library" ON)
option (BUILD_TEST "Build test program" OFF)

if (BUILD_LIBSWEEP)
	include_directories (libsweep)
	add_subdirectory (libsweep)
endif (BUILD_LIBSWEEP)

if (BUILD_TEST)
	include_directories (test)
	add_subdirectory (test)
endif (BUILD_TEST)