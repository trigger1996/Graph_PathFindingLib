#include <iostream>
#include <vector>
#include <cmath>
#include <stdint.h>
#include "../graph_lib/include/graph_simple.h"
#include "../graph_lib/include/graph_weighted.h"

using namespace std;

const uint32_t l = 10;

vector<int32_t> openList_d,  closeList_d;
vector<Point2f> openList_xy, closeList_xy;

inline int32_t Pos_xy_2_D(Point2f xy);
inline void get_AdjacencyPt(MatrixXd D, int32_t pt_d, vector<int32_t> &lists);

int main() {

    MatrixXd mat_test;
    MatrixXd D;
    __graph_simple map(10, 10);

    mat_test.resize(10, 10);
    mat_test << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1;
    map.set_graphMat(mat_test);
    map.draw("example_graph", true);
    D = map.calc_AdjacencyMatrix();
    //cout << D << endl;

    Point2f startPos(0, 0);
    Point2f endPos(9, 9);
    Point2f currentPos;

    /// 第1步: 添加起点到openList
    openList_d.push_back(Pos_xy_2_D(startPos));
    openList_xy.push_back(startPos);

    currentPos = startPos;

//    while (currentPos != endPos) {
        float currentPos_D;


        currentPos_D = Pos_xy_2_D(currentPos);
        //cout << currentPos_D << endl;

        vector<int32_t> list_d;
        vector<Point2f> list_xy;

        /// 第2步: 搜索openList的点附近的点
        list_d.clear();
        list_xy.clear();
        for (int j = 0; j < openList_d.size(); j++) {
            get_AdjacencyPt(D, openList_d[j], list_d);
        }
        for (int k = 0; k < list_d.size(); k++)
            list_xy.push_back(AdjMatGrid_2_GraphGrid(&map, list_d[k]));   // 单坐标转xy

        /// 打印回显结果，调试用
        for (int k = 0; k < list_d.size(); k++)
            cout << list_xy[k] << endl;

        /// 第3步: 对找到的邻近点进行计算距离
        vector<double> f, g, val;
        for (int j = 0; j < list_xy.size(); j++) {
            f.push_back(calc_Dist_Euclidean(startPos,   list_xy[j]));
            g.push_back(calc_Dist_Manhattan(list_xy[j], endPos));
        }
        for (int j = 0; j < f.size(); j++)
            val.push_back(f[j] + g[j]);

        /// 第4步: 寻找代价最低的那个点
        int cost_minium_index = 0;
        for (int j = 0; j < val.size(); j++)
            if (val[j] < val[cost_minium_index])
                cost_minium_index = j;

        /// 打印回显结果，调试用
        cout << cost_minium_index << endl;

        /// 第5步:

//    }


    waitKey(0);
    return 0;
}

inline int32_t Pos_xy_2_D(Point2f xy) {
    return xy.x + xy.y * l;
}

inline void get_AdjacencyPt(MatrixXd D, int32_t pt_d, vector<int32_t> &lists) {
    int i;

    lists.clear();
    for (i = 0; i < D.cols(); i++) {
        if (D(pt_d, i) != 0) {
            lists.push_back(i);
        }
    }
}
