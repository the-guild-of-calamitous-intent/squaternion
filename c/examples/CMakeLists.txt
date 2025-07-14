

list(APPEND APPS
    example
)

foreach(name ${APPS})
    add_executable(${name} ${name}.c)
    target_link_libraries(${name} squaternion)
    # target_include_directories(${name} PUBLIC ../src)
endforeach()