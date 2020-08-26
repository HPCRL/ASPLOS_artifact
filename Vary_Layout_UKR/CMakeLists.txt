cmake_minimum_required(VERSION 3.10)
project(UkrGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)
file(GLOB SOURCES "src/*.cc")

add_executable(UkrGen ${SOURCES})
