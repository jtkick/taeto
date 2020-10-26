cmake_minimum_required(VERSION 2.8.9)
project(taeto)
 
#Bring the headers, such as Student.h into the project
find_package(Curses REQUIRED)
include_directories(include ${CURSES_INCLUDE_DIR})
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(taeto ${SOURCES})

target_link_libraries(taeto ncurses)
