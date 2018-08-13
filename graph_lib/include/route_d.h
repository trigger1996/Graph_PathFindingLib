#ifndef __Route_D_H
#define __Route_D_H

#include "misc.hpp"

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/// 路线类，使用单坐标作为路径点
class __route_d {
public:

    __route_d() {                                           // 初始化一空路径
        r.clear();
        waypt_num = 0;
    }

    __route_d(vector<int32_t> in) {                         // 初始化一整条路径
        set_Route(in);
    }

    __route_d(int32_t startpt) {                            // 初始化一条路径，并赋予起始点
        reset_StartPt(startpt);
    }

    ~__route_d() {                                          // 析构函数
        clear();
    }

    void get_Route(vector<int32_t> &out);                   // 读取整条路径

    uint32_t get_Route_Len()    {                           // 获得路径长度
        waypt_num = r.size();
        return r.size();
    }

    int32_t get_StartPt() { return r[0]; }                  // 读取起始点

    int32_t get_LastWayPt() { return r[waypt_num - 1]; }    // 读取最一个路径点

    uint32_t set_Route(vector<int32_t> in);                 // 设置整条路径

    uint32_t add_WayPt(int32_t in);                         // 添加新的点

    void remove_Last_WayPt();                               // 删除最末端的路径点

    void reset_StartPt(int32_t startpt);                    // 重设开始点，重设就必须清零整个路径

    void clear();                                           // 清零

    void print();                                           // 打印

protected:
    vector<int32_t> r;

    uint32_t waypt_num;

};

#endif // __Route_D_H

