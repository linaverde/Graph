//
// Created by Polina on 23.12.2019.
//

#include "Graph.h"
#include <iostream>

Graph::GraphPoint::GraphPoint(std::string &name) {
    this->name = name;
    this->connected = nullptr;
    this->next = nullptr;
}

Graph::GraphConnection::GraphConnection(GraphPoint *point, int price) {
    this->point = point;
    this->price = price;
    this->next = nullptr;
}

Graph::Graph() {
    this->head = nullptr;
}


bool Graph::addPoint(std::string pName) {
    GraphPoint *curr = head;
    while (curr != nullptr) {
        if (curr->name == pName) {
            return false;
        } else {
            curr = curr->next;
        }
    }
    auto *newPoint = new GraphPoint(pName);
    newPoint->next = head;
    head = newPoint;
    return true;
}

bool Graph::addEdge(std::string pName1, std::string pName2, int price) {
    if (pName1 == pName2){
        return false;
    }
    GraphPoint *p1 = nullptr, *p2 = nullptr;
    GraphPoint *curr = head;
    while (curr != nullptr) {
        if (curr->name == pName1) {
            p1 = curr;
        } else if (curr->name == pName2) {
            p2 = curr;
        }
        curr = curr->next;
    }
    if (p1 == nullptr || p2 == nullptr){
        return false;
    }
    auto *con = p1->connected;
    while (con != nullptr){
        if (con->point->name == p2->name){
            return false;
        }
        con = con->next;
    }
    con = new GraphConnection(p2, price);
    con->next = p1->connected;
    p1->connected = con;
    return true;
}

bool Graph::deletePoint(std::string name) {
    GraphPoint *point = head;
    while (point != nullptr) {
        if (point->name == name) {
            break;
        } else {
            point = point->next;
        }
    }
    if (point == nullptr){
        return false;
    }
    GraphPoint *curr = head;
    while (curr != nullptr){
        GraphConnection *con = curr->connected;
        if (con != nullptr) {
            if (con->point == point) {
                GraphConnection *tempCon = con->next;
                delete (curr->connected);
                curr->connected = tempCon;
            } else {
                while (con->next != nullptr) {
                    if (con->next->point == point) {
                        break;
                    }
                    con = con->next;
                }
                if (con->next->point == point) {
                    GraphConnection *tempCon = con->next->next;
                    delete (con->next);
                    con->next = tempCon;
                }
            }
        }
        curr = curr->next;
    }

    if (head == point){
        head = point->next;
        delete(point);
    } else {
        curr = head;
        while (curr->next != point) {
            curr = curr->next;
        }
        curr->next = point->next;
        delete (point);
    }
    return true;

}

bool Graph::deleteEdge(std::string pName1, std::string pName2) {
    if (pName1 == pName2){
        return false;
    }
    GraphPoint *p1 = nullptr, *p2 = nullptr;
    GraphPoint *curr = head;
    while (curr != nullptr) {
        if (curr->name == pName1) {
            p1 = curr;
        } else if (curr->name == pName2) {
            p2 = curr;
        }
        curr = curr->next;
    }
    if (p1 == nullptr || p2 == nullptr){
        return false;
    }
    auto *con = p1->connected;
    if (con != nullptr) {
        if (con->point == p2) {
            GraphConnection *tempCon = con->next;
            delete (p1->connected);
            p1->connected = tempCon;
            return true;
        } else {
            while (con->next != nullptr) {
                if (con->next->point->name == p2->name) {
                    break;
                }
                con = con->next;
            }
            if (con->next->point == p2) {
                GraphConnection *tempCon = con->next->next;
                delete (con->next);
                con->next = tempCon;
                return true;
            }
        }
    }
    return false;
}

void Graph::printPoints() {
    std::cout << "Graph contains:" << std::endl;
    GraphPoint *curr = this->head;
    while (curr != nullptr) {
        std::cout << curr->name << ' ';
        curr = curr->next;
    }
    std::cout << std::endl << "----------" << std::endl;
}

void Graph::printConnections() {
    std::cout << "Graph contains:" << std::endl;
    GraphPoint *curr = this->head;
    while (curr != nullptr) {
        std::cout << curr->name << ' ';
        curr = curr->next;
    }
    std::cout << std::endl << "Connections:" << std::endl;
    curr = this->head;
    while (curr != nullptr) {
        GraphConnection *connect = curr->connected;
        std::cout << "Point " << curr->name << " connected with: " << std::endl;
        while (connect != nullptr) {
            std::cout << connect->point->name << "(" << connect->price << "), ";
            connect = connect->next;
        }
        std::cout << std::endl;
        curr = curr->next;
    }
    std::cout << "----------" << std::endl;
}