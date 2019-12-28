cmake_minimum_required(VERSION 2.6)
PROJECT(hw8)

# set(CMAKE_CXX_FLAGS -std=c++14)
add_compile_options("-g" "-Wall" "-Wextra" "-std=c++14" "-O2" "-DUSE_FFT")

SUBDIRS( test )