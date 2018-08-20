#include <iostream>
#include <eigen3/Eigen/Dense>
#include "include/graph_simple_w_dijkstra.h"

using namespace std;
using namespace Eigen;

int main() {

    MatrixXd _map;
    Point2f start(0, 0);
    Point2f end(9, 9);

    _map.resize(10, 10);
    _map << 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 0, 1, 1, 1, 1, 1;

    __graph_simple_dijkstra dijkstra_graph(_map, start, end);

    dijkstra_graph.run_Dijkstra();
    dijkstra_graph.draw(true);
    //dijkstra_graph.draw_Img_with_Route((char *)"bfs result");
    //dijkstra_graph.print_Img_with_Route();

    waitKey(0);
    return 0;
}
