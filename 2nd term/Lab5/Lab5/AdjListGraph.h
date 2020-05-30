#pragma once
#include <iostream>

class AdjListGraph {
public:

	struct Node {
		int index;
		int weight;
		Node* next;
	};

	struct Edge {
		int start, end, weight;
		Edge() {}
		Edge(int start, int end, int weight) :start(start), end(end), weight(weight) {};
	};

	int order;
	Node** head;

	AdjListGraph(int order, int edges_count, Edge edges[]);

	void addEdge(int start, int end, int weight);

	static AdjListGraph* makeRandomListGraph(int vertices_count);

	void print();

	~AdjListGraph() {
		for (int i = 0; i < order; i++)
			delete[] head[i];
		delete[] head;
	}
};
