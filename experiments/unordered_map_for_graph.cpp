#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

class Node
{
public:
    // We here creating list inside node object.
    string name;
    list<string> nbrs;

    Node(string name)
    {
        this->name = name;
    }
};

class Graph
{
    // The graph must contin all Node are there.
    // also we need to refer to each node by here name.
    // We use Hashmap (String, Node*), this Hashmap will store the relationships between key and name of the city for example if we have this ex like libya Tripoli and so on.

    unordered_map<string, Node *> m;

public:
    Graph(vector<string> cities)
    {
        for (auto city : cities)
        {
            m[city] = new Node(city);
        }
    }
    void addEdge(string x, string y, bool undir = false)
    {
        m[x]->nbrs.push_back(y);
        if (undir)
        {
            m[y]->nbrs.push_back(x);
        }
    }

    void printAdjList()
    {
        for (auto cityPair : m)
        {
            auto city = cityPair.first;
            Node *node = cityPair.second;
            cout << city << "==>";

            for(auto nbr : node->nbrs)
            {
                cout << nbr << ",";
            }
            cout << endl;
        }
    }
};

int main()
{

    vector<string> cities = {
        "Tripoli", "london", "Cairo"};
    Graph g(cities);
    g.addEdge("Tripoli", "london");
    g.addEdge("Cairo", "Tripoli");
    g.printAdjList();

    return 0;
}
