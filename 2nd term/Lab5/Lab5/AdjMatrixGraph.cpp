#include "AdjMatrixGraph.h"
#include <iostream>
using namespace std;

AdjMatrixGraph* AdjMatrixGraph::makeRandomMatrixGraph(int size){

	bool** matrix = new bool* [size];
	int* values = new int[size];

	for (int i = 0; i < size; i++) {
		srand(i);
	}

	for (int i = 0; i < size; i++) {
		matrix[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			srand(j * i + i);
			matrix[i][j] = rand() % 2;
		}

	}

	return new AdjMatrixGraph(size, matrix);
}


void AdjMatrixGraph::printGraph(){
	int width = (int)log10((double)size) + 1;

	cout << setw(width) << "    " << setw(width);
	for (int v = 0; v < size; ++v) {
			cout << "[" << setw(width) << v << "]";
	}
	cout << endl;

	for (int v = 0; v < size; ++v) {
		cout << "[" << setw(width) << v << "]  ";

		for (int u = 0; u < size; u++)
			cout << setw(width) << adjMatrix[v][u] << "  ";
		cout << endl;
	}
}
