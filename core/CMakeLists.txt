# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (c) 2026 add000
cmake_minimum_required(VERSION 3.16)
project(shinon_core LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(shinon_core INTERFACE)
target_include_directories(shinon_core INTERFACE include)

enable_testing()
add_executable(test_biquad tests/test_biquad.cpp)
target_link_libraries(test_biquad shinon_core)
add_test(NAME biquad COMMAND test_biquad)
