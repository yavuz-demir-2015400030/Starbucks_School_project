cmake_minimum_required(VERSION 2.8)
project(project2_yavuz_demir_2015400030_master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Customer.cpp Customer.h Cashier.cpp Cashier.h Barista.cpp Barista.h)
add_executable(project2_yavuz_demir_2015400030_master ${SOURCE_FILES})