#ifndef __Graph_Simple_w_Floyd_H
#define __Graph_Simple_w_Floyd_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "../graph_lib/include/graph_simple.h"

using namespace std;
using namespace cv;
using namespace Eigen;

class __graph_simple_floyd : public __graph_simple {
public:

    __graph_simple_floyd() : __graph_simple() {
        calc_AdjacencyMatrix();

        adjMatrix_2_adjMatrix_Floyd();
        reset_PathMat();
    }

    __graph_simple_floyd(uint32_t x, uint32_t y) : __graph_simple(x, y) {
        calc_AdjacencyMatrix();

        adjMatrix_2_adjMatrix_Floyd();
        reset_PathMat();
    }

    __graph_simple_floyd(MatrixXd mat_in, Point2f start, Point2f end) {
        x_max = mat_in.cols();
        y_max = mat_in.rows();

        graphMat.setZero(y_max, x_max);
        for (int y = 0; y < mat_in.rows(); y++) {
            for (int x = 0; x < mat_in.cols(); x++) {
                graphMat(y, x) = mat_in(y, x);
            }
        }
        _startPos = start;
        _endPos   = end;

        calc_AdjacencyMatrix();

        adjMatrix_2_adjMatrix_Floyd();
        reset_PathMat();
    }

    ~__graph_simple_floyd() {
        matD_f.resize(0, 0);
        matPath.clear();

        route_d.clear();
        route.clear();

        img.release();
    }

/// 起点、终点读写
    Point2f startPos() { return _startPos; }
    Point2f endPos()   { return _endPos;   }

    Point2f startPos(Point2f in) { _startPos = in; }
    Point2f endPos(Point2f in)   { _endPos   = in; }

    Point2f startPos(int32_t x, int32_t y) { _startPos = Point2f(x, y); }
    Point2f endPos(int32_t x, int32_t y)   { _endPos   = Point2f(x, y); }

/// 路径读写
    vector<vector<vector<int32_t>>> get_path_2_All() { return matPath; }        // 返回所有的路径

    vector<Point2f> get_Route()                      { return route;   }        // 返回起点到终点的路径，笛卡尔坐标


/// 核心代码
    MatrixXd run_Floyd();                                                       // 运行Floyd算法

/// 显示代码
    void print_RouteGrid(int32_t start_d, int32_t end_d);                       // 打印出整条路径的坐标点，输入邻接矩阵坐标

    void print_RouteGrid(Point2f start,   Point2f end);                         // 打印出整条路径的坐标点，输入笛卡尔坐标

    void print_RouteGrid();                                                     // 打印起点到终点的坐标点

    void draw_Img_with_Route(bool is_show);                                     // 作图，同时作出Floyd算出的路径，可选是否显示，固定文件名

    void draw_Img_with_Route(char winName[]);                                   // 作图，同时作出Floyd算出的路径，必定显示，可选文件名

protected:

    Point2f _startPos;
    Point2f _endPos;

    MatrixXd matD_f;                                                            // 由邻接矩阵改写的邻接矩阵
    vector<vector<vector<int32_t>>> matPath;                                    // 路径二维矩阵，每个矩阵元素都是一个队列

    vector<int32_t>                 route_d;                                    // 起点到终点的路径，邻接矩阵坐标
    vector<Point2f>                 route;                                      // 起点到终点的路径，笛卡尔坐标

    void reset_PathMat();                                                       // 重置路径矩阵

    void adjMatrix_2_adjMatrix_Floyd();                                         // 邻接矩阵转换为Floyd算法使用的邻接矩阵

};


#endif  // __Graph_Simple_w_Floyd_H
