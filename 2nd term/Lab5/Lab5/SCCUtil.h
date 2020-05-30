#pragma once
#include <stack> 
using namespace std;

class SCCUtil {

private:
    int order = 0, pre = 0, count = 0;
    int* id,* low_links;
    bool* visited;
    int** adj;
    stack<int> stack;

    void dfs(int u);

public:

    SCCUtil(int** adj, int order) {
        this->order = order;
        this->adj = adj;
        visited = new bool[order] {false};
        id = new int[order];
        low_links = new int[order];

        for (int u = 0; u < order; u++)
            if (!visited[u]) dfs(u);
    }

    int* getConnectedComponents() {
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
