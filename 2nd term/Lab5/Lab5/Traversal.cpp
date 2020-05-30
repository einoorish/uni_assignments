#include "Traversal.h"

void Traversal::DFSUtil(int** adj, int order, int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";

    for (int i = 0; i < order; ++i)
        if (!visited[i] && adj[v][i] != 0)
            DFSUtil(adj, order, i, visited);
}

void Traversal::BFS(AdjListGraph* graph, int order, int s) {
    bool* visited = new bool[order] {};
    queue<int> queue;

    visited[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        cout << s << " ";

        auto temp = graph->head[s];
        while (temp) {
            if (!visited[temp->index]) {
                visited[temp->index] = true;
                queue.push(temp->index);
            }
            temp = temp->next;
        }
    }
}

void Traversal::dijkstra(int** G, int order, int startnode) {
    int* distance = new int[order], * pred = new int[order];
    int* visited = new int[order], count, mindistance, nextnode, i, j;

    for (i = 0; i < order; i++) {
        if (G[startnode][i] == 0) distance[i] = INT_MAX;
        else distance[i] = G[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < order - 1) {
        mindistance = INT_MAX;
        for (i = 0; i < order; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        visited[nextnode] = 1;
        for (i = 0; i < order; i++) {
            if (!visited[i] && G[nextnode][i] != 0)
                if (mindistance + G[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + G[nextnode][i];
                    pred[i] = nextnode;
                }
        }
        count++;
    }
    for (i = 0; i < order; i++)
        if (i != startnode) {
            cout << endl << "Distance to node " << i << " = " << distance[i];
            cout << "\nPath: " << i;
            j = i;
            do {
                j = pred[j];
                cout << "<-" << j;
            } while (j != startnode);
        }
}
