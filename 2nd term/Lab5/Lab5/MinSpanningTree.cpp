#include "MinSpanningTree.h"

void MinSpanningTree::Prim(int** graph, int order){
    MST = new int* [order];
    long visitedNodes = 1;
    bool* connected = new bool[order] {false};
    connected[0] = true;
    int prev = 0;

    auto compare = [](Edge a, Edge b) { return a.cost > b.cost; };
    priority_queue<Edge, std::vector<Edge>, decltype(compare)>  pq(compare);

    for (int i = 1; i < order; i++)
        if (graph[0][i] != 0)
            pq.push(Edge(0, i, graph[0][i]));


    while (visitedNodes != order && !pq.empty()) {
        Edge edge = pq.top();   pq.pop();

        if (!connected[edge.to]) {
            for (int i = 0; i < order; i++)
                if (!connected[i] && graph[edge.to][i] != 0)
                    pq.push(Edge(edge.to, i, graph[edge.to][i]));

            connected[edge.to] = true;
            weight += edge.cost;
            MST[visitedNodes - 1] = new int[2];
            MST[visitedNodes - 1][0] = edge.from;
            MST[visitedNodes - 1][1] = edge.to;
            visitedNodes++;
        } prev = edge.to;
    }

}
