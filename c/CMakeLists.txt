cmake_minimum_required(VERSION 3.25)
PROJECT(squaternion LANGUAGES C VERSION "2024.06.16")

set(CMAKE_C_STANDARD 23)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
# string(PREPEND CMAKE_EXE_LINKER_FLAGS " -Wl,--print-memory-usage ")

# if(CMAKE_COMPILER_IS_GNUC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
# add_compile_options(-Wall -Wextra -Wpedantic)
# endif()


if(PROJECT_IS_TOP_LEVEL)
    cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
    cmake_host_system_information(RESULT OSN QUERY OS_NAME)
    cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
    cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

    message(STATUS "-------------------------------------")
    message(STATUS " Project: ${PROJECT_NAME}")
    message(STATUS "-------------------------------------")
    message(STATUS " Compiler")
    message(STATUS "  C ${CMAKE_C_STANDARD}: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} (${CMAKE_C_COMPILER})")
  # message(STATUS "  CXX ${CMAKE_CXX_STANDARD}: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER})")
    message(STATUS "-------------------------------------")
    message(STATUS " ${HOST}")
    message(STATUS " ${OSN}: ${OS_VERSION}")
    message(STATUS " ${PROC}")
    message(STATUS "-------------------------------------")

    set(BUILD_EXAMPLES ON)
    set(BUILD_SCRUFFY ON)
else()
    if(PICO_PLATFORM)
        message(STATUS "-> ${PROJECT_NAME} is submodule for ${PICO_PLATFORM}")
    else()
        message(STATUS "-> ${PROJECT_NAME} is submodule")
    endif()
    set(BUILD_EXAMPLES OFF)
    set(BUILD_SCRUFFY OFF)
endif()

add_library(${PROJECT_NAME}
    src/quaternion.c
    src/algorithms.c
)
target_include_directories(${PROJECT_NAME} PUBLIC src)

# Examples -----------------------------------------------------------
message(STATUS "Building ${PROJECT_NAME} examples is ${BUILD_EXAMPLES}")
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests --------------------------------------------------------------
message(STATUS "Building ${PROJECT_NAME} scruffy is ${BUILD_SCRUFFY}")
if(BUILD_SCRUFFY)
    add_subdirectory(scruffy)
endif()
