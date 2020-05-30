#pragma once
#include <iostream>
#include <queue>
#include "AdjListGraph.h"
using namespace std;

class Traversal{
    static void DFSUtil(int** adj, int order, int v, bool visited[]);

public:
   
    static void DFS(int** adj, int order, int v){
        bool* visited = new bool[order] {false};
        DFSUtil(adj, order, v, visited);
    }

    static void BFS(AdjListGraph* graph, int order, int s);

    static void dijkstra(int** G, int order, int startnode);

};

