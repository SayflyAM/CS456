The assigment is about state-space search for a dynmaic environmnet.


so we need to understand this that goal test like 
x == 1 && y==1 && coinsMask == 15

because 15 = 1111 meaning all 4 coins are collected.


so we need to make one funtion for all movement for BFS, DFS, and IDS.

we need to use like this 
vector<state> getSuccessors(const state& s) const

so this function must 
try moving up, right, down, left.
not move out side the grid of the game.
stop move if there wall.
also stop moves when fuel == 0.
add 1 to fuel.
refill to 20 if the new cell is the fuel station.
collect the coin automatically if the new cll has a coin.


also we need to use full sate repeated state checking 
visited[x][y] this in not goot its wrong.

so we need to use as the assgiment said 
visited[x][y][fuel][coinsMask]
