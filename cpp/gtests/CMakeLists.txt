find_package(GTest REQUIRED)
if(GTest_FOUND)
    message(STATUS "=> Found gtest")
else()
    message(STATUS "*** Didn't find gtest")
endif()

#----------------------------
enable_testing()

list(APPEND stests
    main-gtest
)

message(STATUS "gTests ----------------------")
foreach(name ${stests})
    # message(STATUS " -> ${name}")
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
        GTest::gtest_main
        ${PROJECT_NAME})
    add_test(NAME ${name} COMMAND ${name})
endforeach()

include(GoogleTest)
gtest_discover_tests(${stests})