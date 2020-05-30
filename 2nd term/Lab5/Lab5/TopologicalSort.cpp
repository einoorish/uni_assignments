#include "TopologicalSort.h"

void TopologicalSort::topologicalSortUtil(int** adjMatrix, int order, int v, bool visited[], stack<int>& result){
    visited[v] = true;

    for (int i = 0; i < order; i++) {
        if (!visited[i] && adjMatrix[v][i] != 0)
            topologicalSortUtil(adjMatrix, order, i, visited, result);
    }

    result.push(v);
}

void TopologicalSort::topologicalSort(int** adjMatrix, int order){
    stack<int> result;

    bool* visited = new bool[order] {false};
    for (int i = 0; i < order; i++)
        if (visited[i] == false)
            topologicalSortUtil(adjMatrix, order, i, visited, result);

    for(int i = 0; i < order; i++)
        if (visited[i] == false) {
            cout << "Graph is not connected.";
            return;
        }

    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
}
