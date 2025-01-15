# Include the Taeto library headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Vaporwave Demo
add_executable(demo demo.cpp)
target_link_libraries(demo PUBLIC Taeto)

# High Dynamic Range Test
add_executable(hdr_test hdr_test.cpp)
target_link_libraries(hdr_test PUBLIC Taeto)

# Light Filter Test
add_executable(light_filter_test light_filter_test.cpp)
target_link_libraries(light_filter_test PUBLIC Taeto)

# Light Mixing Test
add_executable(light_mixing_test light_mixing_test.cpp)
target_link_libraries(light_mixing_test PUBLIC Taeto)

# Normal Mapping Test
add_executable(normal_mapping_test normal_mapping_test.cpp)
target_link_libraries(normal_mapping_test PUBLIC Taeto)

# Output tests to 'build' directory
set_target_properties(
    demo hdr_test light_filter_test light_mixing_test normal_mapping_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/tests"
)