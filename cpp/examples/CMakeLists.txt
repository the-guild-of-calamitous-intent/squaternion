include(FetchContent)


# serialcomm -----------------
FetchContent_Declare(serialcomm
    GIT_REPOSITORY "https://github.com/gecko-robotics/serialcomm.git"
    GIT_TAG "origin/main"
)

# yivo -----------------
FetchContent_Declare(yivo
    GIT_REPOSITORY "https://github.com/MomsFriendlyRobotCompany/yivo.git"
    GIT_TAG "origin/main"
    SOURCE_SUBDIR "cpp"
)

FetchContent_MakeAvailable(serialcomm yivo)

list(APPEND APPS
    simple
    sensor
)

# message(STATUS "Examples ----------------------")
foreach(name ${APPS})
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} squaternion serialcomm yivo)
    # target_include_directories(${name} PUBLIC ../src)
endforeach()