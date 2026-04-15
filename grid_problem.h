#pragma once
#include <vector>// لتخزين الحالات التالية والحالات التي تم زيارتها
#include <cstdint> // For unit8_t // لتخزين حالة جمع العملات باستخدام bitmask
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
    //uint8_t collected_coins;
    bool c1, c2, c3, c4;// تم استخدام 4 متغيرات بوليانية لتمثيل جمع كل عملة بشكل منفصل بدلاً من استخدام
};
struct Node {
    State state;// الحالة الحالية
    Node* parent;//بوينتر إلى الأب في شجرة البحث
    Direction action; // الحركة التي أدت إلى هذه الحالة
    int frontier_size;//
   
    // Constructor
    Node(State s, Node* p, Direction a, int f ) 
    {
        state = s;
        parent = p;
        action = a;
        frontier_size = f;
    }
};
/*struct SearchResult
{

    bool found_solution;
    vector<Direction> path;
    int nodes_expanded;
    double execution_time_ms;
};
*/
// Here we declare a function that takes a State, we have used it as Const not  just State so we do not copy of state just use what we have only.

bool isGoal(const State &current_state, const State &goal_state);

vector<State> getSuccessors(const State &current_state);
