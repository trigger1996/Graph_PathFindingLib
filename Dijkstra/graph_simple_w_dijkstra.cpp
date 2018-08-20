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

    const int32_t N = x_max * y_max;

    int i;
    Point2f currentPt;

    // Q加入所有点
    for (i = 0; i < N; i++) {
        list_to_visit->pushBack(i, i);

        Point2f pt_t = AdjMatGrid_2_GraphGrid(this, i);
        if (D((int32_t)pt_t.y, (int32_t)pt_t.x) == 0)
           dist.push_back(1e6);
        else
           dist.push_back(D((int32_t)pt_t.y, (int32_t)pt_t.x));
    }
    list_to_visit->popElement(_startPos);

    // S加入开始点
    list_visited->pushBack(_startPos, _startPos);
    currentPt = _startPos;

    /// 计算这个点的相邻点
    vector<int32_t> adj_list;
    get_AdjacencyPt(D, GraphGrid_2_AdjMatGrid(this, currentPt), adj_list);

    /// 计算visited到当前点的距离
    for (i = 0; i < adj_list.size(); i++)
        dist[adj_list[i]] = calc_Dist_Euclidean(_startPos, AdjMatGrid_2_GraphGrid(this, adj_list[i]));

    do {

        /// 取出距离最小的那一点，并其记录距离
        int32_t min_seq;
        double  min_dist = 1e6;
        for (i = 0; i < N; i++) {
            if (dist[i] < min_dist) {
                min_dist = dist[i];
                min_seq  = i;
            }
        }

        Point2f min_pt_t = AdjMatGrid_2_GraphGrid(this, i);
        int32_t index    = list_to_visit->find_Element_by_Grid(min_pt_t);
        if ()

        /// 对其他所有点计算，从距离最小点到该点的距离，如果小一些，则更新其他点的距离数据

    } //while (list_to_visit.size());
       while (0);

}
