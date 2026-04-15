#include "search.h"
#include <iostream>

using namespace std;

int main() {

    State goal;
    
    goal.agent_pos = {1,1};// الهدف هو الوصول إلى (1,1)
    goal.c1 = true;
    goal.c2 = true;
    goal.c3 = true;
    goal.c4 = true;


   // goal.collected_coins = 15; // 1111 in binary, meaning all coins collected
   // tests[i] = {{x,y}, fuel, false, false, false, false};
    State tests[10];// مجموعة من الحالات الابتدائية للtests 


     //Represent the tests in an array of type State, each test containing a different location for the (x,y) agent, a different amount of fuel, and coins with a value of 0.
     // { {tests[i].agent_pos.row, tests[i].agent_pos.col}, tests[i].fuel, tests[i].collected_coins }
    /*tests[0] = {{9,9}, 10, 0};
    tests[1] = {{5,5}, 8, 0};
    tests[2] = {{3,7}, 12, 0};
    tests[3] = {{4,6}, 15, 0};
    tests[4] = {{2,2}, 5, 0};
    tests[5] = {{1,2}, 5, 0};     
    tests[6] = {{10,10}, 3, 0};  
    tests[7] = {{4,8}, 1, 0};    
    tests[8] = {{7,7}, 20, 0};   
    tests[9] = {{9,2}, 2, 0}; 
  */


   tests[0] = {{5,7}, 20, false, false, false, false};
   tests[1] = {{5,5}, 8, false, false, false, false};
   tests[2] = {{3,7}, 12, false, false, false, false};
   tests[3] = {{4,6}, 15, false, false, false, false};
   tests[4] = {{2,2}, 5, false, false, false, false};
   tests[5] = {{1,2}, 5, false, false, false, false};
   tests[6] = {{10,10}, 3, false, false, false, false};
   tests[7] = {{4,8}, 1, false, false, false, false};
   tests[8] = {{7,7}, 20, false, false, false, false};
   tests[9] = {{9,2}, 2, false, false, false, false};
    //display the tests
    for(int i = 0; i < 10; i++) {

        cout << "\n****** test " << i+1 << " ********\n";
        cout << "Start State: ("<< tests[i].agent_pos.row << ","
         << tests[i].agent_pos.col<< ", fuel:" << tests[i].fuel << ")\n";
        // BFS(tests[i], goal);cout<<endl<<endl;
         DFS(tests[i], goal);cout<<endl<<endl;
        
    }

    return 0;
}