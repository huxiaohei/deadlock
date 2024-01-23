cmake_minimum_required(VERSION 3.5)

project(LOCKCHECK VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -rdynamic -g -ggdb -fcoroutines -std=c++20 -Wall -Wno-deprecated -Werror -Wno-unused-function")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -rdynamic -fcoroutines -std=c++20 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

message(STATUS "LIBRARY_OUTPUT_PATH: ${LIBRARY_OUTPUT_PATH}")
message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")

set(LIB_SRC
    src/graph.cc    
)
add_library(LOCKCHECK SHARED ${LIB_SRC}) 

set(LIBS
    LOCKCHECK
)


aux_source_directory(tests TEST_SRC_LIST)
foreach(test_src ${TEST_SRC_LIST})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} ${PROTO_SRC_LIST})
    target_link_libraries(${test_name} ${LIBS})
endforeach()