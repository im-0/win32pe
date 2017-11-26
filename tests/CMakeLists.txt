set(TESTS
    test_load
)

foreach(_test ${TESTS})
    add_executable(${_test} ${_test}.cpp)
    set_target_properties(${_test} PROPERTIES
        CXX_STANDARD          11
        CXX_STANDARD_REQUIRED ON
    )
    target_link_libraries(${_test} win32pe)
    add_test(NAME ${_test}
        COMMAND           ${_test}
        WORKING_DIRECTORY $<TARGET_FILE_DIR:win32pe>
    )
endforeach()
