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
        int num;
        int connection_count;
        int *l;
        GraphPoint *dfs;
        GraphPoint *from;

        explicit GraphPoint(std::string name);
    };


    struct GraphConnection {
        GraphPoint *point;
        int price;
        GraphConnection *next;

        GraphConnection(GraphPoint *point, int price);
    };

    struct PointHolder {
        GraphPoint *point;
        PointHolder *next;
        PointHolder *prev;

        explicit PointHolder(GraphPoint *point, PointHolder *prev, PointHolder *next);
    };

    GraphPoint *head;

    bool contains(GraphPoint *p, PointHolder *holder);

    void printPointHolder (PointHolder *holder);

    void printMatrix (int n, int** c, GraphPoint** points);

    void printMarks (int k);

    PointHolder* getT(GraphPoint *p, PointHolder* S, int n, int** c, GraphPoint **points);
    PointHolder* getG(PointHolder* S, int n, int** c, GraphPoint **points);


public:

    Graph();

    bool addPoint(std::string pName);

    bool addEdge(std::string pName1, std::string pName2, int price);

    bool deleteEdge(std::string pName1, std::string pName2);

    bool deletePoint (std::string name);

    void printPoints();

    void printConnections();

    void DFS(std::string start);

    void FordMyrrBelman(std::string start);

};


#endif //GRAPH_GRAPH_H
