#pragma once
#include "SemiStaticRouting.h"
using namespace std;

class simulation {
public:
	int SimGraph[Verticies][Verticies];
	int InitialGraph[Verticies][Verticies];
	int Queuelengths[Verticies];
	int TransmissionVals[Verticies];
	list <bool> Queues[Verticies];

	DijkstraRouting DR;
	DijkstraRouting DRUpdated;

	bool isStatic;
	bool isUpdated;
	bool isCompleted;
	bool isRunning;
	int source;
	int destination;
	int DroppedPacket;
	int MessageSize;
	
public:
	
	simulation() {
		this->source = 0;
		this->destination = Verticies-1;
		this->isStatic = false;
		
	}
	simulation(int graph[Verticies][Verticies],int queues[Verticies], int Transmissions[Verticies], long Message, int src, int destination, bool isStatic) {
		this->source = src;
		this->destination = destination;
		this->isStatic = isStatic;
		this->isUpdated = false;
		this->isCompleted = false;
		this->MessageSize = Message;
		this->DroppedPacket = 0;

		for (int i = 0; i < Verticies; i++) {
			for (int j = 0; j < Verticies; j++) {
				this->SimGraph[i][j] = graph[i][j];
				this->InitialGraph[i][j] = graph[i][j];
			}
			this->Queuelengths[i] = queues[i];
			this->TransmissionVals[i] = Transmissions[i];
			this->DR = DijkstraRouting(this->SimGraph);
		}
	}

	DijkstraRouting UpdatePath();
	void run();
	void PassValue(int curr, int next, int transmission);
};

void run(simulation sim, DijkstraRouting ChangedDR);