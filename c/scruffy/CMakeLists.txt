

add_subdirectory(extlibs/scruffy)

# Test executable
add_executable(test-all test.c)
target_link_libraries(test-all ${PROJECT_NAME} scruffy)

