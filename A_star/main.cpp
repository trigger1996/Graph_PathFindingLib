#include <iostream>
#include "../graph_lib/include/graph_simple.h"
#include "include/graph_simple_w_A_star.h"

using namespace std;
using namespace cv;
using namespace Eigen;

int main() {

    MatrixXd _map;
    Point2f start(0, 0);
    Point2f end(5, 7);                                          // (9, 9), (5, 7)

    _map.resize(10, 10);
    _map << 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 0, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 0, 1, 0, 0, 1, 1, 1, 1,
            1, 0, 0, 1, 0, 1, 1, 1, 1, 1,
            1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1;

    __graph_simple_A_star Astar_graph(_map, start, end);

    Astar_graph.run_Astar();

    Astar_graph.draw_Img_with_Route(true);
    Astar_graph.print_Img_with_Route();

    waitKey(0);
    return 0;
}
