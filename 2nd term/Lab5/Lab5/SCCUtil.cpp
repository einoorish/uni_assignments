#pragma once
#include <stack> 
#include "SCCUtil.h"

using namespace std;

void SCCUtil::dfs(int u){

    visited[u] = true;
    stack.push(u);

    low_links[u] = u;
    int min = u;

    for (int v = 0; v < order; v++) {
        if (adj[u][v]) {
            if (!visited[v])
                dfs(v);
            if (low_links[v] < min) min = low_links[v];
        }
    }

    if (min < low_links[u]) {
        low_links[u] = min;
        return;
    }

    int v;
    do {
        v = stack.top();
        stack.pop();

        low_links[v] = order;
        id[v] = count;
    } while (v != u);

    count++;
}
