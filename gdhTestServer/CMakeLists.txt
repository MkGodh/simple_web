cmake_minimum_required(VERSION 3.27)
project(gdhTestServer)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ROOT C:\\boost_1_88_0)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 mswsock)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)