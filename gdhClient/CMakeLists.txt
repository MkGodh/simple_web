cmake_minimum_required(VERSION 3.28)
project(gdhClient)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ROOT C:\\boost_1_88_0)

add_executable(${PROJECT_NAME} main.cpp)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}
            PUBLIC
                gdhNetWorking
)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            gdhNetWorking
        PRIVATE
            ws2_32
            mswsock
)
