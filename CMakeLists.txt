cmake_minimum_required(VERSION 3.23)
project(C__Learn)

set(CMAKE_CXX_STANDARD 17)


#set(COPY_HEADERS )
set(COPY_SRC copy.cpp)
add_executable(copy ${COPY_SRC})
#target_include_directories(copy ${COPY_HEADERS})

