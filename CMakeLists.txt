cmake_minimum_required(VERSION 3.29)
project(DoomConsole)

set(CMAKE_CXX_STANDARD 20)

set(SRC_DIR src)
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")
add_executable(DoomConsole ${SOURCES})
