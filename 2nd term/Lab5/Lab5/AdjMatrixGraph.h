#pragma once
#include <iomanip>      // std::setw
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include <stack>

class AdjMatrixGraph {
public:
	int** adjMatrix;
	int size;

	AdjMatrixGraph(int size, int** adjMatrix) {
		this->size = size;
		this->adjMatrix = adjMatrix;
	}

	AdjMatrixGraph(int size) {
		this->size = size;
		adjMatrix = new int* [size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new int[size] {false};
		}
	}

	void addEdge(int u, int v, int weight) {
		adjMatrix[u][v] = weight;
		adjMatrix[v][u] = weight;
	}

	void addOrientedEdge(int start, int end, int weight) {
		adjMatrix[start][end] = weight;
	}

	static AdjMatrixGraph* makeRandomMatrixGraph(int size);

	void print();

	~AdjMatrixGraph() {
		for (int i = 0; i < size; i++)
			delete[] adjMatrix[i];
		delete[] adjMatrix;
	}
};
