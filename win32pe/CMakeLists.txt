file(GLOB HEADERS include/win32pe/*.h)

set(SRC
    src/file.cpp
    src/fileheader.cpp
    src/optionalheader.cpp
)

add_library(win32pe SHARED ${SRC})

set_target_properties(win32pe PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
    DEFINE_SYMBOL         WIN32PE_LIBRARY
    PUBLIC_HEADER         "${HEADERS}"
    VERSION               ${PROJECT_VERSION}
    SOVERSION             ${PROJECT_VERSION_MAJOR}
)

target_include_directories(win32pe PUBLIC
    "$<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

install(TARGETS win32pe
    RUNTIME       DESTINATION bin
    LIBRARY       DESTINATION lib
    ARCHIVE       DESTINATION lib
    PUBLIC_HEADER DESTINATION include/win32pe
)
