cmake_minimum_required(VERSION 3.29)
project(DoomConsole)

set(CMAKE_CXX_STANDARD 20)

set(SRC_DIR src)
set(RESOURCE_DIR resources)
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

add_subdirectory(third_party)
add_executable(DoomConsole ${SOURCES})
target_link_libraries(DoomConsole lodepng)
target_include_directories(DoomConsole PUBLIC ${RESOURCE_DIR})
