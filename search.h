#pragma once
#include "grid_problem.h"
#include <fstream>
//SearchResult BFS(const State &start, const State &goal);
void BFS(const State &start, const State &goal, ofstream &out);
void DFS(const State &start, const State &goal, ofstream &out);
void IDS(const State &start, const State &goal, ofstream &out);