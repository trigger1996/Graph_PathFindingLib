#include "include/route_xy.h"

void __route_xy::get_Route(vector<Point2f> &out) {

    out.clear();
    // 这边为了求稳，采用单个赋值，没有用等号
    for (int i = 0; i < r.size(); i++) {
        out.push_back(r[i]);
    }

}

uint32_t __route_xy::set_Route(vector<Point2f> in) {

    clear();
    for (int i = 0; i < in.size(); i++)
        r.push_back(in[i]);
    waypt_num = r.size();
}

uint32_t __route_xy::add_WayPt(Point2f in) {

    r.push_back(in);
    waypt_num++;
}

void __route_xy::remove_Last_WayPt() {
    r.pop_back();
    waypt_num--;
}

void __route_xy::reset_StartPt(Point2f startpt) {
    clear();
    r.push_back(startpt);
    waypt_num = 1;
}

void __route_xy::clear() {
    r.clear();
    waypt_num = 0;
}

void __route_xy::print() {
    cout << r << endl << endl;
}
