cmake_minimum_required(VERSION 3.2)
project(lulesh-RAJA-omp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(RAJA REQUIRED)

add_subdirectory(src)
