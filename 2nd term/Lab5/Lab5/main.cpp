#include <iostream>
#include <thread>
#include <chrono>
#include "AdjListGraph.h"
#include "AdjMatrixGraph.h"
#include "SCCUtil.h"
#include "Traversal.h"
#include "TopologicalSort.h"
#include "MinSpanningTree.h"

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
				newEdge.weight = graph->adjMatrix[i][j];
				edges[edges_count] = newEdge;
				edges_count++;
			}
		}
	}

	return new AdjListGraph(graph->size, edges_count, edges);
}

AdjMatrixGraph* ListToMatrixGraph(AdjListGraph* graph) {
	int** adjMatrix = new int*[graph->order];

	for (int i = 0; i < graph->order; i++) {
		adjMatrix[i] = new int[graph->order]{ 0 };
		AdjListGraph::Node* temp = graph->head[i];
		while (temp != nullptr) {
			adjMatrix[i][temp->index] = temp->weight;
			temp = temp->next;
		}
	}

	return new AdjMatrixGraph(graph->order, adjMatrix);
}


void adjMatrixGraph_DEMO_Block1_2() {
	cout << endl<< "\n-----------------------------------------------------------\n";
	AdjMatrixGraph* graph;

	cout << "GRAPH 1 (both order and edges are passed to consructor) \n" << endl;
	int order = 3;
	int* matrix[] =  {new int[order] {0, 1, 1},
					  new int[order] {0, 0, 0},
					  new int[order] {1, 0, 0} };
	graph = new AdjMatrixGraph(order, matrix);

	graph->print();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	SCCUtil* SCCHelper = new SCCUtil(matrix, order);
	int* res = SCCHelper->getConnectedComponents();
	cout << "Number of connected components: " << SCCHelper->getConnectedComponentsCount() << endl;
	cout << "Mapping of connected components: ";
	for (int i = 0; i < order; i++)
		cout << res[i] << " ";


	std::this_thread::sleep_for(std::chrono::seconds(3));
	cout << endl << "\n\nGRAPH 2 (only order is passed to constructor, edges added later)\n" << endl ;

	order = 8;
	graph = new AdjMatrixGraph(order);
	graph->addOrientedEdge(0, 1, 3);
	graph->addOrientedEdge(1, 2, 4);
	graph->addOrientedEdge(2, 0, 5);
	graph->addOrientedEdge(3, 4, 1);
	graph->addEdge(3, 7, 1);
	graph->addOrientedEdge(4, 5, 1);
	graph->addOrientedEdge(5, 0, 4);
	graph->addOrientedEdge(5, 6, 2);
	graph->addOrientedEdge(6, 0, 4);
	graph->addOrientedEdge(6, 2, 8);
	graph->addOrientedEdge(6, 4, 9);
	graph->addOrientedEdge(7, 5, 1);


	graph->print();

	std::this_thread::sleep_for(std::chrono::seconds(3));
	SCCHelper = new SCCUtil(graph->adjMatrix, order);
	res =  SCCHelper->getConnectedComponents();

	cout << "Number of connected components: " << SCCHelper->getConnectedComponentsCount() << endl;
	cout << "Mapping of connected components: ";
	for (int i = 0; i < order; i++) 
		cout << res[i] << " ";
	

	std::this_thread::sleep_for(std::chrono::seconds(4));
	cout << endl << "\nMATRIX TO LIST: \n"<<endl;

	MatrixToListGraph(graph)->print();


	std::this_thread::sleep_for(std::chrono::seconds(4));
	cout << endl << "\nGRAPH 3 (random graph)\n" << endl;
	
	AdjMatrixGraph::makeRandomMatrixGraph(11)->print();

	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void adjListGraph_DEMO_Block1_2() {
	cout << endl << "\n-----------------------------------------------------------\n";
	cout << "GRAPH 1 (both order and edges are passed to consructor) \n" << endl;

	AdjListGraph::Edge edges[] = {
		AdjListGraph::Edge(0,1,6), AdjListGraph::Edge(0,2,2), AdjListGraph::Edge(1,4,4), AdjListGraph::Edge(2,3,1)
	};

	int order = 5;
	int edges_number = sizeof(edges) / sizeof(edges[0]);

	AdjListGraph* graph = new AdjListGraph(order, edges_number, edges);

	graph->print();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	cout << "LIST TO MATRIX: \n" << endl;

	AdjMatrixGraph* matrixGraph = ListToMatrixGraph(graph);
	matrixGraph->print();
	
	std::this_thread::sleep_for(std::chrono::seconds(3));

	SCCUtil* sccHelper = new SCCUtil(matrixGraph->adjMatrix, order);
	int* res = sccHelper->getConnectedComponents();

	cout << "Number of connected components: " << sccHelper->getConnectedComponentsCount() << endl;
	cout << "Mapping of connected components: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	for (int i = 0; i < order; i++)
		cout << res[i] << " ";
	cout << endl << "Is connected? " << sccHelper->isConnected();
	cout << endl << "Is acyclic? " << sccHelper->isAcyclic();
	cout << endl << "Is tree? " << sccHelper->isTree(edges_number);

	std::this_thread::sleep_for(std::chrono::seconds(4));

	cout << endl << "\nAdding edges (1, 2), (3, 1), (4, 3):  \n";
	graph->addEdge(1, 2, 1);
	graph->addEdge(3, 1, 2);
	graph->addEdge(4, 3, 3);

	graph->print();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	matrixGraph = ListToMatrixGraph(graph);
	sccHelper = new SCCUtil(matrixGraph->adjMatrix, order);
	res = sccHelper->getConnectedComponents();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "New number of connected components: " << sccHelper->getConnectedComponentsCount() << endl;
	cout << "New mapping of connected components: ";
	for (int i = 0; i < order; i++)
		cout << res[i] << " ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << endl << "Is connected? " << sccHelper->isConnected();
	cout << endl << "Is acyclic? " << sccHelper->isAcyclic();

	edges_number = sizeof(edges) / sizeof(edges[0]);
	cout << endl << "Is tree? " << sccHelper->isTree(edges_number);

	std::this_thread::sleep_for(std::chrono::seconds(4));

	cout << endl << "\nGRAPH 2 (random graph) \n" << endl;
	AdjListGraph::makeRandomListGraph(9)->print();

	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void adjMatrixGraph_DEMO_Block3_6() {
	cout << endl << "\n-----------------------------------------------------------\n";
	cout << "GRAPH 1  \n" << endl;
	int order = 3;
	int* matrix[] = { new int[order] {0, 1, 0},
					  new int[order] {0, 0, 0},
					  new int[order] {1, 0, 0} };
	AdjMatrixGraph* graph = new AdjMatrixGraph(order, matrix);
	graph->print();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << endl << "DFS for node at index 0: " << endl;
	Traversal::DFS(matrix, order, 0);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << endl << "Topological Sort: ";
	TopologicalSort::topologicalSort(matrix, 3);

	std::this_thread::sleep_for(std::chrono::seconds(4));
	cout << "\n\nGRAPH 2  \n" << endl;

	AdjListGraph::Edge edges[] = {
		AdjListGraph::Edge(0,0,2), AdjListGraph::Edge(0,2,1), AdjListGraph::Edge(1,4,4), AdjListGraph::Edge(2,3,3)
	};

	order = 5;
	int edges_number = sizeof(edges) / sizeof(edges[0]);

	AdjListGraph* graph2 = new AdjListGraph(order, edges_number, edges);

	graph2->print();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "Topological Sort: ";
	TopologicalSort::topologicalSort(ListToMatrixGraph(graph2)->adjMatrix, order);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << endl << "BFS for node at index 1: ";
	Traversal::BFS(graph2, order, 1);

	std::this_thread::sleep_for(std::chrono::seconds(4));
	cout << endl << "\nGRAPH 3  \n" << endl;

	order = 9;
	int **weighted_matrix  = new int*[order]{ 
						new int[9]{ 0, 4, 0, 0, 0, 0, 0, 7, 0 },
						new int[9]{ 4, 0, 8, 0, 0, 0, 0, 3, 0 },
						new int[9]{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						new int[9]{ 0, 0, 7, 0, 8, 9, 0, 0, 0 },
						new int[9]{ 0, 0, 0, 8, 0, 6, 0, 0, 0 },
						new int[9]{ 0, 0, 4, 9, 6, 0, 2, 0, 0 },
						new int[9]{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						new int[9]{ 8, 9, 0, 0, 0, 0, 1, 0, 7 },
						new int[9]{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
	AdjMatrixGraph* graph3 = new AdjMatrixGraph(order, weighted_matrix);
	graph3->print();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << endl << "DFS for node at index 3: " << endl;
	Traversal::DFS(weighted_matrix, order, 3);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << endl<< "\nDijkstra for node at index 6: " << endl;
	Traversal::dijkstra(weighted_matrix, order, 6);
	MinSpanningTree* MST = new MinSpanningTree(weighted_matrix, order);
	
	std::this_thread::sleep_for(std::chrono::seconds(4));

	cout << "\n\nMST cost: " << MST->getMSTweight()<<endl;
	int** mst = MST->getMST();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << "MST : ";
	for (int i = 0; i < order-1; i++) {
		cout << " [" << mst[i][0] << "; " << mst[i][1] << "] ";
	}
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main(){
	//adjMatrixGraph_DEMO_Block1_2();
	//adjListGraph_DEMO_Block1_2();
	adjMatrixGraph_DEMO_Block3_6();
	return 0;
}
