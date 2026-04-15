#include<iostream>
#include<list>
#include<queue>
using namespace std;

class Graph{
    int V;
    list<int> *lst;

public:
   Graph(int v){
    V = v;
    lst = new list<int>[V];
   }
   void addEdge(int i, int j, bool undir=true){
    lst[i].push_back(j);
    if(undir){
        lst[j].push_back(i);
    }
   }
   //BFS it is takes start node,

   void bfs(int source){
    

   }

};


int main(){
    Graph g(7);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(3,5);
    g.addEdge(5,6);
    g.addEdge(4,5);
    g.addEdge(0,4);
    g.addEdge(3,4);
    g.bfs(1);
    return 0;
}