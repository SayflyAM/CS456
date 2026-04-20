BFS its uses a queuea FIFO
Iterative DFS uses a stack LIFO

so the DFS 
its recurisve DFS uses the program's call stack automatically, but for Iterativ DFS means you create that stack yourself.



What DFS is doing 

DFS means start form one node, go as deep as possible, then backtrack.

Recurisve DFS

when I have call 
dfsHelper(1) then inside it calls: dfsHelper(2) and so on.

remembering where to go back this is handled by the call stack.


so for Iterative DFS we use stack insted of recursion.



so the idea:
1. push the start node into the stack 
2. while the stack is not empty
we need to take the top node. then
process it.
then push it to unviisited nighbors.
