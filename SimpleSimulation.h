#pragma once
#include "SemiStaticRouting.h"
using namespace std;

//simulation class that outlines the simulation objects which provides the running of the static and semi-static algorithms
class simulation {
public:
	//graph in the running simulation
	int SimGraph[Verticies][Verticies];
	
	//initial graph for the running simulation
	int InitialGraph[Verticies][Verticies];
	
	//Queue lengths of the initial graph
	int Queuelengths[Verticies];

	//Transmission values for all nodes in the graph
	int TransmissionVals[Verticies];
	
	//Allocated Queues for the given nodes in the initial graph
	list <bool> Queues[Verticies];

	//Dijkstra routing objects to maintain access to the paths for the current (source, destination) pair
	DijkstraRouting DR;
	DijkstraRouting DRUpdated;

	//storage if the current simulation is static or not
	bool isStatic;
	
	//storage if the current simulation has updated during the run
	bool isUpdated;
	
	//storage if the simulation has completed or not
	bool isCompleted;
	bool isRunning;
	
	//value of the source node
	int source;
	
	//value of the destination node
	int destination;
	
	//value of the number of dropped packets during the simulation's run
	int DroppedPacket;
	
	//message size for the current simulation run
	int MessageSize;
	
public:
	
	//Default constructor
	simulation() {
		this->source = 0;
		this->destination = Verticies-1;
		this->isStatic = false;
		
	}
	
	//overloaded constructor
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
	
	//All of the following functions are defined in the SimpleSimulation.cpp file
	DijkstraRouting UpdatePath();
	void run();
	void PassValue(int curr, int next, int transmission);
};

//overloaded version of the simulation class's run function
void run(simulation sim, DijkstraRouting ChangedDR);
