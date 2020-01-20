#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    for (int i = 1; i < 7; i++){
        g.addPoint(std::to_string(i));
    }
    g.addEdge("1", "3", 0);
    g.addEdge("1", "2", 0);
    g.addEdge("3", "6", 0);
    g.addEdge("2", "4", 0);
    g.addEdge("2", "5", 0);
    g.addEdge("1", "2", 0);
    //g.addEdge("5", "6", 0);

    g.printConnections();

    g.DFS("4");
    g.DFS("2");

    return 0;
}