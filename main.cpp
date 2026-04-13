#include "search.h"
#include <iostream>

using namespace std;

int main() {


    State goal;
    goal.agent_pos = {1,1};

    //************note :  مزال م درتش جمع العملات **** 
   // goal.collected_coins = 0; 
    State tests[5];

    tests[0] = {{9,9}, 10, 0};
    tests[1] = {{5,5}, 8, 0};
    tests[2] = {{3,7}, 12, 0};
    tests[3] = {{10,1}, 15, 0};
    tests[4] = {{2,2}, 5, 0};

   
    for(int i = 0; i < 5; i++) {

        cout << "\n****** test " << i+1 << " ********\n";
        cout << "Start State: ("
             << tests[i].agent_pos.row << ","
             << tests[i].agent_pos.col
             << ", fuel:" << tests[i].fuel << ")\n";

        SearchResult result = BFS(tests[i], goal);

        if(result.found_solution)
            cout << "goal Found\n";
        else
            cout << "no solution\n";

        cout << "number of nodes expanded: " << result.nodes_expanded << endl;
        cout << "time: " << result.execution_time_ms << " ms\n";
    }

    return 0;
}