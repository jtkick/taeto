cmake_minimum_required(VERSION 2.8.9)
project(taeto)

#if (NOT CMAKE_BUILD_TYPE)
#  set (CMAKE_BUILD_TYPE Release)
#endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Curses REQUIRED)
include_directories(include ${CURSES_INCLUDE_DIR})
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(taeto ${SOURCES})

target_link_libraries(taeto ncurses)
