/*
	Written By: Joel Smith
	
	Purpose: Contains the main function and controls which simulations run 
		as well as displaying the run results
*/

#include <iostream>
#include <thread>
#include "SimpleSimulation.h"
using namespace std;

int main()
{
	//Graph used throughout the program
	int initialGraph[Verticies][Verticies]
	{ { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 4, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	{ 0, 0, 4, 0, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	//Queue lengths for each of the node's links within the network
	int NodeQueues[Verticies]{ 1000, 100, 50, 70, 45, 80, 1000,100,1000};
	
	//Treansmission rate from the given nodes
	int transmissionRate[Verticies]{ 10,8,12,9,7,10,6,7 ,13};
	bool isStatic = true;

	//Tracking the packet loos for both the static and semi static runs
	int staticPacketLoss;
	int SemiStaticPacketLoss;

	//Static sim object creation with message size of 1000 and source 0, destion 6
	simulation sim = simulation(initialGraph, NodeQueues, transmissionRate, 1000, 0, 6, true);
	
	//strat time to determine run time of current simulation
	int startTime = clock();
	sim.run();
	int staticTime = clock() - startTime;
	staticPacketLoss = sim.DroppedPacket;

	//Semi-static sim object creation with message size of 1000 and source 0, destion 6
	sim = simulation(initialGraph, NodeQueues, transmissionRate, 1000, 0, 6, false);
	startTime = clock();
	sim.run();
	
	//CURRENTLY NOT FUNCTIONING
	//Attempt to multithread the simulation run function
	/*if (sim.isUpdated) {
		cout << "Starting Multithreaded processing... " << endl;
		thread original(run, sim, sim.DR);
		thread diverted(run, sim, (sim.DRUpdated));

		original.join();
		diverted.join();
	}*/

	int SemiStaticTime = clock() - startTime;
	SemiStaticPacketLoss = sim.DroppedPacket;

	//displaying the packet loss and run times for both the static and semi static runs
	cout << " Static Packet Loss: " << staticPacketLoss << "\tSemi-Static Packet Loss: " << SemiStaticPacketLoss << endl;
	cout << " Static Completion Time: " << staticTime << "\tSemi-Static Completion Time: " << SemiStaticTime << endl;

	return 0;
}
