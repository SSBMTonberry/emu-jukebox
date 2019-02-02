cmake_minimum_required(VERSION 3.12)
project(tests)

set(SOURCE_FILES tests_main.cpp)

add_executable(tests ${SOURCE_FILES} ${FMT_SOURCE_FILES})

if(LINUX)
    target_link_libraries(tests stdc++fs png ${MY_STATIC_LIBS})
elseif(WIN32)
    if(MSVC)
        target_link_libraries(tests ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        target_link_libraries(tests stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    endif()
elseif(APPLE)
    target_link_libraries(tests stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_DYNAMIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
endif()