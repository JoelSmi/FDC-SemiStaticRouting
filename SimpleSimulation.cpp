#include <iostream>
#include <thread>
#include "SimpleSimulation.h"
using namespace std;

DijkstraRouting simulation::UpdatePath() {
	int CurrentQueues[Verticies];
	for (int i = 0; i < Verticies; i++) {
		CurrentQueues[i] = this->Queues[i].size();
	}
	return UpdateGraph(this->DR, this->source, this->destination, CurrentQueues, this->InitialGraph);
}

void simulation::PassValue(int curr, int next, int transmission) {
	for (int i = 0; i < transmission; i++) {
		if (this->Queues[curr].size() == 0) {
			if (curr == *this->DR.Path[this->destination].begin()) {
				this->DR.Path[this->destination].pop_front();
			}
			return;
		}
		this->Queues[curr].pop_front();
		if (this->Queues[next].size() + 1 < this->Queuelengths[next]) {
			this->Queues[next].push_back(true);
		}
		else {
			this->DroppedPacket++;
			if (!isStatic && i == transmission - 1) {
				this->isUpdated = true;
				this->DRUpdated = UpdatePath();
				this->DR.Path[this->destination].pop_front();
				return;
			}
		}
	}
}

void simulation::run() {
	this->DR.Dijkstra(this->source, this->destination);
	bool isEmpty = false;
	list<int> ChosenPath = this->DR.Path[this->destination];
	int Failsafe = 0;

	this->Queuelengths[this->source] = this->MessageSize;
	this->Queues[this->source].clear();
	for (int i = 0; i < MessageSize; i++) {
		this->Queues[this->source].push_back(true);
	}

	int tempNode = -1;
	do {
		for (auto it = ChosenPath.begin(); it != ChosenPath.end(); it++) {
			if (this->Queues[*it].empty()) {
				isEmpty = true;
			}
			else {
				isEmpty = false;
				break;
			}
		}
		int temp = this->source;
		for (auto it = ChosenPath.begin(); it != ChosenPath.end(); it++) {
			if (*it == *ChosenPath.begin()) {
				temp = *it;
				continue;
			}
			else {
				if (this->Queues[*ChosenPath.begin()].empty() && this->Queues[*ChosenPath.end()].empty()) {
					isEmpty = true;
					break;
				}
				
				PassValue(temp, *it, this->TransmissionVals[temp]);
				if (temp == this->source) {
					this->MessageSize = this->Queues[temp].size();
				}
				printf("Current Node %i: %i, Tranmission Rate : %i, Next Node %i: %i             \n", temp, this->Queues[temp].size(), this->TransmissionVals[temp], *it, this->Queues[*it].size());
				if (this->isUpdated) {
					this->isUpdated = false;
					ChosenPath.pop_front();
				}
				if (temp == *ChosenPath.begin() && this->Queues[temp].size() == 0) {
					this->Queues[temp].clear();
					ChosenPath.pop_front();
					if (*ChosenPath.begin() == this->destination) {
						isEmpty = true;
						this->isCompleted = true;
					}
				}
				temp = *it;
			}
		}
		Failsafe++;
		cout << endl;
	} while (!isEmpty && Failsafe < 1000);

	if (this->DRUpdated.getIsUsed() == false) {
		return;
	}
	else {
		this->DR = this->DRUpdated;
		cout << this->MessageSize << endl;
		this->DRUpdated = DijkstraRouting();
		run();
	}
}


/*void run(simulation sim, DijkstraRouting ChangedDR) {
	sim.DR = ChangedDR;
	sim.DR.Dijkstra(sim.source, sim.destination);
	sim.isUpdated = false;
	bool isEmpty = false;
	list<int> ChosenPath = sim.DR.Path[sim.destination];
	int Failsafe = 0;

	if (sim.DR.Path[sim.destination] ==  ChangedDR.Path[sim.destination]) {
		sim.DR.Path[sim.destination].pop_front();
		ChosenPath.pop_front();
	}

	sim.Queuelengths[sim.source] = sim.MessageSize;
	sim.Queues[sim.source].clear();
	for (int i = 0; i < sim.MessageSize; i++) {
		sim.Queues[sim.source].push_back(true);
	}

	int tempNode = -1;
	do {
		for (auto it = ChosenPath.begin(); it != ChosenPath.end(); it++) {
			if (sim.Queues[*it].empty()) {
				isEmpty = true;
			}
			else {
				isEmpty = false;
				break;
			}
		}
		int temp = sim.source;
		for (auto it = ChosenPath.begin(); it != ChosenPath.end(); it++) {
			if (*it == *ChosenPath.begin()) {
				temp = *it;
				continue;
			}
			else {
				if (sim.Queues[*ChosenPath.begin()].empty() && sim.Queues[*ChosenPath.end()].empty()) {
					isEmpty = true;
					break;
				}

				sim.PassValue(temp, *it, sim.TransmissionVals[temp]);
				if (temp == sim.source) {
					sim.MessageSize = sim.Queues[temp].size();
				}
				printf("Current Node %i: %i, Tranmission Rate : %i, Next Node %i: %i             \n", temp, sim.Queues[temp].size(), sim.TransmissionVals[temp], *it, sim.Queues[*it].size());
				if (sim.isUpdated) {
					sim.isUpdated = false;
					ChosenPath.pop_front();
					//Forking the process to complete the original path and the newly gnerated path
				}
				if (temp == *ChosenPath.begin() && sim.Queues[temp].size() == 0) {
					sim.Queues[temp].clear();
					ChosenPath.pop_front();
					if (*ChosenPath.begin() == sim.destination) {
						ChosenPath.clear();
						isEmpty = true;
						sim.isCompleted = true;
					}
				}
				temp = *it;
			}
		}
		Failsafe++;
		cout << endl;
	} while (!isEmpty && Failsafe < 1000);
	
	if (sim.DRUpdated.getIsUsed() == false) {
		return;
	}
	else {
		sim.DR = sim.DRUpdated;
		cout << sim.MessageSize << endl;
		sim.DRUpdated = DijkstraRouting();
		sim.run();
	}
}*/