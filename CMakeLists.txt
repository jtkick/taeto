cmake_minimum_required(VERSION 2.8.9)
project(taeto)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Curses REQUIRED)

add_subdirectory(deps/SFML)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/glm)

include_directories("include"
                    "deps/glm"
		    "deps/SFML/include"
                    "deps/tclap/include"
                    "deps/lodepng"
                    ${CURSES_INCLUDE_DIR})

# TODO: FIX THIS
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp" "src/*/*/*/*/*.cpp" "assets/*/src/*.cpp" "deps/lodepng/lodepng.cpp")

add_executable(taeto ${SOURCES})

target_link_libraries(taeto ncurses sfml-window sfml-audio spdlog::spdlog)
