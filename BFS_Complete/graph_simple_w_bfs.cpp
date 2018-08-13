#include "include/graph_simple_w_bfs.h"

/// 核心程序
void __graph_simple_bfs::run_BFS() {
/*

    初始化：
    起点值初始化（past=NULL，dist=0）
        起点入队
        循环1：直到队列中没有元素
            从队伍中输出一个节点作为当前节点
            循环2：访问与当前节点连通但是【没有被访问过】的节点
              即将访问的节点入队


    https://blog.csdn.net/sallyxyl1993/article/details/57077512

    */
    int i, j;

    /// 起点入队
    if (bfs_q->get_Quene().size() == 0)
        bfs_q->pushBack(_startPos, _startPos);

    // 这里很巧妙利用了因为bfs_q会一直填入新的点
    // 如果到最后，整张图的点都会在表内，所以就不会有新的点，i就能加到最大值，否则因为点一直往里加，不可能退出
    for (i = 0; i < bfs_q->get_Quene().size(); i++) {
        /// 选择一个点作为当前节点
        __node node_temp = bfs_q->get_Quene()[i];
        /// 添加当前点附近，未被访问的节点，并设置其前驱节点为当前点
        vector<int32_t> list;
        get_AdjacencyPt(D, node_temp.grid_d(), list);                       // 获得该点的所有邻近点
        for (j = 0; j < list.size(); j++) {
            // 如果队列里没有，则加入队列
            if (bfs_q->find_Element_by_Grid(AdjMatGrid_2_GraphGrid(this, list[j])) != -1)
                continue;
            else
                bfs_q->pushBack(list[j], node_temp.grid_d());
        }

        /// 如果找到目标点，则结束遍历
        if (bfs_q->find_Element_by_Grid(_endPos) != -1)
            break;
    }

    /// 从终点回溯，得到路径
    vector<__node> temp;

    i = bfs_q->find_Element_by_Grid(_endPos);                               // 压入第一个点
    temp.push_back(bfs_q->get_Quene()[i]);
    while (temp[temp.size() - 1].grid() != _startPos) {
        i = bfs_q->find_Element_by_Grid(temp[temp.size() - 1].grid_p());    // 根据前驱节点坐标获得上一节点
        temp.push_back(bfs_q->get_Quene()[i]);                              // 将上一节点入队

    }
//    i = bfs_q->find_Element_by_Grid(_startPos);                           // 压入起始点，已经在前面了
//    temp.push_back(bfs_q->get_Quene()[i]);


    // 队列倒一下，正序输出
    route->reset(x_max, y_max);

    route->pushBack(_startPos, _startPos);                                  // 这里需要注意的是，route在重置以后，不能直接push，这是因为起始点的没有前驱节点，直接push会异常跳出
    for (i = temp.size() - 2; i >= 0; i--) {
        route->pushBack(temp[i].grid());
    }

    /// 打印结果
    route->print();

}

/// 绘图程序
void __graph_simple_bfs::draw_Img_with_Route(bool is_show) {
    const int32_t l = img_grid_len;
    int i;

    draw(false);

    /// 画出路径点
    for (i = 0; i < route->get_Quene().size(); i++) {
        Point2i way_pt(route->get_Quene()[i].grid().x, route->get_Quene()[i].grid().y);
        way_pt.x = way_pt.x * l + 5;
        way_pt.y = way_pt.y * l + 5;

        // 起点
        if (i == 0)
            circle(img, way_pt, 5, Scalar(33, 248, 146), -1);   // BGR
        else if (i == route->get_Quene().size() - 1)
            circle(img, way_pt, 5, Scalar(240, 33, 248), -1);
        else
            circle(img, way_pt, 3, Scalar(244, 36, 78));
    }

    /// 画出路线
    for (i = 1; i < route->get_Quene().size(); i++) {
        Point2i way_pt(route->get_Quene()[i].grid().x, route->get_Quene()[i].grid().y);
        way_pt.x = way_pt.x * l + 5;
        way_pt.y = way_pt.y * l + 5;

        Point2i way_pt_last(route->get_Quene()[i - 1].grid().x, route->get_Quene()[i - 1].grid().y);
        way_pt_last.x = way_pt_last.x * l + 5;
        way_pt_last.y = way_pt_last.y * l + 5;

        line(img, way_pt_last, way_pt, Scalar(40, 155, 240), 2);

    }

    /// 是否显示
    if (is_show) {
        namedWindow("graph_w_bfs", WINDOW_NORMAL);
        imshow("graph_w_bfs", img);
        waitKey(1);
    }
}

void __graph_simple_bfs::draw_Img_with_Route(char winName[]){
    draw_Img_with_Route(false);

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}

/// 这边尝试复现一下师兄的方向底层
/// 因为不成熟，所以故意写在这里
/// 不写头文件里，不希望被调用
typedef enum {
    _up         = 1,
    _up_right   = 2,
    _right      = 3,
    _down_right = 4,
    _down       = 5,
    _down_left  = 6,
    _left       = 7,
    _up_left    = 8,
    _no_dir     = 9,
} __dir_flag;

void __graph_simple_bfs::print_Img_with_Route() {
    int x, y, i, j;
    Point2f way_pt, way_pt_last;
    bool is_this_point_route = false;

    way_pt = way_pt_last = _startPos;
    i = 0;
    for (y = 0; y < graphMat.cols(); y++) {
        for (x = 0; x < graphMat.rows(); x++) {
            for (i = 0; i < route->get_Quene().size(); i++) {
                // 遇到每个点都检查一遍是不死路径，否则很容易画错
                if (route->get_Quene()[i].grid() == Point2f(x, y)) {
                    // 迭代更新路径点
                    if (i == 0)
                        way_pt = way_pt_last = Point2f(x, y);               // 第一个点没有前驱节点，直接用i - 1会爆炸
                    else {
                        way_pt      = route->get_Quene()[i].grid();
                        way_pt_last = route->get_Quene()[i - 1].grid();
                    }

                    __dir_flag dir;
                    if (way_pt.x > way_pt_last.x) {
                        if (way_pt.y > way_pt_last.y)
                            dir = _down_right;
                        else if (way_pt.y == way_pt_last.y)
                            dir = _right;
                        else if (way_pt.y <  way_pt_last.y)
                            dir = _up_right;
                    }
                    else if (way_pt.x == way_pt_last.x) {
                        if (way_pt.y > way_pt_last.y)
                            dir = _down;
                        else if (way_pt.y == way_pt_last.y)
                            dir = _no_dir;
                        else if (way_pt.y <  way_pt_last.y)
                            dir = _up;
                    }
                    else if (way_pt.x < way_pt_last.x) {
                        if (way_pt.y > way_pt_last.y)
                            dir = _down_left;
                        else if (way_pt.y == way_pt_last.y)
                            dir = _left;
                        else if (way_pt.y <  way_pt_last.y)
                            dir = _up_left;
                    }

                    switch (dir) {
                        case _up   :
                        case _down :
                            printf("| ");
                            break;

                        case _right :
                        case _left  :
                            printf("- ");
                            break;

                        case _up_right  :
                        case _down_left :
                             printf("/ ");
                            break;

                        case _down_right :
                        case _up_left :
                            printf("\\ ");
                            break;

                        case _no_dir :
                            printf("* ");
                            break;

                        default : break;
                    }
                is_this_point_route = true;
                }

            }
            if (is_this_point_route == true)
                is_this_point_route = false;        // 如果上面画过点了，这里就不画了，复位标识位即可
            else if (graphMat(y, x) > 0)
                cout << "1 ";
            else if (!graphMat(y, x))
                cout << "0 ";
        }

        cout << endl;
    }
}
