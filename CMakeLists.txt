cmake_minimum_required(VERSION 3.10)

project(Taeto VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Curses REQUIRED)

add_subdirectory(deps/SFML)
# add_subdirectory(deps/spdlog)
add_subdirectory(deps/glm)

include_directories(
    "include" "deps/glm" "deps/SFML/include" "deps/tclap/include" "deps/lodepng" ${CURSES_INCLUDE_DIR}
)

file(GLOB_RECURSE SOURCES
    "src/*.cpp" "deps/lodepng/lodepng.cpp"
)

# add_executable(taeto ${SOURCES})


#############################################################################

add_library(taeto STATIC
    ${SOURCES}
)

target_include_directories(taeto PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(taeto PUBLIC
    ncurses sfml-window sfml-audio
)

target_link_libraries(taeto PRIVATE spdlog_header_only)

install(TARGETS taeto
    EXPORT TaetoTargets
    DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)

# export(EXPORT TaetoTargets FILE "${CMAKE_CURRENT_BINARY_DIR}/TaetoTargets.cmake")

# Export the target and export set
export(TARGETS taeto sfml-system sfml-audio sfml-window FILE "${CMAKE_CURRENT_BINARY_DIR}/TaetoTargets.cmake")

# To make this an installable export set, also include the following:
# Export the cmake package configuration file
install(EXPORT TaetoTargets
    NAMESPACE taeto::
    FILE TaetoTargets.cmake
    DESTINATION lib/cmake/Taeto
)

# Optionally, add CMake configuration files to make the package findable:
include(CMakePackageConfigHelpers)
# configure_package_config_file(
#     "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TaetoConfig.cmake.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/TaetoConfig.cmake"
#     INSTALL_DESTINATION lib/cmake/Taeto
# )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/TaetoConfig.cmake"
    DESTINATION lib/cmake/Taeto
)