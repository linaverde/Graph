#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    g.addPoint("x1");
    g.addPoint("x3");
    g.addPoint("y");
    g.addPoint("x1");
    g.addEdge("x1", "y", 14);
    g.addEdge("x1", "x3", 20);
    g.printConnections();
    return 0;
}