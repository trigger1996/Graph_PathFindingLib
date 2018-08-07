cmake_minimum_required(VERSION 3.0)
project(simple_graph_libs)

add_definitions(-std=c++11)

find_package(OpenCV 2.4.9 REQUIRED)
find_package(Eigen3 3.1.0 REQUIRED)

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
${EIGEN3_INCLUDE_DIR}
${Pangolin_INCLUDE_DIRS}
)

add_executable(graph_test
graph_simple.cpp
graph_weighted.cpp
route.cpp
main.cpp
)

target_link_libraries(graph_test
${OpenCV_LIBS}
${EIGEN3_LIBS}
)

add_library(${PROJECT_NAME} SHARED
graph_simple.cpp
graph_weighted.cpp
route.cpp
)
