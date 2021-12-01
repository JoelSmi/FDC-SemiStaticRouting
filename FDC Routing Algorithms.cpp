// FDC Routing Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "SimpleSimulation.h"
using namespace std;

int main()
{
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

	int NodeQueues[Verticies]{ 1000, 100, 50, 70, 45, 80, 1000,100,1000};
	
	int transmissionRate[Verticies]{ 10,8,12,9,7,10,6,7 ,13};
	bool isStatic = true;

	int staticPacketLoss;
	int SemiStaticPacketLoss;

	simulation sim = simulation(initialGraph, NodeQueues, transmissionRate, 1000, 0, 6, true);
	int startTime = clock();
	sim.run();
	int staticTime = clock() - startTime;
	staticPacketLoss = sim.DroppedPacket;

	sim = simulation(initialGraph, NodeQueues, transmissionRate, 1000, 0, 6, false);
	startTime = clock();
	//sim.run();
	sim.run();
	/*if (sim.isUpdated) {
		cout << "Starting Multithreaded processing... " << endl;
		thread original(run, sim, sim.DR);
		thread diverted(run, sim, (sim.DRUpdated));

		original.join();
		diverted.join();
	}*/

	int SemiStaticTime = clock() - startTime;
	SemiStaticPacketLoss = sim.DroppedPacket;

	cout << " Static Packet Loss: " << staticPacketLoss << "\tSemi-Static Packet Loss: " << SemiStaticPacketLoss << endl;
	cout << " Static Completion Time: " << staticTime << "\tSemi-Static Completion Time: " << SemiStaticTime << endl;

	return 0;
}
