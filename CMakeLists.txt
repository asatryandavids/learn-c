cmake_minimum_required(VERSION 3.22)
project(C__Learn)

add_compile_options(-pthread)

set(CMAKE_CXX_STANDARD 17)
find_package(Catch2 REQUIRED)


find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")
else()
    message(STATUS "OpenSSL Not Found")
endif()

set(COPY_SRC
        src/copy.cpp
        src/argument_parsers/copy_argument_parser.cpp
        src/exceptions/exception_base.cpp
        src/exceptions/io_exception.cpp
        )
add_executable(copy copy_main.cpp ${COPY_SRC})
target_include_directories(copy PUBLIC include)
target_link_libraries(copy PRIVATE Catch2::Catch2)


set(TEST_SRC tests/test_helper.cpp)

# Tests
add_executable(tests tests/copy_test.cpp ${COPY_SRC} ${TEST_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(tests PUBLIC include ${OPENSSL_INCLUDE_DIR} tests/include)

# Benchmarks
add_executable(benchmarks tests/benchmark_test.cpp ${COPY_SRC} ${TEST_SRC})
target_link_libraries(benchmarks PRIVATE Catch2::Catch2WithMain OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(benchmarks PUBLIC include ${OPENSSL_INCLUDE_DIR} tests/include)


