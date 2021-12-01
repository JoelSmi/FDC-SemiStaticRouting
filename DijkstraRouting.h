#pragma once
#include <list>
#define Verticies 9 
using namespace std;

class DijkstraRouting {

private:
	int ConnectedGraph[Verticies][Verticies];
	int gblDistances[Verticies];

	bool isUsed;

public:
	list <int> Path[Verticies];

	DijkstraRouting() {
		for (int i = 0; i < Verticies; i++) {
			for (int j = 0; j < Verticies; j++) {
				this->ConnectedGraph[i][j] = 0;
			}
		}

		isUsed = false;
	}
	DijkstraRouting(int Graph[Verticies][Verticies]) {
		for (int i = 0; i < Verticies; i++) {
			for (int j = 0; j < Verticies; j++) {
				this->ConnectedGraph[i][j] = Graph[i][j];
			}
		}
		isUsed = true;
	}

	bool getIsUsed() {
		return this->isUsed;
	}

	void PrintSolution();
	void Dijkstra(int src);
	void Dijkstra(int src, int dest);
	void setGraph(int Graph[Verticies][Verticies]);
	void printGraph();
};

int MinDistance(int distance[Verticies], bool sptSet[Verticies]);
