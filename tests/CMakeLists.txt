cmake_minimum_required(VERSION 3.12)
project(tests)

set(SOURCE_FILES tests_main.cpp)

add_executable(tests ${SOURCE_FILES})

target_link_libraries(tests stdc++fs ${MY_STATIC_LIBS})