#ifndef __Route_XY_H
#define __Route_XY_H

#include "misc.hpp"

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/// 路径类
class __route_xy {
public:

    __route();

    ~__route();

    void get_R(vector<Point2f> &out);               // 读取整条路径

    uint32_t get_R_Len()    {                       // 获得路径长度
        waypt_num = r.size();
        return r.size();
    }

    uint32_t set_R(vector<Point2f> in);             // 设置整条路径

    uint32_t add_WayPt(Point2f in);                 // 添加新的点

    uint32_t self_Optimization();                   // 自行优化

    void reset_StartPt(Point2f startpt);            // 重设开始点，重设就必须清零整个路径

    void clear();                                   // 清零

    void print();                                   // 打印

protected:
    vector<Point2f> r;

    uint32_t waypt_num;

};

#endif // __Route_XY_H

