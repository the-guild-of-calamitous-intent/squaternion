cmake_minimum_required(VERSION 3.25)
PROJECT(squaternion VERSION "2024.06.16")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


if(PROJECT_IS_TOP_LEVEL)
    cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
    cmake_host_system_information(RESULT OSN QUERY OS_NAME)
    cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
    cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

    message(STATUS "-------------------------------------")
    message(STATUS "  Project: ${PROJECT_NAME}")
    message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
    message(STATUS "-------------------------------------")
    message(STATUS " ${HOST}")
    message(STATUS " ${OSN}: ${OS_VERSION}")
    message(STATUS " ${PROC}")
    message(STATUS "-------------------------------------")

    set(BUILD_EXAMPLES ON)
    set(BUILD_GTESTS ON)
else()
    message(STATUS "-> ${PROJECT_NAME} is submodule")
    set(BUILD_EXAMPLES OFF)
    set(BUILD_GTESTS OFF)
endif()

add_library(${PROJECT_NAME}
    INTERFACE
    # src/quaternion.cpp
    # src/quaternion_filters.cpp
)
target_include_directories(${PROJECT_NAME} INTERFACE src/)
# target_include_directories(${PROJECT_NAME}
#     INTERFACE
#         src/
# )

# Examples -----------------------------------------------------------
message(STATUS "Building ${PROJECT_NAME} examples is ${BUILD_EXAMPLES}")
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests --------------------------------------------------------------
message(STATUS "Building ${PROJECT_NAME} gtests is ${BUILD_GTESTS}")
if(BUILD_GTESTS)
    add_subdirectory(gtests)
endif()
