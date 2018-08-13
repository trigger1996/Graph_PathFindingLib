#ifndef __Node_H
#define __Node_H

#include <stdint.h>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

#include <opencv2/opencv.hpp>
#include "../../graph_lib/include/graph_simple.h"

using namespace std;
using namespace cv;

typedef enum {
    unvisited = 0,
    visited   = 1,
    adjacent_pts_visited = 2,
} __visit_status;                                                           // 访问状态

class __node {
public:

    /// 构造函数
    __node() {
        __node(0, 0, 1, 1);                                                 // 设置一个缺省的
    }

    //__node(int32_t map_x, int32_t map_y);                                 // 在这里处理这些太复杂了，所以交给队列处理

    __node(Point2f pt, Point2f pt_past, int32_t map_x, int32_t map_y) {
        __graph_abstract *_map_t = new __graph_simple(map_x, map_y);        // 不管是有权图还是无权图，这里都用无权就行了，只是为了获得地图长宽

        _grid    = pt;
        _grid_d  = GraphGrid_2_AdjMatGrid(_map_t, pt);

        _grid_p  = pt_past;
        _grid_pd = GraphGrid_2_AdjMatGrid(_map_t, pt_past);

        delete _map_t;
        calc_Dist_2_Past();
        _dist_2_start = -1e6;
    }

    __node(int32_t pt, int32_t pt_past, int32_t map_x, int32_t map_y) {
        __graph_abstract *_map_t = new __graph_simple(map_x, map_y);

        _grid    = AdjMatGrid_2_GraphGrid(_map_t, pt);
        _grid_d  = pt;

        _grid_p  = AdjMatGrid_2_GraphGrid(_map_t, pt_past);
        _grid_pd = pt_past;

        delete _map_t;
        calc_Dist_2_Past();
        _dist_2_start = -1e6;
    }

    __node(Point2f pt, int32_t pt_past, int32_t map_x, int32_t map_y) {
        __graph_abstract *_map_t = new __graph_simple(map_x, map_y);

        _grid    = pt;
        _grid_d  = GraphGrid_2_AdjMatGrid(_map_t, pt);

        _grid_p  = AdjMatGrid_2_GraphGrid(_map_t, pt_past);
        _grid_pd = pt_past;

        delete _map_t;
        calc_Dist_2_Past();
        _dist_2_start = -1e6;
    }

    __node(int32_t pt, Point2f pt_past, int32_t map_x, int32_t map_y) {
        __graph_abstract *_map_t = new __graph_simple(map_x, map_y);

        _grid    = AdjMatGrid_2_GraphGrid(_map_t, pt);
        _grid_d  = pt;

        _grid_p  = pt_past;
        _grid_pd = GraphGrid_2_AdjMatGrid(_map_t, pt_past);

        delete _map_t;
        calc_Dist_2_Past();
        _dist_2_start = -1e6;
    }

    /// 析构函数
    ~__node() {

    }

    /// 获得数据
    //int32_t map_x()       { return _map_x;   }

    //int32_t map_y()       { return _map_y;   }

    Point2f grid()          { return _grid;    }
    int32_t grid_d()        { return _grid_d;  }

    Point2f grid_p()        { return _grid_p;  }
    int32_t grid_pd()       { return _grid_pd; }

    double dist_2_start()   { return _dist_2_start; }
    double dist_2_pass()    { return _dist_2_past;  }

    /// 计算距离
    double calc_Dist_2_Start(Point2f startPos) {        // 计算与距离起始点的距离
        double dx, dy;
        dx = _grid.x - startPos.x;
        dy = _grid.x - startPos.y;
        _dist_2_start = sqrt(dx * dx + dy * dy);
        return _dist_2_start;
    }

    double calc_Dist_2_Past() {                         // 计算与前驱节点的距离
        double dx, dy;
        dx = _grid.x - _grid_p.x;
        dy = _grid.x - _grid_p.y;
        _dist_2_past = sqrt(dx * dx + dy * dy);
        return _dist_2_past;
    }

    /// 运算符重载
    inline __node& operator =(__node src) {             // 重载赋值运算符
        this->_grid    = src.grid();
        this->_grid_d  = src.grid_d();
        this->_grid_p  = src.grid_p();
        this->_grid_pd = src.grid_pd();

        this->_dist_2_past  = src.dist_2_pass();
        this->_dist_2_start = src.dist_2_start();
    }

    inline bool operator ==(__node src) {               // 重载相等判断运算符
        if ((this->_grid    == src.grid() ||            // &&
             this->_grid_d  == src.grid_d()) &&
            (this->_grid_p  == src.grid_p() ||          // &&
             this->_grid_pd == src.grid_pd()))
            return true;
        else
            return false;
    }

protected:

    //int32_t _map_x, _map_y;                           // 地图长宽

    Point2f _grid;                                      // 当前节点坐标，笛卡尔坐标
    int32_t _grid_d;                                    // 当前节点坐标，邻接矩阵坐标

    Point2f _grid_p;                                    // 前驱节点坐标，笛卡尔坐标
    int32_t _grid_pd;                                   // 前驱节点坐标，邻接矩阵坐标

    double _dist_2_start;                               // 距离起始点距离
    double _dist_2_past;                                // 距离前驱节点距离

//  __visit_status _is_visited;     // 是否被访问过，后面发现这个变量不是很有用，因为基本用不着

};

class __node_q {
public:

    /// 构造函数
    __node_q(int32_t map_x, int32_t map_y);

    __node_q(int32_t map_x, int32_t map_y, Point2f startPos);

    __node_q(int32_t map_x, int32_t map_y, int32_t startPos);

    /// 析构函数
    ~__node_q();

    /// 重置队列
    void reset(int32_t map_x, int32_t map_y) {
        _map_x = map_x;
        _map_y = map_y;
        _q.clear();
    }

    /// 获得数据
    vector<__node> get_Quene() { return _q; }                           // 获得队列

    int32_t        get_Map_X() { return _map_x; }                       // 获得地图长度

    int32_t        get_Map_Y() { return _map_y; }                       // 获得地图宽度

    /// 复制队列
    void copy(vector<__node> &dst);

    void copy(__node_q &dst);

    /// 添加删除操作
    int32_t pushBack(__node in);                                        // 添加一个新元素，并将上一个元素作为其前驱节点，下同

    int32_t pushBack(Point2f in);

    int32_t pushBack(int32_t in);

    int32_t pushBack(__node in,  __node in_passed);                     // 添加一个新元素，并独立设置其前驱节点，下同

    int32_t pushBack(Point2f in, Point2f in_passed);

    int32_t pushBack(int32_t in, int32_t in_passed);


    __node  popFront();                                                 // 删除最前端元素

    int32_t popElement(int32_t index);                                  // 删除某一个元素，输入参数为该元素标号

    int32_t popElement(Point2f target);                                 // 删除某一个元素，输入参数为该元素坐标，注意这里因为参数雷同，所以只能用笛卡尔坐标输入

    /// 查找操作
    int32_t find_Element_by_Node(__node  target);                       // 根据节点信息查找坐标相同的点，返回下标，找不到则返回-1

    int32_t find_Element_by_Grid(Point2f target);                       // 根据节点笛卡尔坐标查找坐标相同的点，返回下标，找不到则返回-1

    int32_t find_Element_by_Grid(int32_t target);                       // 根据节点邻接矩阵坐标查找坐标相同的点，返回下标，找不到则返回-1

    /// 运算符重载
    inline __node_q& operator =(__node_q src) {                         // 重载赋值运算符
       // 运算符最好不要写在.cpp里，好像会报warning
       this->_map_x = src.get_Map_X();
       this->_map_y = src.get_Map_Y();

       vector<__node> q_temp = src.get_Quene();
       this->_q.clear();
       for (int i = 0; i < q_temp.size(); i++)
           _q.push_back(q_temp[i]);
    }

    /// 显示操作
    void print();                                                       // 通过终端界面打印队列

protected:

    vector<__node> _q;                                                  // 本来想用队列的，后面发现队列查找不方便，所以还是改回vector，虽然效率会降低

    int32_t _map_x, _map_y;                                             // 地图长宽
};

static inline Point2f get_Grid_xy_from_Node(__node node) {
    return node.grid();
}

#endif	// __Node_H
