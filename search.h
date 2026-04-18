#pragma once
#include "grid_problem.h"
#include <fstream>
void BFS(const State &start, const State &goal, ofstream &out);
void DFS(const State &start, const State &goal, ofstream &out);
void IDS(const State &start, const State &goal, ofstream &out);