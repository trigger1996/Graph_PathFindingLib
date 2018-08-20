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

class __graph_simple_dijkstra : public __graph_simple {
public:

/// 构造函数
    __graph_simple_dijkstra() : __graph_simple() {                              // 初始化空图
        _startPos = Point2f(0, 0);
        _endPos   = Point2f(x_max, y_max);

        route         = new __node_q(x_max, y_max);
        list_visited  = new __node_q(x_max, y_max, _startPos);
        list_to_visit = new __node_q(x_max, y_max);
    }

    __graph_simple_dijkstra(uint32_t x, uint32_t y) : __graph_simple(x, y) {    // 初始化制定大小的图，同时以(0, 0)点作为起点
        _startPos = Point2f(0, 0);
        _endPos   = Point2f(x_max, y_max);

        route         = new __node_q(x_max, y_max);
        list_visited  = new __node_q(x_max, y_max, _startPos);
        list_to_visit = new __node_q(x_max, y_max);
    }

    __graph_simple_dijkstra(MatrixXd map_in, Point2f start, Point2f end) {      // 以外部给入的矩阵、起点和终点初始化图
        int x, y;

        x_max = map_in.cols();
        y_max = map_in.rows();

        graphMat.resize(map_in.rows(), map_in.cols());
        graphMat.fill(0);
        for (y = 0; y < map_in.cols(); y++) {
            for (x = 0; x < map_in.rows(); x++) {
                graphMat(y, x) = map_in(y, x);
            }
        }

        _startPos = start;
        _endPos   = end;

        route         = new __node_q(x_max, y_max);
        list_visited  = new __node_q(x_max, y_max, _startPos);
        list_to_visit = new __node_q(x_max, y_max);

        calc_AdjacencyMatrix();
    }

/// 析构函数
    ~__graph_simple_dijkstra() {
        graphMat.resize(0, 0);

        x_max = 0;
        y_max = 0;

        delete route;
        delete list_visited;
        delete list_to_visit;
    }

/// 获得、写入数据
    Point2f startPos() { return _startPos; }                                    // 读取路径起点

    Point2f endPos()   { return _endPos;   }                                    // 读取路径终点

    void set_startPos(Point2f in) { _startPos = in; }                           // 设置路径起点

    void set_endPos(Point2f in)   { _endPos = in;   }                           // 设置路径终点

    void get_Route(vector<__node> &out) {                                       // 读取路径
        out.clear();
        for (int i = 0; i < route->get_Quene().size(); i++)
            out.push_back(route->get_Quene()[i]);
    }

/// 核心程序
    void run_Dijkstra();                                                        // 执行Dijkstra算法

/// 绘图程序
    void draw_Img_with_Route(bool is_show);                                     // 作图，同时作出Dijkstra算出的路径，可选是否显示，固定文件名

    void draw_Img_with_Route(char winName[]);                                   // 作图，同时作出Dijkstra算出的路径，必定显示，可选文件名

    void print_Img_with_Route();                                                // 使用终端打印出图以及Dijkstra算出的路径

protected:

    Point2f _startPos;                                                          // 路径起点
    Point2f _endPos;                                                            // 路径终点

    __node_q *list_visited;                                                     // 已遍历集合，即论文中的S集合
    __node_q *list_to_visit;                                                    // 未遍历集合，集论文中的Q集合
    vector<double> dist;                                                        // 距离列表

    __node_q *route;
};

#endif  // __Graph_Simple_w_BFS_H
