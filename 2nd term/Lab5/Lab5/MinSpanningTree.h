#pragma once
#include <queue>
using namespace std;

class MinSpanningTree{ 

    int** MST;
    int weight;

    struct Edge {
        int to, cost, from;

        Edge(int from, int to, int cost) {
            this->from = from;
            this->to = to;
            this->cost = cost;
        }
    };

    friend bool operator<(const Edge& lhs, const Edge& rhs) {
        return lhs.cost - rhs.cost;
    }


    void Prim(int** graph, int order);

public:  

    MinSpanningTree(int** graph, int order) {
        Prim(graph, order);
    }

    int** getMST() { return MST; }
    int getMSTweight() { return weight; }

};

