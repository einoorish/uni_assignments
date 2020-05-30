#include "AdjListGraph.h"

AdjListGraph::AdjListGraph(int order, int edges_count, Edge edges[])
{
	head = new Node * [order]();
	this->order = order;

	for (int i = 0; i < edges_count; i++) {
		int start = edges[i].start;
		int end = edges[i].end;

		Node* newNode = new Node;
		newNode->index = end;
		newNode->weight = edges[i].weight;
		newNode->next = head[start];

		head[start] = newNode;
	}
}

void AdjListGraph::addEdge(int start, int end, int weight) {
	if (weight == 0) std::cout << "Edge weight cannot be 0" << std::endl;
	else {
		Node* newNode = new Node;
		newNode->index = end;
		newNode->next = head[start];
		newNode->weight = weight;

		if (newNode->next == nullptr || newNode->index != newNode->next->index)
			head[start] = newNode;
	}
}

void AdjListGraph::print(){
	for (int i = 0; i < order; i++) {
		Node* current = head[i];

		while (current != nullptr) {
			std::cout << "[(" << i << ";" << current->index << "): "<<current->weight<< "] ";
			current = current->next;
		}
		std::cout << std::endl;
	}
}

AdjListGraph* AdjListGraph::makeRandomListGraph(int vertices_count){

	AdjListGraph::Edge* edges = new AdjListGraph::Edge[vertices_count];

	for (int i = 0; i < vertices_count; i++) {
		srand(i * vertices_count);

		AdjListGraph::Edge newEdge = AdjListGraph::Edge();
		newEdge.start = i;
		newEdge.end = rand() % vertices_count;
		newEdge.weight = rand() % 9 + 1;

		edges[i] = newEdge;
	}

	AdjListGraph* graph = new AdjListGraph(vertices_count, vertices_count, edges);


	//randomly add up to 5 edges:
	for (int i = 0; i < vertices_count; i++) {
		srand(i * vertices_count);
		for (int j = 0; j < rand() % 6; j++) {
			srand(i * j);
			graph->addEdge(i, rand() % vertices_count, rand()%50+2);
		}
	}

	return graph;
}
