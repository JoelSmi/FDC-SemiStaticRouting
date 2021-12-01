#pragma once
#include <list>

//global constant defining the max size for the verticies (i.e. the number of nodes within the graph)
#define Verticies 9 
using namespace std;

class DijkstraRouting {

private:
	//Graph being analyzed to find the shortest paths from source to all nodes in the graph
	int ConnectedGraph[Verticies][Verticies];
	
	//Distances for the given nodes form the source
	int gblDistances[Verticies];

	//Bool value to indicate if the Graph has been overwritten or not
	bool isUsed;

public:
	//Array of lists to hold the shortest path form source to a given node
	list <int> Path[Verticies];

	//Default constructor
	DijkstraRouting() {
		for (int i = 0; i < Verticies; i++) {
			for (int j = 0; j < Verticies; j++) {
				this->ConnectedGraph[i][j] = 0;
			}
		}

		isUsed = false;
	}
	
	//Overloaded constructor
	DijkstraRouting(int Graph[Verticies][Verticies]) {
		for (int i = 0; i < Verticies; i++) {
			for (int j = 0; j < Verticies; j++) {
				this->ConnectedGraph[i][j] = Graph[i][j];
			}
		}
		isUsed = true;
	}

	//Returning the private isUsed object variables
	bool getIsUsed() {
		return this->isUsed;
	}

	//view DijkstraRouting.cpp for full implementation of the following functions
	void PrintSolution();
	void Dijkstra(int src);
	void Dijkstra(int src, int dest);
	void setGraph(int Graph[Verticies][Verticies]);
	void printGraph();
};

//Implementation found in the DijkstraRouting.cpp file
int MinDistance(int distance[Verticies], bool sptSet[Verticies]);
