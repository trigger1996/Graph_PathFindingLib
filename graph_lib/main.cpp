#include <iostream>
#include "include/graph_simple.h"
#include "include/graph_weighted.h"

using namespace Eigen;
using namespace cv;
using namespace std;


int main(void) {

    MatrixXd mat_test;
    MatrixXd _D, _D_rec;
    __graph_simple example_graph(10, 10);
    __graph_weighted example_graph_weighted(10, 10);

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
    cout << _D(23, 18) << endl;

    /// 测试内容10： 无权图绘制路线


    //cout << 233 << endl;
    waitKey(0);
    return 0;
}
