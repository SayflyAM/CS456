#include <iostream>
#include <list>
using namespace std;

class Graph
{
    list<int> *lst;
    int V;

public:
    Graph(int v)
    {
        V = v;
        lst = new list<int>[V];
    }

    void addEdge(int i, int j, bool undir = true)
    {
        if (i < 0 || j < 0 || i >= V || j >= V)
        {
            cerr << "Invalid edge: " << i << " - " << j << endl;
            return;
        }
        lst[i].push_back(j);
        if (undir)
        {
            lst[j].push_back(i);
        }
    }
    void printAdjList()
    {
        // Iterate over  all the rows
        for (int i = 0; i < V; i++)
        {
            cout << i << "-->";
            // every element of the linked list.
            for (auto node : lst[i])
            {
                cout << node << ",";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    // g.addEdge(1, 1);
    // g.addEdge(2, 4);
    // g.addEdge(2, 5);
    // g.addEdge(5, 3);
    // g.addEdge(6, 1);
    // g.addEdge(7, 2);

    g.printAdjList();

    return 0;
}
