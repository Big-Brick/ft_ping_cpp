cmake_minimum_required(VERSION 2.8)
project(testTask)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(PkgConfig)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

add_executable(testTask srcs/main.cpp includes/Poller.h srcs/IcmpPoller.cpp includes/IcmpPoller.h)

target_include_directories(testTask PRIVATE ${JSONCPP_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(testTask ${JSONCPP_LIBRARIES} ${Boost_LIBRARIES} oping pthread)
