#include "include/route_d.h"

void __route_d::get_Route(vector<int32_t> &out) {

    out.clear();
    // 这边为了求稳，采用单个赋值，没有用等号
    for (int i = 0; i < r.size(); i++) {
        out.push_back(r[i]);
    }

}

uint32_t __route_d::set_Route(vector<int32_t> in) {

    clear();
    for (int i = 0; i < in.size(); i++)
        r.push_back(in[i]);
    waypt_num = r.size();
}

uint32_t __route_d::add_WayPt(int32_t in) {

    r.push_back(in);
    waypt_num++;
}

void __route_d::remove_Last_WayPt() {
    r.pop_back();
    waypt_num--;
}

void __route_d::reset_StartPt(int32_t startpt) {
    clear();
    r.push_back(startpt);
    waypt_num = 1;
}

void __route_d::clear() {
    r.clear();
    waypt_num = 0;
}

void __route_d::print() {
    cout << "[";
    for (int i = 0; i < r.size(); i++) {
        if (i == r.size() - 1)
            cout << "  " << r[i] << " ]" << endl;
        else if (i == 0)
            cout << " "  << r[i] << endl;               // 为了打印得好看一点
        else
            cout << "  " << r[i] << endl;
    }
    cout << endl;
}

