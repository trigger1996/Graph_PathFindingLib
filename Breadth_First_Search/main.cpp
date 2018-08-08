#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Dense>

#include "../graph_lib/include/graph_simple.h"

using namespace std;
using namespace cv;
using namespace Eigen;

const uint32_t l = 10;

typedef enum {
    unvisited = 0,
    visited   = 1,
    adjacent_pts_visited = 2,
} __visit_status;

typedef struct {
    Point2f grid;       // 当前结点坐标
    int32_t grid_d;

    Point2f grid_p;                 // 前驱结点
    int32_t grid_pd;

    double dist;                    // 距离起始点距离

    __visit_status is_visited;      // 是否被访问过
} __bfs_node;

MatrixXd       _D;
__graph_simple _map(10, 10);
Point2f startPos(0, 0);
Point2f endPos(9, 9);

vector<__bfs_node> bfs_q;           // bfs_quene

inline int32_t Pos_xy_2_D(Point2f xy);
inline void get_AdjacencyPt(MatrixXd D, int32_t pt_d, vector<int32_t> &lists);

void bfs_Push(Point2f pt, Point2f pt_past);
void bfs_Push(int32_t pt_d, int32_t pt_past_d);
void bfs_PushStart(Point2f start);
void bfs_Copy(vector<__bfs_node> src, vector<__bfs_node> &dst);
inline __bfs_node grid_xy_2_bfsnode(Point2f pt, Point2f pt_past);
inline __bfs_node grid_D_2_bfsnode(int32_t pt_d, int32_t pt_past_d);
inline  int32_t bfs_Find_Node_by_Info(vector<__bfs_node> array, __bfs_node target);
inline int32_t bfs_Find_Node_by_Grid(vector<__bfs_node> array, Point2f target);

int main(void) {

    int i, j ,k;
    MatrixXd mat_test;

    mat_test.resize(10, 10);
    mat_test << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
                1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
                1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
                1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
                1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1;
    _map.set_graphMat(mat_test);
    _map.draw("example_graph", true);
    _D = _map.calc_AdjacencyMatrix();
    //cout << D << endl;

/*

初始化：
起点值初始化（past=NULL，dist=0，visit=1）
其他节点值初始化（past=NULL，dist=无穷，visit=0）
    起点入队
    循环1：直到队列中没有元素
        从队伍中输出一个节点作为当前节点
        循环2：访问与当前节点连通但是【没有被访问过】的节点（visit=0的节点）
          将即将访问的节点记为正在访问的状态
          将即将访问的节点的状态更新（past=当前节点，dist=即将访问的节点到当前节点的距离，visit=1）
          即将访问的节点入队
   将当前节点的visit记为2（因为与它连接的所有节点都被访问过）

https://blog.csdn.net/sallyxyl1993/article/details/57077512

*/

    /// 步骤1: 将起点入队
    bfs_PushStart(startPos);

    i = 0;
  while (true) {                                                // bfs_q.size()
        vector<__bfs_node> temp_q;
        vector<int32_t> list;

        __bfs_node currentPt;
        __bfs_node temp_node;
        vector<__bfs_node> pt_to_add;

        bfs_Copy(bfs_q, temp_q);
        for (i = 0; i < temp_q.size(); i++) {
            currentPt = temp_q[i];

            list.clear();
            pt_to_add.clear();
            get_AdjacencyPt(_D, currentPt.grid_d, list);        // 获得当前点的邻接点
            for (j = 0; j < list.size(); j++)                   // 邻接点数据格式转换
                pt_to_add.push_back(grid_D_2_bfsnode(list[j], currentPt.grid_d));
            for (j = 0; j < pt_to_add.size(); j++) {
                temp_node = pt_to_add[j];
                if (bfs_Find_Node_by_Info(bfs_q, temp_node) >= 0)
                    continue;                                   // 邻接点删除已有点
                else {
                    temp_node.is_visited = visited;
                    bfs_q.push_back(temp_node);                 // 当前点邻接点添加进队列
                }
            }
            int32_t index = bfs_Find_Node_by_Info(bfs_q, currentPt);
            bfs_q[index].is_visited = adjacent_pts_visited;     // 当前结点连接的所有结点都已经访问过
        }

        if (bfs_Find_Node_by_Grid(bfs_q, endPos) != -1)
            break;

    }

    /// 打印路径
    vector<__bfs_node> route;
    __bfs_node temp_node;
    route.clear();

    i = bfs_Find_Node_by_Grid(bfs_q, endPos);                   // 压入第一个点
    route.push_back(bfs_q[i]);
    while (route[route.size() - 1].grid_pd >= 0) {
        i = bfs_Find_Node_by_Grid(bfs_q, route[route.size() - 1].grid_p);
        route.push_back(bfs_q[i]);
    }


    for (i = 0; i < route.size(); i++)
        cout << route[i].grid << endl;

    waitKey(0);
    return 0;

}// main

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

void bfs_Push(Point2f pt, Point2f pt_past) {
    __bfs_node temp;

    temp.grid    = pt;
    temp.grid_d  = Pos_xy_2_D(pt);

    temp.grid_p  = pt_past;
    temp.grid_pd = Pos_xy_2_D(pt_past);

    double dx = pt.x - startPos.x;
    double dy = pt.y - startPos.y;
    temp.dist = sqrt(dx * dx + dy * dy);

    temp.is_visited = unvisited;

    bfs_q.push_back(temp);
}

void bfs_Push(int32_t pt_d, int32_t pt_past_d) {
    __bfs_node temp;

    temp.grid    = AdjMatGrid_2_GraphGrid(&_map, pt_d);
    temp.grid_d  = pt_d;

    temp.grid_p  = AdjMatGrid_2_GraphGrid(&_map, pt_past_d);
    temp.grid_pd = pt_d;

    double dx = temp.grid.x - startPos.x;
    double dy = temp.grid.y - startPos.y;
    temp.dist = sqrt(dx * dx + dy * dy);

    temp.is_visited = unvisited;

    bfs_q.push_back(temp);
}

void bfs_PushStart(Point2f start) {
    __bfs_node temp;

    temp.grid    = start;
    temp.grid_d  = Pos_xy_2_D(start);

    temp.grid_p  = Point2f(-1e6, -1e6);
    temp.grid_pd = -1e6;

    temp.dist = 0;

    temp.is_visited = unvisited;

    while (bfs_q.size())
        bfs_q.pop_back();
    bfs_q.push_back(temp);
}

void bfs_Copy(vector<__bfs_node> src, vector<__bfs_node> &dst) {
    dst.clear();
    for (int i = 0; i < src.size(); i++) {
        dst.push_back(src[i]);
    }
}

inline __bfs_node grid_xy_2_bfsnode(Point2f pt, Point2f pt_past) {
    __bfs_node temp;

    temp.grid    = pt;
    temp.grid_d  = Pos_xy_2_D(pt);

    temp.grid_p  = pt_past;
    temp.grid_pd = Pos_xy_2_D(pt_past);

    double dx = pt.x - startPos.x;
    double dy = pt.y - startPos.y;
    temp.dist = sqrt(dx * dx + dy * dy);

    temp.is_visited = unvisited;

    return temp;
}

inline __bfs_node grid_D_2_bfsnode(int32_t pt_d, int32_t pt_past_d) {
    __bfs_node temp;

    temp.grid    = AdjMatGrid_2_GraphGrid(&_map, pt_d);
    temp.grid_d  = pt_d;

    temp.grid_p  = AdjMatGrid_2_GraphGrid(&_map, pt_past_d);
    temp.grid_pd = pt_d;

    double dx = temp.grid.x - startPos.x;
    double dy = temp.grid.y - startPos.y;
    temp.dist = sqrt(dx * dx + dy * dy);

    temp.is_visited = unvisited;

    return temp;
}

inline int32_t bfs_Find_Node_by_Info(vector<__bfs_node> array, __bfs_node target) {

    for (int i = 0; i < array.size(); i++)
        if (target.grid_d == array[i].grid_d ||
            target.grid   == array[i].grid)
            return i;

    return -1;
}

inline int32_t bfs_Find_Node_by_Grid(vector<__bfs_node> array, Point2f target) {

    for (int i = 0; i < array.size(); i++)
        if (target == array[i].grid)
            return i;

    return -1;
}
