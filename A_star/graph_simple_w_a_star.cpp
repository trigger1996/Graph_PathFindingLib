#include "include/graph_simple_w_A_star.h"


int32_t find_Element_by_Grid(vector<__node_A_star> q, Point2f target) {
    for (int i = 0; i < q.size(); i++) {
        if (target == q[i].grid())
            return i;
    }
    return -1;
}

void remove_Element(vector<__node_A_star> &q, Point2f target) {
    vector<__node_A_star>::iterator itr = q.begin();
    while ( itr != q.end()) {
        __node_A_star temp = *itr;
        if (target == temp.grid()) {
            itr = q.erase(itr);
        }
        else
            itr++;
    }
}

void print_list(vector<__node_A_star> q) {
    for (int i = 0; i < q.size(); i++)
        cout << q[i].grid() << endl;
    cout << endl;
}

int32_t find_Node_with_Lowest_F(vector<__node_A_star> q) {
    int index = 0;
    for (int i = 0; i < q.size(); i++) {
        if (q[index].F() > q[i].F())
            index = i;
    }
    return index;
}

/// 核心程序
void __graph_simple_A_star::run_Astar() {

/// https://www.cnblogs.com/21207-iHome/p/6048969.html
/*
    [openList add:originalSquare]; // start by adding the original position to the open list

    do {
        currentSquare = [openList squareWithLowestFScore]; // Get the square with the lowest F score

        [closedList add:currentSquare]; // add the current square to the closed list
        [openList remove:currentSquare]; // remove it from the open list

        if ([closedList contains:destinationSquare]) { // if we added the destination to the closed list, we've found a path
            // PATH FOUND
            break; // break the loop
        }

        adjacentSquares = [currentSquare walkableAdjacentSquares]; // Retrieve all its walkable adjacent squares

        foreach (aSquare in adjacentSquares) {

            if ([closedList contains:aSquare]) { // if this adjacent square is already in the closed list ignore it
                continue; // Go to the next adjacent square
            }

            if (![openList contains:aSquare]) { // if its not in the open list
                // compute its score, set the parent
                [openList add:aSquare]; // and add it to the open list
            } else {
                // if its already in the open list
                // test if using the current G score make the aSquare F score lower, if yes update the parent because it means its a better path
            }
        }

    } while(![openList isEmpty]); // Continue until there is no more available square in the open list (which means there is no path)

*/
    __node_A_star currentPt;
    int i;

    /// 添加起点到openList内
    if (!openList.size()) {
        __node_A_star temp(_startPos, _startPos, x_max, y_max);
        openList.push_back(temp);
    }
    openList[0].G(0);
    openList[0].H(calc_Dist_Manhattan(_startPos, _endPos));

    do {
        /// 将开销最小的点作为当前点
        currentPt = openList[find_Node_with_Lowest_F(openList)];


        /// 闭列表添加该元素
        closeList.push_back(currentPt);
        /// 开列表删除该元素
        remove_Element(openList, currentPt.grid());

        /// 如果闭列表中存在终点，则退出
        /// 其实开列表重存在也是可以的
        if (find_Element_by_Grid(closeList, _endPos) != -1)
            break;

        /// 查找当前点附近的相邻点
        vector<int32_t> adj_list;
        get_AdjacencyPt(D, currentPt.grid_d(), adj_list);

        for (i = 0; i < adj_list.size(); i++) {
            __node_A_star temp(adj_list[i], currentPt.grid_d(), x_max, y_max);

            /// 如果闭列表中有这个点，则跳过
            if (find_Element_by_Grid(closeList, temp.grid()) != -1)
                continue;

            if (find_Element_by_Grid(openList,  temp.grid()) == -1) {
                /// 如果开列表中不含有这个点
                /// 计算其G值和H值，添加进开列表
                // 计算H值，H值好算，因为只与坐标有关
                temp.H(calc_Dist_Manhattan(temp.grid(), _endPos));
                // 计算G值
                temp.G(currentPt.G() + calc_Dist_Euclidean(currentPt.grid(), temp.grid())); // G值可以通过迭代得到，每次计算当前点到前驱节点的距离，加上前驱节点的G即可
                openList.push_back(temp);
            } else {
                /// 若该点在开列表内，则计算开销
                int32_t index = find_Element_by_Grid(openList,  temp.grid());
                __node_A_star pt_exist = openList[index];
                double g_temp = currentPt.G() + calc_Dist_Euclidean(currentPt.grid(), temp.grid());

                /// 若开销更小则，更新该点的父节点
                //  这里因为不好操作，所以直接删掉，然后重新放一个一样的进队列
                if (g_temp < pt_exist.G()) {
                    remove_Element(openList, pt_exist.grid());

                    temp.H(calc_Dist_Manhattan(temp.grid(), _endPos));
                    temp.G(g_temp);
                    openList.push_back(temp);
                }
            }
        }


    } while (openList.size());

    /// 回溯得到路径
    /// 从终点回溯，得到路径
    vector<__node_A_star> temp_q;

    // 压入第一个点，终点肯定在闭列表内
    i = find_Element_by_Grid(closeList, _endPos);
    temp_q.push_back(closeList[i]);
    while (temp_q[temp_q.size() - 1].grid() != _startPos) {
        i = find_Element_by_Grid(closeList,    temp_q[temp_q.size() - 1].grid_p()); // 根据前驱节点坐标获得上一节点
        if (i == -1) {
            i = find_Element_by_Grid(openList, temp_q[temp_q.size() - 1].grid_p());
            if (i == -1)
                break;
            temp_q.push_back(openList[i]);
        }
        temp_q.push_back(closeList[i]);                                             // 将上一节点入队

    }

//    i = bfs_q->find_Element_by_Grid(_startPos);                           // 压入起始点，已经在前面了
//    temp.push_back(bfs_q->get_Quene()[i]);

    // 队列倒一下，正序输出
    route->reset(x_max, y_max);

    route->pushBack(_startPos, _startPos);                                  // 这里需要注意的是，route在重置以后，不能直接push，这是因为起始点的没有前驱节点，直接push会异常跳出
    for (i = temp_q.size() - 2; i >= 0; i--) {
        route->pushBack(temp_q[i].grid());
    }
    cout << "Open  List: " << endl;
    print_list(openList);
    cout << "Close List: " << endl;
    print_list(closeList);
    cout << "Route: " << endl;
    route->print();

}// run_Astar

/// 绘图程序
void __graph_simple_A_star::draw_Img_with_Route(bool is_show) {
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

void __graph_simple_A_star::draw_Img_with_Route(char winName[]){
    draw_Img_with_Route(false);

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}
