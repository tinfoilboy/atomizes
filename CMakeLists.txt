cmake_minimum_required (VERSION 3.0)
project (atomizes)

set (CMAKE_CXX_STANDARD 11)
set (ATOMIZES_TEST_SOURCE ${PROJECT_SOURCE_DIR}/tests/main.cpp ${PROJECT_SOURCE_DIR}/tests/message_tests.cpp ${PROJECT_SOURCE_DIR}/tests/parser_tests.cpp)

add_library (atomizes INTERFACE)

target_include_directories (atomizes INTERFACE include/)

option (ATOMIZES_ENABLE_TESTS "Build tests for atomizes?" ON)

if (ATOMIZES_ENABLE_TESTS)
    enable_testing ()
    add_executable (atomizes_test ${ATOMIZES_TEST_SOURCE})
    target_link_libraries (atomizes_test atomizes)
    add_test (NAME AtomizesTests COMMAND atomizes_test)
endif ()