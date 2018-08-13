#ifndef __Graph_Simple_w_BFS_H
#define __Graph_Simple_w_BFS_H

#include "node.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>
#include "../../graph_lib/include/graph_simple.h"

using namespace std;
using namespace cv;
using namespace Eigen;

class __graph_simple_bfs : public __graph_simple {
public:

    __graph_simple_bfs() : __graph_simple() {

    }

    __graph_simple_bfs(uint32_t x, uint32_t y) : __graph_simple(x, y) {

    }

    ~__graph_simple_bfs() {

    }

    void run_BFS();

    void draw_Img_with_Route(bool is_show);

    void draw_Img_with_Route(String winName);

    void print_Img_with_Route();

protected:

    Point2f startPos;
    Point2f endPos;

    vector<__node> bfs_q;           // bfs_quene

    vector<__node> route;

};

#endif  // __Graph_Simple_w_BFS_H
