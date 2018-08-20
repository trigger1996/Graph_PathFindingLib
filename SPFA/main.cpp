#include <iostream>
#include "include/graph_simple_w_spfa.h"

using namespace std;

int main() {

    MatrixXd _map;
    Point2i start(0, 0);
    Point2i end(9, 9);

    _map.resize(10, 10);
    _map << 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 0, 1, 0, 0, 1, 1, 1, 1,
            1, 0, 0, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1;

    __graph_simple_spfa spfa_graph(_map, start, end);

    spfa_graph.run_SPFA();
    spfa_graph.draw_Img_with_Route(true);

    waitKey(0);
    return 0;
}
