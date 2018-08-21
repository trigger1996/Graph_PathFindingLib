#include "include/graph_simple_w_dijkstra.h"

void __graph_simple_dijkstra::run_Dijkstra() {

/// 第一步：从起始顶点开始

/// 第二步：对当前顶点进行标识

/// 第三步：对当前顶点的所有相邻顶点依次进行松弛操作

/// 第四步：更新列表

/// 第五步：从列表的未标识顶点中找到当前最短距离最小
///        的顶点，作为新的当前顶点

/// 第六步：重复第二步至第五步，直到列表中不存在未标
///        识顶点
/*
    Dijkstra 算法的时间复杂度：O(E*logV)

    Dijkstra
        S = NULL
        Q = G
        while (!Q.empty) {
            u = HEAP-EXTRACT-MIN(Q)
            S.insert(u)
            for(从u出发的每一条边v)
            RELAX(u, v, w)
    }

    RELAX(u, v, w)
      if (d[v] > d[u] + w(u,v)) {
        d[v] = d[u] + w(u,v)
        v.π = u
      }

        for(k = 0;k < n;k++){
            if(!visited[k] && (dist[k] > (dist[min_i] + map[min_i][k])))
                dist[k] = dist[min_i] + map[min_i][k];
        }
*/
/// 主要参考:
/// https://blog.csdn.net/a_big_pig/article/details/44163903
/// https://blog.csdn.net/jinixin/article/details/52247763
/// 有些操作和SPFA相似，这里也可以参考：
/// https://blog.csdn.net/xunalove/article/details/70045815

    const int32_t N = x_max * y_max;

    int i;
    int32_t currentPt_d;

    currentPt_d = GraphGrid_2_AdjMatGrid(this, _startPos);

    adjMat_2_Weighted();

    // Q加入所有点
    for (i = 0; i < N; i++)
        list_to_visit->pushBack(i, i);
    list_to_visit->popElement(_startPos);

    // dist设为初始值，这里直接用起始点对应到各个点的距离，这里可以直接读取邻接矩阵指定行
    dist.clear();
    for (i = 0; i < N; i++) {
        if (i == currentPt_d)
            dist.push_back(0);
        else
            dist.push_back(1e6);        // Dw(currentPt_d, i)
    }
    // S加入开始点
    list_visited->pushBack(_startPos, _startPos);

    // 路径初始化
    for (i = 0; i < N; i++)
        path.push_back(0);

    do {

        vector<int32_t> adj_list;

        get_AdjacencyPt(Dw, currentPt_d, adj_list);

        /// 松弛操作
        for (i = 0; i < N; i++) {
            if (dist[i] > dist[currentPt_d] + Dw(currentPt_d, i)) {
                dist[i] = dist[currentPt_d] + Dw(currentPt_d, i);

            path[i] = currentPt_d;

            }
        }

        ///  寻找距离最小的点，作为当前点
        int min_seq = (currentPt_d >= N - 1) ? currentPt_d - 1 :
                                               currentPt_d + 1;    // 这里注意，不能设为0或者currentPt_d
                                                                   // 因为这个位置的值是0，同时如果全用 + 1 可能会超
        for (i = 0; i < N; i++) {
            if (list_to_visit->find_Element_by_Grid(i) != -1 &&     // 这个点没有被浏览过
                i != currentPt_d &&                                 // 这个点不是当前点
                dist[min_seq] > dist[i]) {                          // 这个点的距离最小
                min_seq = i;

            }
        }
        currentPt_d = min_seq;

        /// 当前点进行标记
        list_visited->pushBack(currentPt_d, currentPt_d);
        list_to_visit->popElement(AdjMatGrid_2_GraphGrid(this, currentPt_d));

        if (list_visited->find_Element_by_Grid(_endPos) != -1)      // 在找到终点后退出，如果不加这个会有点退不出来
            break;

    } while(list_to_visit->get_Quene().size());
      //while (0);

    /// 回溯得到路径
    vector<Point2f> route_t;
    i = GraphGrid_2_AdjMatGrid(this, _endPos);
    route_t.clear();
    do {
        route_t.push_back(AdjMatGrid_2_GraphGrid(this, i));
        //cout << AdjMatGrid_2_GraphGrid(this, i) << endl;
        i = path[i];
    } while (i != 0);
    route_t.push_back(_startPos);

    // 队列倒一下，正序输出
    // 因为回溯得到的是倒过来的，所以这边必须反向
    route->pushBack(_startPos, _startPos);
    for (i = route_t.size() - 2; i >= 0; i--) {
        route->pushBack(route_t[i], route_t[i + 1]);
    }

    route->print();
}

/// 绘图程序
void __graph_simple_dijkstra::draw_Img_with_Route(bool is_show) {
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
        namedWindow("graph_w_Dijkstra", WINDOW_NORMAL);
        imshow("graph_w_Dijkstra", img);
        waitKey(1);
    }
}

void __graph_simple_dijkstra::draw_Img_with_Route(char winName[]) {
    draw_Img_with_Route(false);

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}

void __graph_simple_dijkstra::adjMat_2_Weighted() {

    const int N = x_max * y_max;

    Dw.setZero(N, N);
    for (int32_t y = 0; y < N; y++) {
        for (int32_t x = 0; x < N; x++) {
            if (y == x)
                Dw(y, x) = 0;
            else if (D(y, x) == 0)
                Dw(y, x) = 1e6;
            else
                Dw(y, x) = calc_Dist_Euclidean(AdjMatGrid_2_GraphGrid(this, y),
                                               AdjMatGrid_2_GraphGrid(this, x));       // 计算目标点之间的欧式距离，为什么两个点是x和y，这个可以去茶邻接矩阵的定义
        }
    }
}
