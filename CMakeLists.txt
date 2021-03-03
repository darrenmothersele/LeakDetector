cmake_minimum_required(VERSION 3.17)
project(LeakDetector)

add_library(LeakDetector STATIC debug_new.cpp LeakDetector.h)
target_include_directories(LeakDetector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
