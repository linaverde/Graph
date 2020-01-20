//
// Created by Polina on 23.12.2019.
//

#include "Graph.h"
#include <iostream>
#include <limits>
#include <cmath>

#define infinity std::numeric_limits<int>::max();

Graph::GraphPoint::GraphPoint(std::string name) {
    this->name = name;
    this->connected = nullptr;
    this->next = nullptr;
    this->num = 0;
    this->connection_count = 0;
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
    if (pName1 == pName2) {
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
    if (p1 == nullptr || p2 == nullptr) {
        return false;
    }
    auto *con = p1->connected;
    while (con != nullptr) {
        if (con->point->name == p2->name) {
            return false;
        }
        con = con->next;
    }
    con = new GraphConnection(p2, price);
    con->next = p1->connected;
    p1->connected = con;
    //p1->connection_count++;
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
    if (point == nullptr) {
        return false;
    }
    GraphPoint *curr = head;
    while (curr != nullptr) {
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
                if (con->next != nullptr && con->next->point == point) {
                    GraphConnection *tempCon = con->next->next;
                    delete (con->next);
                    con->next = tempCon;
                }
            }
        }
        curr = curr->next;
    }

    if (head == point) {
        head = point->next;
        delete (point);
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
    if (pName1 == pName2) {
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
    if (p1 == nullptr || p2 == nullptr) {
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
            if (con->next != nullptr && con->next->point == p2) {
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

void Graph::DFS(std::string start) {

    ///НД - это следующая за текущей вершина!
    ///При перестроении меняется
    ///Если выписывать проход сразу - фиктивную можно не вводить
    ///для моей структуры массивы не нужны
    ///даже число вершин в связях хранить не обязательно, просто брать следующую за текущей по списку
    GraphPoint *sp = head;
    while (sp != nullptr) {
        if (sp->name == start) {
            break;
        } else {
            sp = sp->next;
        }
    }
    if (sp == nullptr)
        return;
    std::cout << "DFS: ";

    //очищаем метки
    GraphPoint *curr = head;
    while (curr != nullptr) {
        curr->dfs = nullptr;
        curr->from = nullptr;
        curr = curr->next;
    }

    //Добавляем фиктивную вершину
    GraphPoint *q = new GraphPoint("Q0");
    q->from = nullptr;
    q->dfs = sp;
    q->connected = new GraphConnection(sp, 0);


    //Создаем фиктивную вершину для пометок
    GraphPoint *temp = new GraphPoint("temp");
    temp->dfs = temp;
    //обход

    curr = sp;
    sp->from = q;
    do {
        if (curr->dfs == nullptr) { //если текущая вершина не помечена, выписываем её в обход и переходим в нее
            std::cout << curr->name << ", ";
            if (curr->connected != nullptr) {
                curr->dfs = curr->connected->point;
                curr->dfs->from = curr;
                curr = curr->dfs;
            } else {
                curr->dfs = curr;
                //curr->from = curr;
            }
        } else { //если текущая вершина помеченя, то возвращаемся на шаг назад и меняем пометку
            curr = curr->from;
            GraphConnection *next = curr->connected;
            while (next->point != curr->dfs) {
                next = next->next;
            }
            next = next->next;
            if (next != nullptr) { //если есть, на что поменять из пометку
                curr->dfs = next->point;
                curr->dfs->from = curr;
                curr = curr->dfs;
            }
            //если связи кончились, то на след итерации снова поднимемся на уровень выше
        }
    } while (curr != q); // обход продолжается, пока мы не пришли в фиктивную вершину.

    std::cout << "that's all" << std::endl;


}

Graph::PointHolder::PointHolder(GraphPoint *point, PointHolder *prev, PointHolder *next) {
    this->point = point;
    this->next = next;
    this->prev = prev;
}


void Graph::FordMyrrBelman(std::string start) {

    //ищем начальную вершину
    GraphPoint *sp = head;
    while (sp != nullptr) {
        if (sp->name == start) {
            break;
        } else {
            sp = sp->next;
        }
    }
    if (sp == nullptr) //если её нет, алгоритм не рабочий
        return;

    //нумеруем вершины
    int n = 0;
    GraphPoint *curr = head;
    while (curr != nullptr) {
        n++;
        curr->num = n - 1;
        curr = curr->next;
    }

    GraphPoint *points[n]; //создаем массив вершин для быстрого доступа по номеру

    curr = head;
    while (curr != nullptr) {
        points[curr->num] = curr;
        curr = curr->next;
    }

    int **c = new int *[n]; //матрица весов
    for (int i = 0; i < n; i++) {
        c[i] = new int[n];
    }

    //заполняем матрицу весов бесконечностью
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = infinity;
        }
    }

    //curr = head;

    //while (curr != nullptr){
    for (int i = 0; i < n; i++) {
        GraphConnection *con = points[i]->connected;
        while (con != nullptr) {
            c[curr->num][con->point->num] = con->price;
            con = con->next;
        }
        //создаем для каждой вершины массив меток из н+1
        points[i]->l = new int[n + 1];
        //заполняем метки бесконечностью
        for (int j = 0; j < n + 1; j++) {
            points[i]->l[j] = infinity;
        }
    }

    //формируем начальное множество S
    auto *S = new PointHolder(nullptr, nullptr, nullptr);
    PointHolder *currHolder = S;
    GraphConnection *con = sp->connected;
    while (con != nullptr) {
        currHolder->point = con->point;
        currHolder = new PointHolder(nullptr, currHolder, nullptr);
        currHolder = currHolder->next;
        con = con->next;
    }
    currHolder = currHolder->prev;
    delete (currHolder->next);
    currHolder->next = nullptr;

    int k = 0;

    //изменяем метки для всех вершин, достижимых из sp
    sp->l[0] = 0;
    currHolder = S;
    while (currHolder != nullptr) {
        currHolder->point->l[0] = c[sp->num][currHolder->point->num];
        currHolder = currHolder->next;
    }

    //обновление меток

    //строим Г(S)
    PointHolder *G = getGFromS(S);

    //изменяем метки
    for (int i = 0; i < n; i++) {
        if (contains(points[i], G)) { //если содержится, то изменяем метку
            //строим Ti

        } else { //иначе копируем предыдущую
            points[i]->l[k + 1] = points[i]->l[k];
        }
    }


}

bool Graph::contains(GraphPoint *p, PointHolder *holder) {
    PointHolder *curr = holder;
    while (curr != nullptr) {
        if (curr->point == p) {
            return true;
        } else {
            curr = curr->next;
        }
    }
    return false;
}


Graph::PointHolder *Graph::getGFromS(PointHolder *S) {
    PointHolder *newHolder = new PointHolder(nullptr, nullptr, nullptr);
    PointHolder *currHolder = newHolder;
    PointHolder *currS = S;
    while (currS != nullptr) {
        GraphConnection *con = currS->point->connected;
        while (con != nullptr) {
            currHolder->point = con->point;
            currHolder->next = new PointHolder(nullptr, currHolder, nullptr);
            currHolder = currHolder->next;
            con = con->next;
        }
        currS = currS->next;
    }
    currHolder = currHolder->prev;
    delete (currHolder->next);
    currHolder->next = nullptr;

    return newHolder;
}
