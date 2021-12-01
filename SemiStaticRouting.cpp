#include <iostream>
#include <limits.h>
#include <list>
#include "SemiStaticRouting.h"
using namespace std;



DijkstraRouting UpdateGraph(DijkstraRouting DRObject, int src, int dest, int Queues[Verticies], int CurrentGraph[Verticies][Verticies]) {
	int tempGraph[Verticies][Verticies];
	for (int i = 0; i < Verticies; i++) {
		for (int j = 0; j < Verticies; j++) {
			if (CurrentGraph[i][j] != 0) {
				if (searchPath(DRObject.Path[dest], j)) {
					tempGraph[i][j] = Queues[i] + CurrentGraph[i][j];
				}
				else {
					tempGraph[i][j] = CurrentGraph[i][j];
				}
			}
			else {
				tempGraph[i][j] = 0;
				continue;
			}
		}
	}
	DRObject.setGraph(tempGraph);
	DRObject.printGraph();
	DRObject.Dijkstra(src,dest);

	return DRObject;
}

bool searchPath(list<int> path, int value) {
	for (auto it = path.begin(); it != path.end(); it++) {
		if (*it == value) {
			return true;
		}
	}
	return false;
}