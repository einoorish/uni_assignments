#pragma once
#include <stack>
#include <iostream>
using namespace std;

class TopologicalSort{

    static void topologicalSortUtil(int** adjMatrix, int order, int v, bool visited[], stack<int>& result);

public:

    static void topologicalSort(int** adjMatrix, int order);
};

