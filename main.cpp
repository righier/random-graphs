#include <iostream>

#include "random.h"
#include "utils.h"
#include "args.h"
#include "randomgraphs.h"
#include "serialize.h"
#include "timer.h"

int main(int argc, char **argv) {
    auto rnd = Random(13);
    Timer timer;

    int n = 100;
    int m = 200;
    // auto edges = randomGraph(rnd, 60000, 1000000, 1.0);
    timer.start();
    Edges edges = randomGeometricGraphFast(rnd, n, m, 100, true, false);
    std::cout << "Edges generated " << timer.delta() << std::endl;

    // Edges edges = randomGraphOneLong(rnd, 10, 40, 1.0);

    timer.start();
    // Edges edges3 = randomGeometricGraph(rnd, n, m, 10, false);
    std::cout << "Edges generated " << timer.delta() << std::endl;



    timer.start();
    Graph g = edgesToGraph(edges);
    std::cout << "Graph generated " << timer.delta() << std::endl;

    timer.start();
    edgesToFile(edges, "test.edges.txt");
    std::cout << "Edges saved " << timer.delta() << std::endl;

    timer.start();
    graphToFile(g, "test.graph.txt");
    std::cout << "Graph saved " << timer.delta() << std::endl;

    timer.start();
    std::vector<Edge> edges2 = parseEdges("test.edges.txt");
    std::cout << edges2.size() << std::endl;
    std::cout << "Edges loaded " << timer.delta() << std::endl;

    timer.start();
    Graph g2 = parseGraph("test.graph.txt");
    std::cout << g2.size() << std::endl;
    std::cout << "Graph loaded " << timer.delta() << std::endl;


    // for (Edge edge: edges2) {
    //     std::cout << edge.a << " " << edge.b << " " << edge.w << std::endl;
    // }

    return 0;
}
