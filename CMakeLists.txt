cmake_minimum_required(VERSION 4.2)
project(BVA_test)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

add_executable(BVA_test main.cpp)

target_link_libraries(BVA_test PRIVATE ${OpenCV_LIBS})