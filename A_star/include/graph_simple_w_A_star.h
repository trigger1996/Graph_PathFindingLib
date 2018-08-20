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

typedef enum {
    _up         = 1,
    _up_right   = 2,
    _right      = 3,
    _down_right = 4,
    _down       = 5,
    _down_left  = 6,
    _left       = 7,
    _up_left    = 8,
    _no_dir     = 9,
} __dir_flag;


class __node_A_star : public __node {
public:
    /// 构造函数
    __node_A_star() : __node() {                                // 设置一个缺省的
        _F = _G = _H = 0.;
    }

    __node_A_star(Point2f pt, Point2f pt_past, int32_t map_x, int32_t map_y) :
        __node(pt, pt_past, map_x, map_y) {
        _F = _G = _H = 0.;
    }

    __node_A_star(int32_t pt, int32_t pt_past, int32_t map_x, int32_t map_y) :
        __node(pt, pt_past, map_x, map_y) {
        _F = _G = _H = 0.;
    }

    __node_A_star(Point2f pt, int32_t pt_past, int32_t map_x, int32_t map_y) :
        __node(pt, pt_past, map_x, map_y) {
        _F = _G = _H = 0.;
    }

    __node_A_star(int32_t pt, Point2f pt_past, int32_t map_x, int32_t map_y) :
        __node(pt, pt_past, map_x, map_y) {
        _F = _G = _H = 0.;
    }

    /// 析构函数
    ~__node_A_star() {

    }

    /// 更新距离
    void G(double in) {
        _G = in;
        _F = _G + _H;
    }

    void H(double in) {
        _H = in;
        _F = _G + _H;
    }

    /// 读取距离
    double F()        { return _F; }
    double G()        { return _G; }
    double H()        { return _H; }

    /// 运算符重载
    inline __node_A_star& operator =(__node_A_star src) {       // 重载赋值运算符
        this->_grid    = src.grid();
        this->_grid_d  = src.grid_d();
        this->_grid_p  = src.grid_p();
        this->_grid_pd = src.grid_pd();

        this->_dist_2_past  = src.dist_2_pass();
        this->_dist_2_start = src.dist_2_start();

        this->_F = src.F();
        this->_G = src.G();
    }

    inline bool operator ==(__node src) {                       // 重载相等判断运算符
        if ((this->_grid    == src.grid() ||                    // &&
             this->_grid_d  == src.grid_d()) &&
            (this->_grid_p  == src.grid_p() ||                  // &&
             this->_grid_pd == src.grid_pd()))
            return true;
        else
            return false;
    }

private:

    double _F;                                                  // 该点的总开销值
    double _G, _H;                                              // G为从原点经过各个点到当前位置的开销，欧式距离，H为当前点到终点的估计距离，曼哈顿距离

};

class __graph_simple_A_star : public __graph_simple {
public:

/// 构造函数
    __graph_simple_A_star() : __graph_simple() {                            // 初始化空图
        _startPos = Point2f(0, 0);
        _endPos   = Point2f(x_max, y_max);

    }

    __graph_simple_A_star(uint32_t x, uint32_t y) : __graph_simple(x, y) {  // 初始化制定大小的图，同时以(0, 0)点作为起点
        _startPos = Point2f(0, 0);
        _endPos   = Point2f(x_max, y_max);


    }

    __graph_simple_A_star(MatrixXd map_in, Point2f start, Point2f end) {    // 以外部给入的矩阵、起点和终点初始化图
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

        route     = new __node_q(x_max, y_max);

        calc_AdjacencyMatrix();
    }

/// 析构函数
    ~__graph_simple_A_star() {
        graphMat.resize(0, 0);

        x_max = 0;
        y_max = 0;

        delete route;
    }

/// 获得、写入数据
    Point2f startPos() { return _startPos; }                                // 读取路径起点

    Point2f endPos()   { return _endPos;   }                                // 读取路径终点

    void set_startPos(Point2f in) { _startPos = in; }                       // 设置路径起点

    void set_endPos(Point2f in)   { _endPos = in;   }                       // 设置路径终点

    void get_Route(vector<__node> &out) {                                   // 读取路径
        out.clear();
        for (int i = 0; i < route->get_Quene().size(); i++)
            out.push_back(route->get_Quene()[i]);
    }

/// 核心程序
    void run_Astar();                                                       // 执行A*算法

/// 绘图程序
    void draw_Img_with_Route(bool is_show);                                 // 作图，同时作出A*算出的路径，可选是否显示，固定文件名

    void draw_Img_with_Route(char winName[]);                               // 作图，同时作出A*算出的路径，必定显示，可选文件名

    void print_Img_with_Route();                                            // 使用终端打印出图以及A*算出的路径

protected:

    Point2f _startPos;                                                      // 路径起点
    Point2f _endPos;                                                        // 路径终点

    vector<__node_A_star> openList;                                         // Open列表
    vector<__node_A_star> closeList;                                        // Close列表，这两个表的定义详见A*算法的文档

    __node_q *route;                                                        // 路径列表

};

#endif  // __Graph_Simple_w_BFS_H
