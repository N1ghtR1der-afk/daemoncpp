cmake_minimum_required(VERSION 3.0)
project(Daemon VERSION 0.1 LANGUAGES CXX)
set(PROJECT_NAME "Daemon")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
find_package(Boost REQUIRED COMPONENTS program_options)
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
include_directories(libs)
