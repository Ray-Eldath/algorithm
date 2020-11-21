cmake_minimum_required(VERSION 3.16)
project(algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(ccf2019121 ccf2019121.cpp)
add_executable(ccf2019122 ccf2019122.cpp)
add_executable(ccf2019091 ccf2019091.cpp)
add_executable(ccf2020061 ccf2020061.cpp)

add_executable(1-16 1-16.cpp)
add_executable(1-23 1-23.cpp)
add_executable(1-29 1-29.cpp)
add_executable(1-13 1-13.cpp)

add_executable(2 utils.h 2.h 2.cpp)
target_compile_options(2 PRIVATE -DDEBUG)

add_executable(2-35 utils.h 2-34.h 2-35.cpp)
add_executable(2-36 utils.h 2-34.h 2-36.cpp)
add_executable(2-22 2-22.cpp)
add_executable(deduplicate deduplicate.cpp)
add_executable(3 utils.h 3.h 3.cpp)
add_executable(3-19 3.h 3-19.cpp)
add_executable(4 4.h 4.cpp)
add_executable(4.3.3 4.h 4.3.3.cpp)
add_executable(4.4.2 4.h 4.4.2.cpp)
add_executable(4.4.3 4.h 4.4.3.cpp)
add_executable(5 5.h 5.cpp)

add_executable(5.5.3 5.h 5.5.3.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/freq
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(5-30 5-30.cpp)
add_executable(6 6.h 6.cpp)
add_executable(6-8 6.h 6-8.cpp)

add_executable(leetcode224 leetcode224.cpp)
add_executable(leetcode51 leetcode51.cpp)
add_executable(leetcode140 leetcode140.cpp)
add_executable(leetcode139 leetcode139.cpp)
add_executable(leetcode208 leetcode208.cpp)