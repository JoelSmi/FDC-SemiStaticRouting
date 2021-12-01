/*
	Written By: Joel Smith
	
	Purpose: Controll structure that changes the static Dijkstra algorithm to a Semi-static/ adaptive 
		algorithm that adjust when the conditions are met (in this case when a queue overflows within the network)
*/

#include <iostream>
#include <limits.h>
#include <list>
#include "SemiStaticRouting.h"
using namespace std;

//Function to update the graph in the givin Dijkstra routing object based on the source, destination, queues, and the current(initial graph)
DijkstraRouting UpdateGraph(DijkstraRouting DRObject, int src, int dest, int Queues[Verticies], int CurrentGraph[Verticies][Verticies]) {
	int tempGraph[Verticies][Verticies];
	for (int i = 0; i < Verticies; i++) {
		for (int j = 0; j < Verticies; j++) {
			if (CurrentGraph[i][j] != 0) {
				if (searchPath(DRObject.Path[dest], j)) {
					//Only updates the the graph if the current path contains the j value
					tempGraph[i][j] = Queues[i] + CurrentGraph[i][j];
				}
				else {
					//copies the value from the currentGraph array to the tempGraph array
					tempGraph[i][j] = CurrentGraph[i][j];
				}
			}
			else {
				//Assigning zero to all undifined/0 values in the current graph array
				tempGraph[i][j] = 0;
				continue;
			}
		}
	}
	
	//calling of the setGraph function in the DRObject found in DijkstraRouting.cpp
	DRObject.setGraph(tempGraph);
	
	//calling of the overloaded Dijkstra function in the DRObject found in DijkstraRouting.cpp
	DRObject.Dijkstra(src,dest);

	return DRObject;
}

//Searches the given path fro a specific value and returns the boolean value of the path search
bool searchPath(list<int> path, int value) {
	for (auto it = path.begin(); it != path.end(); it++) {
		if (*it == value) {
			return true;
		}
	}
	return false;
}
