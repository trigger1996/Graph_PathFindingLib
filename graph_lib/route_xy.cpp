#include "include/route.h"

void __route::get_R(vector<Point2f> &out) {

    out.clear();
    // 这边为了求稳，采用单个赋值，没有用等号
    for (int i = 0; i < r.size(); i++) {
        out.push_back(r[i]);
    }

}

uint32_t __route::set_R(vector<Point2f> in) {

    clear();
    for (int i = 0; i < in.size(); i++)
        r.push_back(in[i]);
    waypt_num = r.size();
}

uint32_t __route::add_WayPt(Point2f in) {

    r.push_back(in);
    waypt_num++;
}

uint32_t __route::self_Optimization() {
    // 消除路径中重复的路段，慎用
    int i, j;


    for (i = 0; i < r.size(); i++) {
        for (j = i + 1; j < r.size(); j++) {

        }
    }
}

void __route::reset_StartPt(Point2f startpt) {
    clear();
    r.push_back(startpt);
    waypt_num = 1;
}

void __route::clear() {
    r.clear();
    waypt_num = 0;
}

void __route::print() {
    cout << r << endl << endl;
}
