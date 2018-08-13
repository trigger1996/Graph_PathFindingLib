#ifndef __Route_XY_H
#define __Route_XY_H

#include "misc.hpp"

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/// 路径，使用笛卡尔坐标作为路径点
class __route_xy {
public:

    __route_xy() {                                          // 初始化一空路径
        r.clear();
        waypt_num = 0;
    }

    __route_xy(vector<Point2f> in) {                        // 初始化一整条路径
        set_Route(in);
    }

    __route_xy(Point2f startpt) {                           // 初始化一条路径，并赋予起始点
        reset_StartPt(startpt);
    }

    ~__route_xy() {                                         // 析构函数
        clear();
    }

    void get_Route(vector<Point2f> &out);                   // 读取整条路径

    uint32_t get_Route_Len()    {                           // 获得路径长度
        waypt_num = r.size();
        return r.size();
    }

    Point2f get_StartPt() { return r[0]; }                  // 读取起始点

    Point2f get_LastWayPt() { return r[waypt_num - 1]; }    // 读取最一个路径点

    uint32_t set_Route(vector<Point2f> in);                 // 设置整条路径

    uint32_t add_WayPt(Point2f in);                         // 添加新的点

    void remove_Last_WayPt();                               // 删除最末端的路径点

    void reset_StartPt(Point2f startpt);                    // 重设开始点，重设就必须清零整个路径

    void clear();                                           // 清零

    void print();                                           // 打印

protected:
    vector<Point2f> r;

    uint32_t waypt_num;

};

#endif // __Route_XY_H

