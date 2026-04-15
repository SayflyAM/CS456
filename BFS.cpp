#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Graph
{
    int V;
    list<int> *lst;

public:
    Graph(int v)
    {
        V = v;
        lst = new list<int>[V];
    }
    void addEdge(int i, int j, bool undir = true)
    {
        lst[i].push_back(j);
        if (undir)
        {
            lst[j].push_back(i);
        }
    }
    // BFS it is takes start node,you need quee and you push the start node to queue and then push th  nibers of start node inside the queue

    void bfs(int source)
    {
        queue<int> q;
        bool *visited = new bool[V]{0};
        q.push(source);
        visited[source] = true;

        while (!q.empty())
        {
            // Do some work for every node inside the queue.

            int f = q.front();
            // Here first we see it then printed then pop it.
            cout << f << endl;
            q.pop();

            // Push the nbrs or child for that node or current node inside  queue if they not already visited.

            for (auto nbr : lst[f])
            {

                if (!visited[nbr])
                {
                    q.push(nbr);
                    visited[nbr] = true;
                }
            }
        }
    }
};

int main()
{
    Graph g(6);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(5, 6);
    g.bfs(1);
    return 0;
}