#include <iostream>
#include "include/graph_simple_w_floyd.h"

using namespace std;

int main() {

    MatrixXd _map;
    Point2f start(0, 0);
    Point2f end(5, 7);

    _map.resize(10, 10);
    _map << 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 0, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 1, 1, 0, 0, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 0, 1, 0, 1, 1, 1, 1, 1,
            1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1;

    __graph_simple_floyd floyd_graph(_map, start, end);

    MatrixXd floyd_result = floyd_graph.run_Floyd();
//  floyd_graph.print_RouteGrid(start, end);
    floyd_graph.print_RouteGrid();

    floyd_graph.draw_Img_with_Route((char *)"Floyd");

    waitKey(0);
    return 0;
}
