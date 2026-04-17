#include "search.h"
#include <iostream>
#include <fstream>// used for output file
#include <cstdlib>// used for random number generation
#include <ctime>// used for random number generation
using namespace std;

int main()
 {
     ofstream out("output.txt");
     int num_algorithm;
     State goal;
     
    goal.agent_pos = {1,1};// الهدف هو الوصول إلى (1,1)
    goal.c1 = true;
    goal.c2 = true;
    goal.c3 = true;
    goal.c4 = true;

    srand(time(0)); // used to seed the random number generator with the current time, ensuring different random values each time the program is run
   
    // coins random
    for(int i = 0; i < 4; i++)
     {
    coins[i].row = rand() % 10 + 1;
    coins[i].col = rand() % 10 + 1;
    }

    // fuel place random
    fuel_place.row = rand() % 10 + 1;
    fuel_place.col = rand() % 10 + 1;

   // goal.collected_coins = 15; // 1111 in binary, meaning all coins collected
   // tests[i] = {{x,y}, fuel, false, false, false, false};
   //Represent the tests in an array of type State, each test containing a different location for the (x,y) agent, a different amount of fuel, and coins with a value of 0.
   // { {tests[i].agent_pos.row, tests[i].agent_pos.col}, tests[i].fuel, tests[i].collected_coins }
    

   State tests[10];// مجموعة من الحالات الابتدائية للtests 
   for(int i = 0; i < 10; i++)
    {

    tests[i].agent_pos.row = rand() % 10 + 1; // من 1 إلى 10
    tests[i].agent_pos.col = rand() % 10 + 1;

    tests[i].fuel = rand() % 20 + 1; // من 1 إلى 20

    tests[i].c1 = false;
    tests[i].c2 = false;
    tests[i].c3 = false;
    tests[i].c4 = false;
}


  out<<"**********************************************BFS************************************************\n";
    for(int i = 0; i < 10; i++)
     {  
        out << "\n****** test " << i+1 << " ********\n";
        out << "Start State: ("<< tests[i].agent_pos.row << ","<< tests[i].agent_pos.col << ", fuel:" << tests[i].fuel << ")\n";
        BFS(tests[i], goal, out); out << endl;
     }
 

  out<<"**********************************************DFS************************************************\n";
    for(int i = 0; i < 10; i++)
     {
        out << "\n****** test " << i+1 << " ********\n";
        out << "Start State: ("<< tests[i].agent_pos.row << ","<< tests[i].agent_pos.col<< ", fuel:" << tests[i].fuel << ")\n";
        DFS(tests[i], goal, out);out << endl;
     }
 

  out<<"**********************************************IDS************************************************\n";
    for(int i = 0; i < 10; i++) 
    {
        out << "\n****** test " << i+1 << " ********\n";
        out << "Start State: ("<< tests[i].agent_pos.row << ","<< tests[i].agent_pos.col << ", fuel:" << tests[i].fuel << ")\n";
        IDS(tests[i], goal, out); out  << endl;
    }

    out.close();
    return 0;
  
}