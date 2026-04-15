#pragma once
#include <vector>
#include <cstdint> // For unit8_t
#include <iostream>
using namespace std;

enum class Direction
{

    Up,
    Down,
    Left,
    none,// تم اضافتها لتمثل الحالة الأولية (عقدة الجذر ) حيث لا توجد حركة 
    Right
};

struct Position
{
    int row;
    int col;
};

struct State
{
    Position agent_pos;
    int fuel;
    // We have Using bool for every coins C1-C4 but it not good  for memory, that way we have used a bitmask for coins to save memory.
    uint8_t collected_coins;
};

struct SearchResult
{

    bool found_solution;
    vector<Direction> path;
    int nodes_expanded;
    double execution_time_ms;
};

// Here we declare a function that takes a State, we have used it as Const not  just State so we do not copy of state just use what we have only.

bool isGoal(const State &current_state, const State &goal_state);

vector<State> getSuccessors(const State &current_state);
