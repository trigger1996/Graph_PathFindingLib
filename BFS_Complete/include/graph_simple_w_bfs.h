#ifndef __Graph_Simple_w_BFS_H
#define __Graph_Simple_w_BFS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>
#include "../../graph_lib/include/graph_simple.h"

class __graph_simple_bfs : public __graph_simple {
public:

    __graph_simple_bfs() : __graph_simple() {

    }

    __graph_simple_bfs(uint32_t x, uint32_t y) : __graph_simple(x, y) {

    }

    ~__graph_simple_bfs() {

    }

protected:

};

#endif  // __Graph_Simple_w_BFS_H
