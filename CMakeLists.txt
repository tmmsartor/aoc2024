cmake_minimum_required(VERSION 3.20)
project(aoc2024 VERSION 1.0)


set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_compile_options(-ftime-report)

add_subdirectory(src)
