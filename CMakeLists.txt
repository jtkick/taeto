# Minimum CMake version
cmake_minimum_required(VERSION 3.14)

# Project name and version
project(Taeto VERSION 0.0.0 LANGUAGES CXX)

# Specify the library target
file(GLOB_RECURSE SOURCES
    "src/*.cpp" "deps/lodepng/lodepng.cpp"
)
add_library(Taeto STATIC 
    ${SOURCES}
)

# Optional tests to build
option(BUILD_TESTS "Build test executables" ON)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Set include directories
target_include_directories(Taeto PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/deps/lodepng>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add dependencies in /deps directory
add_subdirectory(deps/glm)
add_subdirectory(deps/SFML)
add_subdirectory(deps/spdlog)

# Link dependencies to the library
target_link_libraries(Taeto PUBLIC ncurses sfml-window sfml-audio spdlog_header_only)

# Specify C++ standard
target_compile_features(Taeto PUBLIC cxx_std_17)

# Set other compiler options (e.g., warnings)
target_compile_options(Taeto PRIVATE -Wall -Wextra -Wpedantic)