#include <iostream>
#include <list>
#include <queue>
#include <stack>
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

    void ids(int source)
    {
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(source);
        visited[source] = true;

        while(!st.empty()){
            int node = st.top();
            cout << node << endl;
            st.pop();
            for(auto nbr : lst[node]){
                if(!visited[nbr]){
                    visited[nbr] = true;
                    st.push(nbr);
                }
            }
        }
        
    }
};

int main()
{
    Graph g(7);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(5, 6);
    g.ids(1);
    return 0;
}