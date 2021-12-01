/*
	Written By: Joel Smith
	Based on code found here: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

	Purpose: The following code provides the routing functions 
	      to determine the shortest path from a source to a destination.

*/

#include <iostream>
#include <limits.h>
#include "DijkstraRouting.h"
using namespace std;

//setGraph function to replace the object's currentGraph with the given graph 2d array 
void DijkstraRouting::setGraph(int Graph[Verticies][Verticies]) {
	for (int i = 0; i < Verticies; i++) {
		for (int j = 0; j < Verticies; j++) {
			this->ConnectedGraph[i][j] = Graph[i][j];
		}
	}

	this->Path->clear();
}

//MinDistance function determines the node with the smallest distance from the source based upon the given sptSet.
static int MinDistance(int distance[Verticies], bool sptSet[Verticies]) {

	int TempMin = INT_MAX, MinDistance_idx;

	for (int i = 0; i < Verticies; i++) {
		if (sptSet[i] == false && distance[i] <= TempMin) {
			TempMin = distance[i], MinDistance_idx = i;
		}
	}
	
	return MinDistance_idx;
}

//printGraph function displays the objects currentGraph 2d Array
void DijkstraRouting::printGraph() {
	for (int i = 0; i < Verticies; i ++) {
		for (int j = 0; j < Verticies; j++) {
			cout << this->ConnectedGraph[i][j] << "\t";
		}
		cout << endl;
	}
}

//PrintSolution function displays all the nodes and their distances from the source
void DijkstraRouting::PrintSolution() {
	cout << "Vertex \t Distance from source" << endl;
	for (int i = 0; i < Verticies; i++) {
		if (this->gblDistances[i] >= 0) {
			cout << i << " \t\t" << this->gblDistances[i] << endl;
		}
	}
}

//Dijkstra function binder function reponsible for determining the unprocessed nodes and passing the unprocessed nodes to the MinDistance function
void DijkstraRouting::Dijkstra(int src)
{
	int distance[Verticies];
	bool sptSet[Verticies];
	
	//Assigning the distance and sptSet arrays
	for (int i = 0; i < Verticies; i++) {
		distance[i] = INT_MAX;
		sptSet[i] = false;
	}
	
	//Ensuring that the source node it added to its own path for accurate path allocation
	if (this->Path[src].empty()) {
		distance[src] = 0;
		this->Path[src].push_back(src);
	}

	//Controlling loop handling the Mindistance function and the Path Assignments
	for (int i = 0; i < Verticies; i++) {
		int Unprocessed = MinDistance(distance, sptSet);
		sptSet[Unprocessed] = true;
		for (int j = 0; j < Verticies; j++) {
			
			//4 conditions of the if statement
			//1) checking that the node j has not been assigned proviously
			//2) Checking to ensure that the link in position (Unprocessed, j) exists
			//3) Ensures that the distance is less than the maximum int allowed
			//4) Ensures that the value about to be added to the path/distance array is less than the value in the j position of the distanc earray
			if (!sptSet[j] && this->ConnectedGraph[Unprocessed][j] && distance[Unprocessed] != INT_MAX && distance[Unprocessed] + ConnectedGraph[Unprocessed][j] < distance[j]) {
				distance[j] = distance[Unprocessed] + this->ConnectedGraph[Unprocessed][j];
				
				//j-value is the node to be assigned while Unprocessed-value is the path on which j is assigned 
				this->Path[j] = this->Path[Unprocessed];
				this->Path[j].push_back(j);
				this->Path[j].unique();

				cout << "Node " << j << " has been added to path " << Unprocessed << endl;
			}
		}
	}
	
	//Assigning the local distance array to the gblDistance array
	for (int i = 0; i < Verticies; i++) {
		this->gblDistances[i] = distance[i];
	}
}

//Overloaded version of the Djkstra function which recieves the destion value and calls the original Dijkstra function
void DijkstraRouting::Dijkstra(int src, int dest)
{
	for (int i = 0; i < Verticies; i++) {
		this->Path[i].clear();
	}
	
	cout << "Soruce: " << src << ";  Destination: " << dest << endl;
	Dijkstra(src);

	//displaying the Path order to ensure proper flow through the network linnks
	cout << "Path order";
	for (auto it = this->Path[dest].begin(); it != this->Path[dest].end(); it++) {
		cout << "  " << *it;
	}
	cout << endl;

}
