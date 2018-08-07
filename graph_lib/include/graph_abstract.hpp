#ifndef __Graph_Abstract_HPP
#define __Graph_Abstract_HPP

#include "misc.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace Eigen;
using namespace cv;

///  抽象类，定义基本接口
class __graph_abstract {
public:

    __graph_abstract() {
        graphMat.resize(1, 1);
        graphMat.fill(0);

        x_max = y_max = 1;
        }

    __graph_abstract(uint32_t x, uint32_t y) {
        graphMat.resize(y, x);
        graphMat.fill(0);

        x_max = x;
        y_max = y;
    }

    ~__graph_abstract() {
        graphMat.resize(0, 0);

        x_max = 0;
        y_max = 0;
    }

/// 实函数
    MatrixXd get_graphMat()   { return graphMat; }                          // 读取矩阵

    MatrixXd get_AdjMat()     { return D;}                                  // 读取邻接矩阵

    MatrixXd get_AdjMat_Rec() { return D_rec; }                             // 读取邻接矩阵倒数

    Mat get_Img() { return img.clone(); }                                   // 读取图像矩阵

    uint32_t get_x_max() {                                                  // 返回矩阵列数
        x_max = graphMat.cols();
        return x_max;
    }

    uint32_t get_y_max() {                                                  // 返回矩阵行数
        y_max = graphMat.rows();
        return y_max;
    }

/// 虚函数，用作接口
    virtual double get_Pixel(uint32_t x, uint32_t y) = 0;                   // 获得某一个像素点的值

    virtual void set_graphMat(MatrixXd in) = 0;                             // 设置矩阵

    virtual bool set_Pixel(double in, uint32_t x, uint32_t y) = 0;          // 强制设置某一个像素点

    virtual MatrixXd calc_AdjacencyMatrix() = 0;                            // 计算邻接矩阵

    virtual MatrixXd calc_AdjMat_Reciprocal() = 0;                          // 计算邻接矩阵的倒数

    virtual void print() {                                                  // 终端打印
        cout << graphMat << endl << endl;
    }

    virtual void draw(bool is_show) = 0;                                    // 用OpenCV画出来，如果用is_show显示，窗口名是固定的，graph_test

/// 两个升级版的画图操作
    virtual void draw(String winName, bool is_show) {                       // 用OpenCV画出来，名称自定
        draw(false);

        if (is_show) {
            namedWindow(winName, WINDOW_NORMAL);
            imshow(winName, img);
            waitKey(1);
        }
    }

    virtual void show_Img(String winName) {                                 // 用OpenCV，只显示图片，不更新图像

        namedWindow(winName, WINDOW_NORMAL);
        imshow(winName, img);
        waitKey(1);
    }

protected:

    static const int32_t img_grid_len = 10;

    MatrixXd graphMat;

    uint32_t x_max, y_max;

    MatrixXd D;                                                             // 邻接矩阵
    MatrixXd D_rec;                                                         // 邻接矩阵倒数

    Mat      img;

};

static inline Point2f AdjMatGrid_2_GraphGrid(__graph_abstract *graph, uint32_t in) {
    // 邻接矩阵中的单值坐标与图中坐标转换
    Point2f pt;
    uint32_t x_max, y_max;

    x_max = graph->get_x_max();
    y_max = graph->get_y_max();
    if (in >= x_max * y_max)
        return Point(-1., -1.);

    pt.x = in % x_max;
    pt.y = in / x_max;

    return pt;
}

static inline Vec4f AdjMatPos_2_GraphGrid2(__graph_abstract *graph, uint32_t startpos, uint32_t endpos) {
    // 邻接矩阵中的点与图中坐标转换
    // 返回值形式(x0, y0, x1, y1)
    // 其中(x0, y0)是起始点坐标，(x1, y1)是目标点坐标
    // 如果输入邻接矩阵, startpos对应y，endpos对应x
    Vec4f pt2;
    uint32_t x_max, y_max;

    x_max = graph->get_x_max();
    y_max = graph->get_y_max();
    if (startpos >= x_max * y_max || endpos >= x_max * y_max)
        return Vec4f(-1., -1., -1., -1.);

    pt2[0] = startpos % x_max;
    pt2[1] = startpos / x_max;
    pt2[2] = endpos   % x_max;
    pt2[3] = endpos   / x_max;

    return pt2;
}

static inline double calc_Dist_Manhattan(Point2f pt1, Point2f pt2) {
    return fabs(pt2.y - pt1.y) + fabs(pt2.x - pt1.x);
}

static inline double calc_Dist_Euclidean(Point2f pt1, Point2f pt2) {
    double dx, dy;
    dx = pt2.x - pt1.x;
    dy = pt2.y - pt1.y;
    return sqrt(dx * dx + dy * dy);
}

static inline double calc_Dist_Chebyshev(Point2f pt1, Point2f pt2) {
    double dx, dy;
    dx = pt2.x - pt1.x;
    dy = pt2.y - pt1.y;
    return max(dx, dy);
}

#endif  // __Graph_Abstract_HPP
