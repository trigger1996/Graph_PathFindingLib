#ifndef __Graph_Simple_H
#define __Graph_Simple_H

#include "misc.hpp"
#include "graph_abstract.hpp"

/// 无权无向图
class __graph_simple : public __graph_abstract {
public:
    __graph_simple() : __graph_abstract() {

    }

    __graph_simple(uint32_t x, uint32_t y) : __graph_abstract(x, y) {

    }

    ~__graph_simple() {

    }

    double get_Pixel(uint32_t x, uint32_t y) override {          // 获得某一个像素点的值
        if (x > x_max || y > y_max)
            return -1.;
        else
            return graphMat(y, x);
    }

    bool set_Pixel(double in, uint32_t x, uint32_t y) override { // 强制设置某一个像素点
        if (x > x_max || y > y_max)
            return false;
        else {
            if (in != 0.0f)
                graphMat(y, x) = 1;
            else
                graphMat(y, x) = 0;
            return true;
        }
    }

    void set_graphMat(MatrixXd in) override {                   // 设置矩阵

        int x, y;

        graphMat = in;
        x_max = in.cols();
        y_max = in.rows();

        for (y = 0; y < graphMat.rows(); y++) {
            for (x = 0; x < graphMat.cols(); x++) {
                if (graphMat(y, x) == 0.0f)
                    graphMat(y, x) = 0.0f;
                else
                    graphMat(y, x) = 1.0f;
            }
        }
    }

    MatrixXd calc_AdjacencyMatrix() override;                    // 计算邻接矩阵

    MatrixXd calc_AdjMat_Reciprocal() override;                  // 计算邻接矩阵的倒数

    void print() override;                                       // 终端打印

    void draw(bool is_show) override;                            // 用OpenCV画出来，如果用is_show显示，窗口名是固定的，graph_test

    virtual void draw(String winName, bool is_show) override;    // 用OpenCV画出来，名称自定

    virtual void show_Img(String winName) override;              // 用OpenCV，只显示图片，不更新图像


protected:

};

#endif // __Graph_Simple_H

