//
// Created by Polina on 23.12.2019.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <string>

class Graph {

    struct GraphPoint;
    struct GraphConnection;

    struct GraphPoint {
        std::string name;
        GraphConnection *connected;
        GraphPoint *next;

        explicit GraphPoint(std::string &name);
    };


    struct GraphConnection {
        GraphPoint *point;
        int price;
        GraphConnection *next;

        GraphConnection(GraphPoint *point, int price);
    };

    GraphPoint *head;

public:

    Graph();

    bool addPoint(std::string pName);

    bool addEdge(std::string pName1, std::string pName2, int price);

    bool deleteEdge(std::string pName1, std::string pName2);

    bool deletePoint (std::string name);

    void printPoints();

    void printConnections();




};


#endif //GRAPH_GRAPH_H
