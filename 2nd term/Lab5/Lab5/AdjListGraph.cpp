#include "AdjListGraph.h"

AdjListGraph::AdjListGraph(int size, int edges_count, Edge edges[])
{
	head = new Node * [size]();
	this->size = size;

	for (int i = 0; i < edges_count; i++) {
		int start = edges[i].start;
		int end = edges[i].end;

		Node* newNode = new Node;
		newNode->index = end;
		newNode->next = head[start];


		head[start] = newNode;
	}
}

void AdjListGraph::addEdge(int start, int end) {
	//TODO: add check for repeating {start; end; x} edges
	Node* newNode = new Node;
	newNode->index = end;
	newNode->next = head[start];

	if(newNode->next == nullptr || newNode->index != newNode->next->index)
	head[start] = newNode;
}

void AdjListGraph::print(){
	for (int i = 0; i < size; i++) {
		Node* current = head[i];

		while (current != nullptr) {
			std::cout << "(" << i << ";" << current->index << ")";
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

		edges[i] = newEdge;
	}

	AdjListGraph* graph = new AdjListGraph(vertices_count, vertices_count, edges);


	//randomly add up to 5 edges:
	for (int i = 0; i < vertices_count; i++) {
		srand(i * vertices_count);
		for (int j = 0; j < rand() % 6; j++) {
			srand(i * j);
			graph->addEdge(i, rand() % vertices_count);
		}
	}

	return graph;
}
