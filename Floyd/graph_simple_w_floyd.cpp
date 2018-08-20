#include "include/graph_simple_w_floyd.h"

/// 核心代码
MatrixXd __graph_simple_floyd::run_Floyd() {

    const int pt_max = x_max * y_max;

    int i, x, y;

    for (i = 0; i < pt_max; i++) {
        for (y = 0; y < pt_max; y++) {
            for (x = 0; x < pt_max; x++) {
                if (matD_f(y, x) > matD_f(i, x) + matD_f(y, i)) {
                    /// 算法主体部分
                    matD_f(y, x) = matD_f(i, x) + matD_f(y, i);

                    /// 更新路径
                    vector<int32_t> route_xt, route_yt;
                    route_xt = matPath[i][x];
                    route_yt = matPath[y][i];
                    matPath[y][x].clear();
                    for (int j = 0; j < route_yt.size(); j++)
                        matPath[y][x].push_back(route_yt[j]);
                    for (int j = 1; j < route_xt.size(); j++)
                        matPath[y][x].push_back(route_xt[j]);
                }

            }
        }
    }

    /// 更新起点、终点路径
    int32_t start_d = GraphGrid_2_AdjMatGrid(this, _startPos);
    int32_t end_d   = GraphGrid_2_AdjMatGrid(this, _endPos);
    route_d.clear();
    route_d = matPath[start_d][end_d];                                  // 邻接矩阵坐标
    route.clear();
    for (size_t j = 0; j < route_d.size(); j++)
        route.push_back(AdjMatGrid_2_GraphGrid(this, route_d[j]));      // 笛卡尔坐标

    cout << "Distance: " << matD_f(start_d, end_d) << endl;

    return matD_f;
}

/// 显示代码
void __graph_simple_floyd::print_RouteGrid(int32_t start_d, int32_t end_d) {
    vector<int32_t> route_dt;
    route_dt = matPath[start_d][end_d];
    for (size_t i = 0; i < route_dt.size(); i++)
        cout << AdjMatGrid_2_GraphGrid(this, route_dt[i]) << endl;

}

void __graph_simple_floyd::print_RouteGrid(Point2f start, Point2f end) {
    int32_t start_d, end_d;

    start_d = GraphGrid_2_AdjMatGrid(this, start);
    end_d   = GraphGrid_2_AdjMatGrid(this, end);

    print_RouteGrid(start_d, end_d);
}

void __graph_simple_floyd::print_RouteGrid() {
    for (size_t i = 0; i < route.size(); i++)
        cout << route[i] << endl;
}

void __graph_simple_floyd::draw_Img_with_Route(bool is_show) {
    const int32_t l = img_grid_len;
    int i;

    draw(false);


    /// 画出路径点
    for (i = 0; i < route.size(); i++) {
        Point2i way_pt(route[i].x, route[i].y);
        way_pt.x = way_pt.x * l + 5;
        way_pt.y = way_pt.y * l + 5;

        // 起点
        if (i == 0)
            circle(img, way_pt, 5, Scalar(33, 248, 146), -1);   // BGR
        else if (i == route.size() - 1)
            circle(img, way_pt, 5, Scalar(240, 33, 248), -1);
        else
            circle(img, way_pt, 3, Scalar(244, 36, 78));
    }


    /// 画出路线
    for (i = 1; i < route.size(); i++) {
        Point2i way_pt(route[i].x, route[i].y);
        way_pt.x = way_pt.x * l + 5;
        way_pt.y = way_pt.y * l + 5;

        Point2i way_pt_last(route[i - 1].x, route[i - 1].y);
        way_pt_last.x = way_pt_last.x * l + 5;
        way_pt_last.y = way_pt_last.y * l + 5;

        line(img, way_pt_last, way_pt, Scalar(40, 155, 240), 2);

    }

    /// 是否显示
    if (is_show) {
        namedWindow("graph_w_floyd", WINDOW_NORMAL);
        imshow("graph_w_floyd", img);
        waitKey(1);
    }
}

void __graph_simple_floyd::draw_Img_with_Route(char winName[]){
    draw_Img_with_Route(false);

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}

/// 私有类辅助代码
void __graph_simple_floyd::reset_PathMat() {

    const int l = x_max * y_max;
    int x, y;

    matPath.clear();
    for (y = 0; y < l; y++) {
        vector<vector<int32_t>> line_t;
        for (x = 0; x < l; x++) {
            vector<int32_t> element_t;
            element_t.push_back(y);
            element_t.push_back(x);
            line_t.push_back(element_t);
        }
        matPath.push_back(line_t);
    }
}

void __graph_simple_floyd::adjMatrix_2_adjMatrix_Floyd() {

    const int l = x_max * y_max;
    int x, y;

    matD_f.setZero(l, l);
    for (y = 0; y < l; y++) {
        for (x = 0; x < l; x++) {

            if (y == x)
                matD_f(y, x) = 0;
            else if (D(y, x) == 0)
                matD_f(y, x) = 1e6;
            else
                matD_f(y, x) = calc_Dist_Euclidean(AdjMatGrid_2_GraphGrid(this, y),
                                                   AdjMatGrid_2_GraphGrid(this, x));
        }
    }
}

