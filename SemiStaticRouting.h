#pragma once
#include "DijkstraRouting.h" 

DijkstraRouting UpdateGraph(DijkstraRouting DRObject, int src, int dest, int QueueLengths[Verticies], int CurrentGraph[Verticies][Verticies]);
bool searchPath(list<int> path, int value);