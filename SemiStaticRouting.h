#pragma once
#include "DijkstraRouting.h" 

//Implementations for the following functions in the SemiStatic.cpp file
//conrtoller function to update the current paths within the DijkstraRouting objects for ideal pathing based on current snapshot of the graphs and queues
DijkstraRouting UpdateGraph(DijkstraRouting DRObject, int src, int dest, int QueueLengths[Verticies], int CurrentGraph[Verticies][Verticies]);

//Searcing the current path for a specific value
bool searchPath(list<int> path, int value);
