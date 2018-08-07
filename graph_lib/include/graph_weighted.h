#ifndef __Graph_Weighted_H
#define __Graph_Weighted_H


#include "misc.hpp"
#include "graph_abstract.hpp"

/// 有权无向图
class __graph_weighted : public __graph_abstract {
public:
    __graph_weighted() : __graph_abstract() {
        maxval = minval = 0;
    }

    __graph_weighted(uint32_t x, uint32_t y) : __graph_abstract(x, y) {
        maxval = minval = 0;
    }

    ~__graph_weighted() {
        maxval = minval = 0;
    }

    double get_Maxval() { return maxval; }                          // 返回矩阵中最大的元素值

    double get_Minval() { return minval; }                          // 返回矩阵中最小的元素值


    double get_Pixel(uint32_t x, uint32_t y) override {             // 获得某一个像素点的值，注意一下超出了这边是返回0不是-1
        if (x > x_max || y > y_max)
            return 0.;
        else
            return graphMat(y, x);
    }

    bool set_Pixel(double in, uint32_t x, uint32_t y) override {    // 强制设置某一个像素点，有权图就没必要做0，1的限制
        if (x > x_max || y > y_max)
            return false;
        else {
            graphMat(y, x) = in;
            return true;
        }

        // 改变个别值后可能也导致最大，最小值改变，这边需要重设
        if (in > maxval)
            maxval = in;
        else if (in < minval)
            minval = in;
    }

    void set_graphMat(MatrixXd in) override {                       // 设置矩阵，这边也解除0，1的限制
        graphMat = in;
        x_max = in.cols();
        y_max = in.rows();

        calc_Maxval();
        calc_Minval();
    }

    MatrixXd calc_AdjacencyMatrix() override;                       // 计算邻接矩阵

    MatrixXd calc_AdjMat_Reciprocal() override;                     // 计算邻接矩阵的倒数

    void print() override;                                          // 终端打印

    void draw(bool is_show) override;                               // 用OpenCV画出来，如果用is_show显示，窗口名是固定的，graph_test

    virtual void draw(String winName, bool is_show) override;       // 用OpenCV画出来，名称自定

    virtual void show_Img(String winName) override;                 // 用OpenCV，只显示图片，不更新图像


protected:
    double maxval, minval;

    void calc_Maxval();

    void calc_Minval();
};


#endif // __Graph_Weighted_H

