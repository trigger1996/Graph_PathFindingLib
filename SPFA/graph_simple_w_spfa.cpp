#include "include/graph_simple_w_spfa.h"

inline int32_t pop_front(vector<int32_t> &_q);\
inline int32_t find_Element_in_List(vector<int32_t> _q, int32_t tgt);

void __graph_simple_spfa::run_SPFA() {

/*
我们用数组dis记录每个结点的最短路径估计值，用邻接表或邻接矩阵来存储图G。
我们采取的方法是动态逼近法：
    设立一个先进先出的队列用来保存待优化的结点，
    优化时每次取出队首结点u，并且用u点当前的最短路径估计值对离开u点所指向的结点v进行松弛操作，
    如果v点的最短路径估计值有所调整，且v点不在当前的队列中，就将v点放入队尾。
    这样不断从队列中取出结点来进行松弛操作，直至队列空为止

https://blog.csdn.net/qq_35644234/article/details/61614581

//_______________________________________________________________________________________________

最短路径本身怎么输出？
    在一个图中，我们仅仅知道结点A到结点E的最短路径长度，有时候意义不大。这个图如果是地图的模型的话，在算出最短路径长度后，我们总要说明“怎么走”才算真正解决了问题。如何在计算过程中记录下来最短路径是怎么走的，并在最后将它输出呢？
    我们定义一个path[]数组，path[i]表示源点s到i的最短路程中，结点i之前的结点的编号(父结点)，我们在借助结点u对结点v松弛的同时，标记下path[v]=u，记录的工作就完成了。
    如何输出呢？我们记录的是每个点前面的点是什么，输出却要从最前面到后面输出，这很好办，递归就可以了：

https://blog.csdn.net/xunalove/article/details/70045815

*/

    const int32_t l = x_max * y_max;
    int32_t i, j;

    // 邻接矩阵转换成有权的，不然不连通的点都是0，是最小值，会影响计算
    adjMat_2_Weighted();

    /// 初始化队列v
    v.push_back(GraphGrid_2_AdjMatGrid(this, _startPos));

    /// 初始化距离矩阵dist
    for (i = 0; i < l; i++) {
        if (i == GraphGrid_2_AdjMatGrid(this, _startPos))
            dist.push_back(0);
        else
            dist.push_back(1e6);
    }

    /// 初始化一个邻接矩阵长度的一维数组，用于存放路径
    vector<int32_t> path;
    for (i = 0; i < l; i++)
        path.push_back(0);

    do {
        /// 弹出队首
        int32_t currentPt_d;
        currentPt_d = pop_front(v);

        /// 遍历所有点
        for (i = 0; i < l; i++) {
            /// 松弛操作
            if (dist[i] > dist[currentPt_d] + Dw(currentPt_d, i)) {
                dist[i] = dist[currentPt_d] + Dw(currentPt_d, i);

                /// 一旦允许松弛操作，则检查队列，该点是否在队列内，如果不是，则入队
                if (find_Element_in_List(v, i) == -1) {
                    v.push_back(i);

                    // 记录父节点，准备回溯
                    path[i] = currentPt_d;
                }
            }
        }

    } while (v.size());

    /// 回溯得到路径
    i = GraphGrid_2_AdjMatGrid(this, _endPos);
    route.clear();
    do {
        route.push_back(AdjMatGrid_2_GraphGrid(this, i));
        //cout << AdjMatGrid_2_GraphGrid(this, i) << endl;
        i = path[i];
    } while (i != 0);
    route.push_back(_startPos);

    // 回溯得到的是倒过来的，现在需要正过来
    for (i = 0, j = route.size() - 1; i < route.size() / 2; i++, j--) {     // i < route.size()
        //Point2i temp;
        //temp = route[i];
        //route[i] = route[j];
        //route[j] = temp;
        swap(route[i], route[j]);
    }


    /// 打印路径
    for (i = 0; i < route.size(); i++)
        cout << route[i] << endl;

}

void __graph_simple_spfa::adjMat_2_Weighted() {
    const int32_t l = x_max * y_max;
    int x, y;

    Dw.setZero(l, l);
    for (y = 0; y < l; y++) {
        for (x = 0; x < l; x++) {
            if (D(y, x) == 0)
                Dw(y, x) = 1e6;
            else
                Dw(y, x) = calc_Dist_Euclidean(AdjMatGrid_2_GraphGrid(this, y), AdjMatGrid_2_GraphGrid(this, x));
        }
    }
}

/// 显示代码
void __graph_simple_spfa::draw_Img_with_Route(bool is_show) {
    const int32_t l = img_grid_len;
    int i;

    draw(false);


    /// 画出路径点
    for (i = 0; i < route.size(); i++) {
        Point2i way_pt(route[i].x, route[i].y);
        way_pt.x = way_pt.x * l + 5;
        way_pt.y = way_pt.y * l + 5;

        // 起点
        if (i == 0)
            circle(img, way_pt, 5, Scalar(33, 248, 146), -1);   // BGR
        else if (i == route.size() - 1)
            circle(img, way_pt, 5, Scalar(240, 33, 248), -1);
        else
            circle(img, way_pt, 3, Scalar(244, 36, 78));
    }


    /// 画出路线
    for (i = 1; i < route.size(); i++) {
        Point2i way_pt(route[i].x, route[i].y);
        way_pt.x = way_pt.x * l + 5;
        way_pt.y = way_pt.y * l + 5;

        Point2i way_pt_last(route[i - 1].x, route[i - 1].y);
        way_pt_last.x = way_pt_last.x * l + 5;
        way_pt_last.y = way_pt_last.y * l + 5;

        line(img, way_pt_last, way_pt, Scalar(40, 155, 240), 2);

    }

    /// 是否显示
    if (is_show) {
        namedWindow("graph_w_SPFA", WINDOW_NORMAL);
        imshow("graph_w_SPFA", img);
        waitKey(1);
    }
}

void __graph_simple_spfa::draw_Img_with_Route(char winName[]) {
    draw_Img_with_Route(false);

    namedWindow(winName, WINDOW_NORMAL);
    imshow(winName, img);
    waitKey(1);
}


/// 工具内联函数
inline int32_t pop_front(vector<int32_t> &_q) {
    int32_t temp;

    temp = _q[0];

    for (size_t i = 0; i < _q.size() - 1; i++)
        _q[i] = _q[i + 1];
    _q.pop_back();

    return temp;

}

inline int32_t find_Element_in_List(vector<int32_t> _q, int32_t tgt) {
    for (size_t i = 0; i < _q.size(); i++)
        if (_q[i] == tgt)
            return i;

    return -1;
}
