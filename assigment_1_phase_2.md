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