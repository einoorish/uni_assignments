#include <iostream>
#include "AdjListGraph.h"
#include "AdjMatrixGraph.h"
#include "SCCUtil.h"

using namespace std;


AdjListGraph* MatrixToListGraph(AdjMatrixGraph* graph) {

	AdjListGraph::Edge* edges = new AdjListGraph::Edge[graph->size * graph->size];
	int edges_count = 0;

	for (int i = 0; i < graph->size; i++) {
		for (int j = 0; j < graph->size; j++) {
			if (graph->adjMatrix[i][j]) {
				AdjListGraph::Edge newEdge = AdjListGraph::Edge();
				newEdge.start = i;
				newEdge.end = j;
				edges[edges_count] = newEdge;
				edges_count++;
			}
		}
	}

	return new AdjListGraph(graph->size, edges_count, edges);
}


AdjMatrixGraph* ListToMatrixGraph(AdjListGraph* graph) {
	bool** adjMatrix = new bool*[graph->size];

	for (int i = 0; i < graph->size; i++) {
		adjMatrix[i] = new bool[graph->size]{ 0 };
		AdjListGraph::Node* temp = graph->head[i];
		while (temp != nullptr) {
			adjMatrix[i][temp->index] = 1;
			temp = temp->next;
		}
	}

	return new AdjMatrixGraph(graph->size, adjMatrix);
}



void adjMatrixGraph_TEST_Block1_2() {
	cout << endl<< "\n-----------------------------------------------------------\n";
	AdjMatrixGraph* graph;

	cout << "GRAPH 1 (both order and edges are passed to consructor) \n" << endl;
	int order = 3;
	bool* matrix[] = {new bool[order] {0, 1, 1},
					  new bool[order] {0, 0, 0},
					  new bool[order] {1, 0, 0} };
	graph = new AdjMatrixGraph(order, matrix);

	graph->printGraph();

	SCCUtil* SCCHelper = new SCCUtil(matrix, order);
	int* res = SCCHelper->getConnectedComponents();
	cout << "Number of connected components: " << SCCHelper->getConnectedComponentsCount() << endl;
	cout << "Mapping of connected components: ";
	for (int i = 0; i < order; i++)
		cout << res[i] << " ";


	cout << endl << "\nGRAPH 2 (only order is passed to constructor, edges added later)\n" << endl ;

	order = 8;
	graph = new AdjMatrixGraph(order);
	graph->addOrientedEdge(0, 1);
	graph->addOrientedEdge(1, 2);
	graph->addOrientedEdge(2, 0);
	graph->addOrientedEdge(3, 4);
	graph->addEdge(3, 7);
	graph->addOrientedEdge(4, 5);
	graph->addOrientedEdge(5, 0);
	graph->addOrientedEdge(5, 6);
	graph->addOrientedEdge(6, 0);
	graph->addOrientedEdge(6, 2);
	graph->addOrientedEdge(6, 4);
	graph->addOrientedEdge(7, 5);


	graph->printGraph();

	SCCHelper = new SCCUtil(graph->adjMatrix, order);
	res =  SCCHelper->getConnectedComponents();

	cout << "Number of connected components: " << SCCHelper->getConnectedComponentsCount() << endl;
	cout << "Mapping of connected components: ";
	for (int i = 0; i < order; i++) 
		cout << res[i] << " ";
	
	
	cout << endl << "\nMATRIX TO LIST: \n"<<endl;

	MatrixToListGraph(graph)->print();


	cout << endl << "\nGRAPH 3 (random graph)\n" << endl;
	
	AdjMatrixGraph::makeRandomMatrixGraph(11)->printGraph();

}

void adjListGraph_TEST_Block1_2() {
	cout << endl << "\n-----------------------------------------------------------\n";
	cout << "GRAPH 1 (both order and edges are passed to consructor) \n" << endl;

	AdjListGraph::Edge edges[] = {
		{0,1},{0,2},{1,4},{2,3}
	};

	int order = 5;
	int edges_number = sizeof(edges) / sizeof(edges[0]);

	AdjListGraph* graph = new AdjListGraph(order, edges_number, edges);

	graph->print();

	cout << "LIST TO MATRIX: \n" << endl;

	AdjMatrixGraph* matrixGraph = ListToMatrixGraph(graph);
	matrixGraph->printGraph();

	SCCUtil* sccHelper = new SCCUtil(matrixGraph->adjMatrix, order);
	int* res = sccHelper->getConnectedComponents();

	cout << "Number of connected components: " << sccHelper->getConnectedComponentsCount() << endl;
	cout << "Mapping of connected components: ";
	for (int i = 0; i < order; i++)
		cout << res[i] << " ";
	cout << endl << "Is connected? " << sccHelper->isConnected();
	cout << endl << "Is acyclic? " << sccHelper->isAcyclic();
	cout << endl << "Is tree? " << sccHelper->isTree(edges_number);

	//

	cout << endl << "\nAdding edges (1, 2), (3, 1), (4, 3):  \n";
	graph->addEdge(1, 2);
	graph->addEdge(3, 1);
	graph->addEdge(4, 3);

	graph->print();

	matrixGraph = ListToMatrixGraph(graph);
	sccHelper = new SCCUtil(matrixGraph->adjMatrix, order);
	res = sccHelper->getConnectedComponents();

	cout << "New number of connected components: " << sccHelper->getConnectedComponentsCount() << endl;
	cout << "New mapping of connected components: ";
	for (int i = 0; i < order; i++)
		cout << res[i] << " ";
	cout << endl << "Is connected? " << sccHelper->isConnected();
	cout << endl << "Is acyclic? " << sccHelper->isAcyclic();

	edges_number = sizeof(edges) / sizeof(edges[0]);
	cout << endl << "Is tree? " << sccHelper->isTree(edges_number);

	//

	cout << endl << "\nGRAPH 2 (random graph) \n" << endl;
	AdjListGraph::makeRandomListGraph(9)->print();

}

int main(){
	adjMatrixGraph_TEST_Block1_2();
	adjListGraph_TEST_Block1_2();
	return 0;
}
