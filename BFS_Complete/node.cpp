#include "include/node.h"

/// 构造函数
__node_q::__node_q(int32_t map_x, int32_t map_y) {
    _map_x = map_x;
    _map_y = map_y;
}

__node_q::__node_q(int32_t map_x, int32_t map_y, Point2f startPos) {
    _map_x = map_x;
    _map_y = map_y;
    pushBack(startPos, startPos);       // 为了方便编程，前驱节点设成自己
}

__node_q::__node_q(int32_t map_x, int32_t map_y, int32_t startPos) {
    _map_x = map_x;
    _map_y = map_y;
    pushBack(startPos, startPos);
}

/// 析构函数
__node_q::~__node_q() {
    _map_x = _map_y = -1;
    _q.clear();
}

/// 复制队列
void __node_q::copy(vector<__node> &dst) {
    dst.clear();
    this->_q.clear();
    for (int i = 0; i < _q.size(); i++)
        dst.push_back(_q[i]);
}

void __node_q::copy(__node_q &dst) {
    dst = *this;
}

/// 添加删除操作
int32_t __node_q::pushBack(__node in) {
    // 需要注意：这边修改了前驱节点
    __node temp(in.grid(), _q[_q.size() - 1].grid(), _map_x, _map_y);    // in.grid(), in.grid_p(), _map_x, _map_y
    _q.push_back(temp);
}

int32_t __node_q::pushBack(Point2f in) {
    // 换种好理解的写法
    size_t quene_last_seq = _q.size() - 1;
    Point2f grid_passed_t = _q[quene_last_seq].grid();

    __node temp(in, grid_passed_t, _map_x, _map_y);
    _q.push_back(temp);
}

int32_t __node_q::pushBack(int32_t in) {
    __node temp(in, _q[_q.size() - 1].grid(), _map_x, _map_y);
    _q.push_back(temp);
}

int32_t __node_q::pushBack(__node in,  __node in_passed) {
    __node temp(in.grid(), in_passed.grid(), _map_x, _map_y);
    _q.push_back(temp);
}

int32_t __node_q::pushBack(Point2f in, Point2f in_passed) {
    __node temp(in, in_passed, _map_x, _map_y);
    _q.push_back(temp);
}

int32_t __node_q::pushBack(int32_t in, int32_t in_passed) {
    __node temp(in, in_passed, _map_x, _map_y);
    _q.push_back(temp);
}

__node __node_q::popFront() {
    __node temp = _q[0];

    vector<__node>::iterator itr = _q.begin();
    itr = _q.erase(itr);                                                // 本来要写第一个将第二个点的前驱节点修改成它自己的，结果发现搞不定，所以就这样
    return temp;
}

int32_t __node_q::popElement(int32_t index) {
    if (index < _q.size()) {
        vector<__node>::iterator itr = _q.begin() + index;
        itr = _q.erase(itr);
    }
    return _q.size();
}

int32_t __node_q::popElement(Point2f target) {
    vector<__node>::iterator itr = _q.begin();
    while ( itr != _q.end()) {
        __node temp = *itr;
        if (target == temp.grid()) {
            itr = _q.erase(itr);
        }
        else
            itr++;
    }
}

/// 查找操作
int32_t __node_q::find_Element_by_Node(__node  target) {
    // 注意:
    // 这里只检查当前坐标，不检查其前驱节点坐标
    for (int i = 0; i < _q.size(); i++) {
        if (target.grid()   == _q[i].grid() ||
            target.grid_d() == _q[i].grid_d())
            return i;
    }
    return -1;
}

int32_t __node_q::find_Element_by_Grid(Point2f target) {
    for (int i = 0; i < _q.size(); i++) {
        if (target == _q[i].grid())
            return i;
    }
    return -1;
}

int32_t __node_q::find_Element_by_Grid(int32_t target) {
    for (int i = 0; i < _q.size(); i++) {
        if (target == _q[i].grid_d())
            return i;
    }
    return -1;
}

/// 显示操作
void  __node_q::print() {
    for (int i = 0; i < _q.size(); i++) {
        cout << _q[i].grid() << endl;
    }
    cout << endl;
}
