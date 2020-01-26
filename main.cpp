#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    for (int i = 1; i < 10; i++){
        g.addPoint(std::to_string(i));
    }
    g.addEdge("1", "2", -3);
    g.addEdge("1", "5", 2);

    g.addEdge("2", "3", -5);
    g.addEdge("2", "4", 15);
    g.addEdge("2", "5", 12);

    g.addEdge("3", "8", 24);
    g.addEdge("3", "4", 8);

    g.addEdge("4", "1", 6);
    g.addEdge("4", "6", 18);
    g.addEdge("4", "7", 4);
    g.addEdge("4", "9", 11);
    g.addEdge("4", "3", 8);

    g.addEdge("5", "4", -7);
    g.addEdge("5", "2", 12);
    g.addEdge("5", "6", 20);

    g.addEdge("6", "5", 20);
    g.addEdge("6", "7", 9);

    g.addEdge("7", "3", -10);
    g.addEdge("7", "4", 4);
    g.addEdge("7", "8", 16);
    g.addEdge("7", "6", 9);

    g.addEdge("8", "3", 24);
    g.addEdge("8", "7", 16);
    g.addEdge("8", "9", 22);

    g.addEdge("9", "4", 11);
    g.addEdge("9", "6", -13);


    //g.addEdge("5", "6", 0);

    g.printConnections();

    g.FordMyrrBelman("1");


    return 0;
}