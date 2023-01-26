cmake_minimum_required(VERSION 2.8.9)
project(taeto)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Curses REQUIRED)
find_package(spdlog REQUIRED)

# Detect and add SFML
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
#find_package(SFML 2 REQUIRED network audio graphics window system)
#if(SFML_FOUND)
#  include_directories(${SFML_INCLUDE_DIR})
#  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#endif()

include_directories("include"
                    "prerequisites/spdlog"
                    "prerequisites/tclap-1.2.4/include"
                    "prerequisites/lodepng/include"
                    "include/system_layer"
                    "include/system_layer/render_system"
                    "include/system_layer/render_system/frames"
                    "include/message_layer"
                    "include/scene_layer"
                    "assets/lights/include"
                    "assets/sprites/include"
                    "assets/scenes/include"
                    ${CURSES_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp" "src/*/*/*/*/*.cpp" "assets/*/src/*.cpp" "prerequisites/*/src/**")

add_executable(taeto ${SOURCES})

target_link_libraries(taeto ncurses sfml-window sfml-audio spdlog::spdlog)
