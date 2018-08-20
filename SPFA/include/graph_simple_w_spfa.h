#ifndef __Graph_Simple_w_SPFA_H
#define __Graph_Simple_w_SPFA_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Dense>

#include <../../graph_lib/include/graph_simple.h>

using namespace std;
using namespace cv;
using namespace Eigen;


class __graph_simple_spfa : public __graph_simple {
public:
/// 构造函数
    __graph_simple_spfa() : __graph_simple() {

    }

    __graph_simple_spfa(uint32_t x, uint32_t y) : __graph_simple(x, y) {

    }

    __graph_simple_spfa(MatrixXd map_in, Point2i start, Point2i end) {
        int x, y;
        graphMat.setZero(map_in.rows(), map_in.cols());
        for (y = 0; y < map_in.rows(); y++) {
            for (x = 0; x < map_in.cols(); x++) {
                graphMat(y, x) = map_in(y, x);
            }
        }
        x_max = map_in.cols();
        y_max = map_in.rows();

        // 记录起点、终点
        _startPos = start;
        _endPos   = end;

        // 计算邻接矩阵
        calc_AdjacencyMatrix();

    }

/// 路径起点、终点读写函数
    Point2i startPos() { return _startPos; }
    Point2i endPos()   { return _endPos;   }

    void startPos(Point2i in) { _startPos = in; }
    void endPos(Point2i   in) { _endPos   = in; }


/// 析构函数
    ~__graph_simple_spfa() {

    }

/// 核心程序
    void run_SPFA();

/// 显示程序

    void draw_Img_with_Route(bool is_show);                                     // 作图，同时作出SPFA算出的路径，可选是否显示，固定文件名

    void draw_Img_with_Route(char winName[]);                                   // 作图，同时作出SPFA算出的路径，必定显示，可选文件名


protected:

    MatrixXd Dw;                                                                    // 带权重的邻接矩阵

    Point2i _startPos, _endPos;                                                     // 路径起点、终点

    vector<int32_t> v;                                                              // 用于松弛操作的顶点队列

    vector<double> dist;                                                            // 距离列表

    vector<Point2i> route;                                                          // 路径列表

    void adjMat_2_Weighted();                                                       // 邻接矩阵转换带权重的邻接矩阵
};


#endif  // __Graph_Simple_w_SPFA_H

