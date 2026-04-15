Pass by value:
This so bad because when we will use BFS and it expands 100,000 nodes, this will triggered 100,000 massive memory.
bool isGoal(State s ) {
    retrun s.fuel == 0;
}
To fix this we need to pass by Const Reference
what this mean?
pass the memory address, don't copy the data.

bool isGoal(const State& s) {
    rturen s.fuel ==0;
}

**********************explain code ************************
in main 
 The target state was determined, which is reaching the location (1,1) while collecting all the coins, then a set of different states was created, and after that, the algorithm function was called.


 in grid_problem.h 
It contains basic definitions such as the state representing the agent's location, fuel, and coins, in addition to defining possible movement directions using an enum, and defining basic functions such as isGoal to check for reaching the goal and getSuccessors to generate the next states.

in grid_problem.cpp
The getSuccessors function generates all possible states from the current state by trying the four moves, while checking the grid boundaries and fuel consumption, in addition to updating the coin state when they are collected, and refueling when reaching the gas station.

in search.h
The BFS function was defined in file , and the type void was used, and the second definition was commented out, as well as the struct in the Grid Problem file, because the results are printed directly inside the function.


in search.cpp
The BFS function explores states using a queue according to the FIFO principle, where the next states are generated using getSuccessors, with duplication prevented using visited, and upon reaching the goal, the path is extracted by tracing the parents (parent pointers), then the path and the remaining data are printed.