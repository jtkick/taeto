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

# Optional documentation to build
option(BUILD_DOCS "Build Doxygen documentation" ON)
find_package(Doxygen)
if(BUILD_DOCS AND DOXYGEN_FOUND)
    # Configure the Doxyfile.in template
    configure_file(
        ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
    )

    # Add a custom target to run Doxygen
    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating Doxygen documentation..."
        VERBATIM
    )
     
    # Make it easier to open the HTML documentation
    if(UNIX) # For Linux and macOS
        add_custom_target(open_docs
            COMMAND xdg-open ${CMAKE_BINARY_DIR}/html_docs/index.html
            COMMENT "Opening Doxygen HTML documentation..."
        )
    elseif(WIN32) # For Windows
        add_custom_target(open_docs
            COMMAND cmd.exe /C start ${CMAKE_BINARY_DIR}/html_docs/index.html
            COMMENT "Opening Doxygen HTML documentation..."
        )
    endif()

    # Add the documentation directory to the list of installable files
    install(DIRECTORY ${CMAKE_BINARY_DIR}/html_docs DESTINATION share/doc/${PROJECT_NAME})

else()
    message(STATUS "Doxygen documentation will not be built (BUILD_DOCS is OFF or Doxygen not found).")
endif()

# Set include directories
target_include_directories(Taeto PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/deps/lodepng>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add dependencies in /deps directory
add_subdirectory(deps/glm)
add_subdirectory(deps/SDL)
add_subdirectory(deps/SFML)
add_subdirectory(deps/spdlog)

# Link dependencies to the library
target_link_libraries(Taeto PUBLIC ncurses sfml-window sfml-audio spdlog_header_only SDL2)

# Specify C++ standard
target_compile_features(Taeto PUBLIC cxx_std_17)

# Set other compiler options (e.g., warnings)
target_compile_options(Taeto PRIVATE -Wall -Wextra -Wpedantic)