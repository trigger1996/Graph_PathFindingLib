#include <iostream>
#include "include/graph_simple.h"
#include "include/graph_weighted.h"
#include "include/route_xy.h"
#include "include/route_d.h"

using namespace Eigen;
using namespace cv;
using namespace std;


int main(void) {

    MatrixXd mat_test;
    MatrixXd _D, _D_rec;
    __graph_simple example_graph(10, 10);
    __graph_weighted example_graph_weighted(10, 10);
    __route_xy example_route_xy;
    __route_d  example_route_d(0);

    /// 测试内容1：从类中读取矩阵并打印
    mat_test = example_graph.get_graphMat();
    cout << mat_test << endl << endl;


    /// 测试内容2： 写入新的矩阵，并使用类中方法打印
    mat_test << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
                1, 1, 1, 1, 1, 0, 0, 1, 1, 1,
                1, 1, 1, 1, 1, 0, 0, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1;
    example_graph.set_graphMat(mat_test);
    example_graph.print();


    /// 测试内容3： 作出新矩阵的图像
    //example_graph.draw(true);
    example_graph.draw("example_graph", true);


    /// 测试内容4： 计算邻接矩阵，读取，并打印
    _D = example_graph.calc_AdjacencyMatrix();
    //cout << endl << _D << endl;


    /// 测试内容5： 计算邻接矩阵倒数
    _D_rec = example_graph.calc_AdjMat_Reciprocal();
    //cout << endl <<_D_rec << endl;


    /// 测试内容6： 有权图写入新的矩阵，并使用类中方法打印
    mat_test.resize(5, 5);
    mat_test << 10,  7,   6.5, 4.5, 1.8,
                8,   0,   0,   3,   1.5,
                6,   0,   0,   0,   1.2,
                4,   3,   2,   1,   0.8,
                1.8, 1.5, 1.2, 0.8, 0.5;
    example_graph_weighted.set_graphMat(mat_test);
    example_graph_weighted.print();


    /// 测试内容7： 有权图使用OpenCV打印
    example_graph_weighted.draw("example_graph_weighted", true);


    /// 测试内容8： 有权图打印邻接矩阵
    _D = example_graph_weighted.calc_AdjacencyMatrix();
    cout << _D << endl << endl;


    /// 测试内容9： 邻接矩阵坐标转换图中坐标
    Point pt_test;
    Vec4f pt2_test;
    pt_test  = AdjMatGrid_2_GraphGrid(&example_graph_weighted, 23);
    cout << pt_test << endl;
    pt2_test = AdjMatPos_2_GraphGrid2(&example_graph_weighted, 23, 18);
    cout << pt2_test << endl;
    cout << _D(23, 18) << endl << endl;

    /// 测试内容10： 二维坐标路线写入路线并打印
    vector<Point2f> route_temp_xy;
    route_temp_xy.push_back(Point(0, 0));
    route_temp_xy.push_back(Point(0, 1));
    route_temp_xy.push_back(Point(1, 1));
    route_temp_xy.push_back(Point(1, 2));
    route_temp_xy.push_back(Point(1, 3));
    route_temp_xy.push_back(Point(1, 4));
    example_route_xy.set_Route(route_temp_xy);
    example_route_xy.print();

    /// 测试内容11： 单坐标路线写入并打印
    vector<int32_t> route_temp_d;
    route_temp_d.push_back(1);
    route_temp_d.push_back(4);
    route_temp_d.push_back(7);
    route_temp_d.push_back(11);
    route_temp_d.push_back(25);
    route_temp_d.push_back(6);
    route_temp_d.push_back(8);
    example_route_d.set_Route(route_temp_d);
    example_route_d.print();


    /// 测试内容12： 二维坐标路线添加新的路径点
    example_route_xy.add_WayPt(Point(2, 4));
    example_route_xy.add_WayPt(Point(2, 5));
    example_route_xy.print();

    /// 测试内容13： 单坐标路线删除最末端
    example_route_d.remove_Last_WayPt();
    example_route_d.remove_Last_WayPt();
    example_route_d.print();

    //cout << 233 << endl;
    waitKey(0);
    return 0;
}
