cmake_minimum_required(VERSION 3.23)
project(C__Learn)

add_compile_options(-pthread)

set(CMAKE_CXX_STANDARD 17)
find_package(Catch2 REQUIRED)

set(COPY_SRC src/copy.cpp)
add_executable(copy ${COPY_SRC})
target_include_directories(copy PUBLIC include)
target_link_libraries(copy PRIVATE Catch2::Catch2)

add_executable(tests tests/copy.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PUBLIC include)


