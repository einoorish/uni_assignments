#pragma once
#include <iomanip>      // std::setw
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

#include "AdjListGraph.h"
#include <stack>

class AdjMatrixGraph {
public:
	bool** adjMatrix;
	int size;

	AdjMatrixGraph(int size, bool** adjMatrix) {
		this->size = size;
		this->adjMatrix = adjMatrix;
	}

	AdjMatrixGraph(int size) {
		this->size = size;
		adjMatrix = new bool* [size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new bool[size] {false};
		}
	}

	void addEdge(int u, int v) {
		adjMatrix[u][v] = true;
		adjMatrix[v][u] = true;
	}

	void addOrientedEdge(int start, int end) {
		adjMatrix[start][end] = true;
	}

	static AdjMatrixGraph* makeRandomMatrixGraph(int size);

	void printGraph();

	~AdjMatrixGraph() {
		for (int i = 0; i < size; i++)
			delete[] adjMatrix[i];
		delete[] adjMatrix;
	}
};
