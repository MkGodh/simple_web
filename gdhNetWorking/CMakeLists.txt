cmake_minimum_required(VERSION 3.28)
project(gdhNetWorking)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

file(GLOB_RECURSE SOURCES
        src/*.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(gdhNetWorking
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${BOOST_INCLUDE_DIRS}
        PRIVATE

)

target_link_libraries(gdhNetWorking
        PUBLIC
        Boost::boost
)
