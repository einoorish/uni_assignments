#pragma once
#include <iostream>


#ifndef AdjListGraph_H
#define AdjListGraph_H


class AdjListGraph {
public:

	struct Node {
		int index;
		Node* next;
	};

	struct Edge {
		int start, end;
	};

	int size;
	Node** head;

	AdjListGraph(int size, int edges_count, Edge edges[]);

	void addEdge(int start, int end);

	static AdjListGraph* makeRandomListGraph(int vertices_count);

	void print();

	~AdjListGraph() {
		for (int i = 0; i < size; i++)
			delete[] head[i];
		delete[] head;
	}
};

#endif 