cmake_minimum_required(VERSION 2.8.9)
project(taeto)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Curses REQUIRED)
find_package(spdlog REQUIRED)

include_directories("include"
                    "prerequisites/spdlog"
                    "prerequisites/tclap-1.2.4/include"
                    "prerequisites/lodepng/include"
                    ${CURSES_INCLUDE_DIR})

# TODO: FIX THIS
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp" "src/*/*/*/*/*.cpp" "assets/*/src/*.cpp" "prerequisites/*/src/**")

add_executable(taeto ${SOURCES})

target_link_libraries(taeto ncurses sfml-window sfml-audio spdlog::spdlog)
