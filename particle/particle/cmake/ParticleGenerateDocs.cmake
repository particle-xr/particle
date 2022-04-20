find_package(Doxygen REQUIRED)

doxygen_add_docs(particle-docs ${PROJECT_SOURCE_DIR} ALL)

install(DIRECTORY ${PROJECT_BINARY_DIR}/html/
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
