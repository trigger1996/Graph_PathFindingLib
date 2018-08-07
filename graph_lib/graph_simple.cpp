#include "include/graph_simple.h"

/// 核心数学功能
MatrixXd __graph_simple::calc_AdjacencyMatrix() {
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
                                D(x0 + y0 * x_max, x1 + y1 * x_max) = 1;
                        }
                    }
                }
            }
        }
    }

    return D;
}

MatrixXd __graph_simple::calc_AdjMat_Reciprocal() {
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

/// 显示功能
void __graph_simple::print() {
    cout << graphMat << endl << endl;
}

void __graph_simple::draw(bool is_show) {
    const int l = img_grid_len;

    int x, y;
    Mat zero(Size(x_max * l + 1, y_max * l + 1), CV_8UC3, Scalar(255, 255, 255));       // 加1是为了边框

    img.release();
    img = zero.clone();
    zero.release();

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
            if (graphMat(y, x) == 0) {
                Rect select;//声明矩形
                select.x = x * l + 1;
                select.y = y * l + 1;
                select.width  = l - 1;
                select.height = l - 1;
                rectangle(img, select, Scalar(128, 128, 128), -1, 4, 0);
            }
        }
    }

    if (is_show) {
        namedWindow("graph_test", WINDOW_NORMAL);
        imshow("graph_test", img);
        waitKey(1);
    }
}

void __graph_simple::draw(String winName, bool is_show) {
    draw(false);

    if (is_show) {
        namedWindow(winName, WINDOW_NORMAL);
        imshow(winName, img);
        waitKey(1);
    }
}

void __graph_simple::show_Img(String winName) {

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}
