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

void DijkstraRouting::setGraph(int Graph[Verticies][Verticies]) {
	for (int i = 0; i < Verticies; i++) {
		for (int j = 0; j < Verticies; j++) {
			this->ConnectedGraph[i][j] = Graph[i][j];
		}
	}

	this->Path->clear();
}


static int MinDistance(int distance[Verticies], bool sptSet[Verticies]) {

	int TempMin = INT_MAX, MinDistance_idx;

	for (int i = 0; i < Verticies; i++) {
		if (sptSet[i] == false && distance[i] <= TempMin) {
			TempMin = distance[i], MinDistance_idx = i;
		}
	}
	
	return MinDistance_idx;
}

void DijkstraRouting::printGraph() {
	for (int i = 0; i < Verticies; i ++) {
		for (int j = 0; j < Verticies; j++) {
			cout << this->ConnectedGraph[i][j] << "\t";
		}
		cout << endl;
	}
}

void DijkstraRouting::PrintSolution() {
	cout << "Vertex \t Distance from source" << endl;
	for (int i = 0; i < Verticies; i++) {
		if (this->gblDistances[i] >= 0) {
			cout << i << " \t\t" << this->gblDistances[i] << endl;
		}
	}
}

void DijkstraRouting::Dijkstra(int src)
{
	int distance[Verticies];
	bool sptSet[Verticies];

	for (int i = 0; i < Verticies; i++) {
		distance[i] = INT_MAX;
		sptSet[i] = false;
	}

	if (this->Path[src].empty()) {
		distance[src] = 0;
		this->Path[src].push_back(src);
	}

	for (int i = 0; i < Verticies; i++) {
		int Unprocessed = MinDistance(distance, sptSet);
		sptSet[Unprocessed] = true;
		for (int j = 0; j < Verticies; j++) {
			if (!sptSet[j] && this->ConnectedGraph[Unprocessed][j] && distance[Unprocessed] != INT_MAX && distance[Unprocessed] + ConnectedGraph[Unprocessed][j] < distance[j]) {
				distance[j] = distance[Unprocessed] + this->ConnectedGraph[Unprocessed][j];

				this->Path[j] = this->Path[Unprocessed];
				this->Path[j].push_back(j);
				this->Path[j].unique();

				cout << "Node " << j << " has been added to path " << Unprocessed << endl;
			}
		}
	}

	for (int i = 0; i < Verticies; i++) {
		this->gblDistances[i] = distance[i];
	}
}

void DijkstraRouting::Dijkstra(int src, int dest)
{
	for (int i = 0; i < Verticies; i++) {
		this->Path[i].clear();
	}

	cout << "Soruce: " << src << ";  Destination: " << dest << endl;
	Dijkstra(src);

	cout << "Path order";
	for (auto it = this->Path[dest].begin(); it != this->Path[dest].end(); it++) {
		cout << "  " << *it;
	}
	cout << endl;

}