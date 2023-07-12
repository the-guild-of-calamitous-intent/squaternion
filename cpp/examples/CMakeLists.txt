list(APPEND ex
    simple.cpp
)

# message(STATUS "Examples ----------------------")
foreach(src ${ex})
    get_filename_component(name ${src} NAME_WE)
    # message(STATUS " -> ${name}")
    add_executable(${name} ${src})
    target_link_libraries(${name} squaternion)
    target_include_directories(${name} PUBLIC ../src)
    # add_test(NAME ${name} COMMAND ${name})
endforeach()