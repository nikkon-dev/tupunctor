cmake_minimum_required(VERSION 2.8)
project(tupunctor)

set(SRCS main.cpp)
set(HDRS tupunctor.h)

add_definitions(-std=c++11)
add_executable(tupunctor-test ${SRCS} ${HDRS})
