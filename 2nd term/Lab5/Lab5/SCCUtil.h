#pragma once
#include <stack> 
using namespace std;

//This class contains method that finds all connected components
class SCCUtil {

private:
    void dfs(int u);

public:
    int order = 0, pre = 0, count = 0;
    int* id,* low_links;
    bool* visited;
    bool** adj;
    stack<int> stack;

    SCCUtil(bool** adj, int order) {
        this->order = order;
        this->adj = adj;
        visited = new bool[order] {false};
        id = new int[order];
        low_links = new int[order];

        for (int u = 0; u < order; u++)
            if (!visited[u]) dfs(u);
    }

    int* getConnectedComponents() {
        for (int u = 0; u < order; u++) 
            if (!visited[u]) dfs(u);
        return id;
    }

    int getConnectedComponentsCount() {
        return count;
    }

    bool isConnected() {
        return count == 1;
    }

    bool isAcyclic() {
        return count == order;
    }

    bool isTree(int edges_number) {
        return edges_number + 1 == order && isAcyclic();
    }
};
