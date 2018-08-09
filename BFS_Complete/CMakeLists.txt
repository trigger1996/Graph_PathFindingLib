cmake_minimum_required(VERSION 3.0)
project(bfs_w_ui)

add_definitions(-std=c++11)

find_package(OpenCV 2.4.9 REQUIRED)
find_package(Eigen3 3.1.0 REQUIRED)

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
${EIGEN3_INCLUDE_DIR}
${Pangolin_INCLUDE_DIRS}
../graph_lib/include
)

link_directories(
../graph_lib/build
)

add_executable(${PROJECT_NAME}
main.cpp
node.cpp
graph_simple_w_bfs.cpp
graph_weighted_w_bfs.cpp
)

target_link_libraries(${PROJECT_NAME}
${OpenCV_LIBS}
${EIGEN3_LIBS}
simple_graph_libs
)
