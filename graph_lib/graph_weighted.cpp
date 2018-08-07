#include "include/graph_weighted.h"

/// 核心数学功能
MatrixXd __graph_weighted::calc_AdjacencyMatrix() {
    const int l = img_grid_len;
    int32_t x0, y0, x1, y1;

    D.resize(x_max * y_max, x_max * y_max);
    D.fill(0);

    for (y0 = 0; y0 < graphMat.rows(); y0++) {
        for (x0 = 0; x0 < graphMat.cols(); x0++) {
            if(graphMat(y0, x0) != 0) {
                for (y1 = 0; y1 < graphMat.rows(); y1++) {
                    for (x1 = 0; x1 < graphMat.cols(); x1++) {
                        if(graphMat(y1, x1) != 0) {
                            uint32_t dx, dy;
                            dx = abs(x1 - x0);
                            dy = abs(y1 - y0);
                            if (dx + dy == 1 || (dx == 1 && dy == 1))
                                D(x0 + y0 * x_max, x1 + y1 * x_max) = (graphMat(y0, x0) + graphMat(y1, x1)) / 2.;   // 这边的值用目标和当前点的平均
                        }
                    }
                }
            }
        }
    }

    return D;
}

MatrixXd __graph_weighted::calc_AdjMat_Reciprocal() {
    int x, y;

    D_rec = calc_AdjacencyMatrix();

    for (y = 0; y < D_rec.rows(); y++) {
        for (x = 0; x < D_rec.cols(); x++) {
            if (D_rec(y, x) != 0)
                D_rec(y, x) = 1. / D_rec(y, x);
        }
    }

    return D_rec;
}

void __graph_weighted::calc_Maxval() {
    int x, y;

    maxval = -1e6;
    for (y = 0; y < graphMat.rows(); y++) {
        for (x = 0; x < graphMat.cols(); x++) {
            if (graphMat(y, x) > maxval && graphMat(y, x) != 0.)
                maxval = graphMat(y, x);
        }
    }
}

void __graph_weighted::calc_Minval() {
    int x, y;

    minval = 1e6;
    for (y = 0; y < graphMat.rows(); y++) {
        for (x = 0; x < graphMat.cols(); x++) {
            if (graphMat(y, x) < minval && graphMat(y, x) != 0.)
                minval = graphMat(y, x);
        }
    }
}

/// 显示功能
void __graph_weighted::print() {
    cout << graphMat << endl << endl;
}

void __graph_weighted::draw(bool is_show) {
    const int l = img_grid_len;

    int x, y;
    uint8_t h, s, v;
    Mat zero(Size(x_max * l + 1, y_max * l + 1), CV_8UC3, Scalar(255, 255, 255));       // 加1是为了边框

    img.release();
    img = zero.clone();
    zero.release();

    // 采用HSV划分颜色
    s = 200;
    v = 180;
    cvtColor(img, img, CV_BGR2HSV);                                                     // https://www.cnblogs.com/wangyblzu/p/5710715.html
                                                                                        // H: 0~180, S,V: 0~255

    // 绘制网格
    for (y = 0; y < img.rows; y += l) {
        line(img, Point(0, y), Point(img.cols, y), Scalar(0, 0, 0));
    }
    for (x = 0; x < img.cols; x += l) {
        line(img, Point(x, 0), Point(x, img.rows), Scalar(0, 0, 0));
    }
    line(img, Point(0, y - 1), Point(img.cols, y - 1), Scalar(0, 0, 0));                // 补最右、最下两条线
    line(img, Point(x - 1, 0), Point(x - 1, img.rows), Scalar(0, 0, 0));

    // 根据矩阵填充画图
    for (y = 0; y < graphMat.rows(); y++) {
        for (x = 0; x < graphMat.cols(); x++) {

                Rect select;//声明矩形
                select.x = x * l + 1;
                select.y = y * l + 1;
                select.width  = l - 1;
                select.height = l - 1;

                // 计算颜色
                // 为了好看这边代码可以多写一点
                if (graphMat(y, x) == 0) {
                    rectangle(img, select, Scalar(0, 5, 80), -1, 4, 0);                 // HSV
                }
                else {
                    // 线性化区间
                    double val;
                    val = (graphMat(y, x) - minval) / (maxval - minval);                // 数值归一化
                    h = val * 160;                                                      // HSV满值180，但是由于180和0的颜色差不多，为了区别，这部故意不满
                    rectangle(img, select, Scalar(h, s, v), -1, 4, 0);                  // 彩色矩阵
                }
            }
        }

    cvtColor(img, img, CV_HSV2BGR);
    if (is_show) {
        namedWindow("graph_weighted_test", WINDOW_NORMAL);
        imshow("graph_weighted_test", img);
        waitKey(1);
    }
}

void __graph_weighted::draw(String winName, bool is_show) {
    draw(false);

    if (is_show) {
        namedWindow(winName, WINDOW_NORMAL);
        imshow(winName, img);
        waitKey(1);
    }
}

void __graph_weighted::show_Img(String winName) {

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}
