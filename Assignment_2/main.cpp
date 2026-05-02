#include "search.h"
#include <iostream>
#include <fstream>// used for output file
#include <cstdlib>// used for random number generation
#include <ctime>// used for random number generation
using namespace std;

int main()
 {
     ofstream out("output.txt");
     State goal;
     
    goal.agent_pos = {1,1};// الهدف هو الوصول إلى (1,1)
    goal.c1 = true;
    goal.c2 = true;
    goal.c3 = true;
    goal.c4 = true;

    
   srand(time(0)); // used to seed the random number generator with the current time, ensuring different random values each time the program is run
     
   // walls fixed positions
      block[0] = {3,3};
      block[1] = {5,5};
      block[2] = {7,2};
    // coins random
    for(int i = 0; i < 4; i++)
     {
    coins[i].row = rand() % 10 + 1;
    coins[i].col = rand() % 10 + 1; }

    // fuel place random
    fuel_place.row = rand() % 10 + 1;
    fuel_place.col = rand() % 10 + 1;

   //Represent the tests in an array of type State, each test containing a different location for the (x,y) agent, a different amount of fuel, and coins with a value of 0.
   // { {tests[i].agent_pos.row, tests[i].agent_pos.col}, tests[i].fuel, false, false, false, false }
    

   State tests[5];// مجموعة من الحالات الابتدائية للtests 
   for(int i = 0; i < 5; i++)
    {
    tests[i].agent_pos.row = rand() % 10 + 1; // من 1 إلى 10
    tests[i].agent_pos.col = rand() % 10 + 1;
    tests[i].fuel = rand() % 20 + 1; // من 1 إلى 20

    tests[i].c1 = false;
    tests[i].c2 = false;
    tests[i].c3 = false;
    tests[i].c4 = false;

    }
 
 /*  // walls fixed positions
block[0] = {3,3};
block[1] = {5,5};
block[2] = {7,2};


// coins fixed positions
coins[0] = {2,2};
coins[1] = {9,9};
coins[2] = {3,2};
coins[3] = {7,1};


// fuel station fixed position
fuel_place = {4,4};


// tests fixed states
State tests[5];

tests[0].agent_pos = {1,1};
tests[0].fuel = 20;

tests[1].agent_pos = {2,5};
tests[1].fuel = 15;

tests[2].agent_pos = {8,1};
tests[2].fuel = 18;

tests[3].agent_pos = {6,6};
tests[3].fuel = 12;

tests[4].agent_pos = {10,10};
tests[4].fuel = 20;


// all coins البداية غير مجمعة
for(int i = 0; i < 5; i++)
{
    tests[i].c1 = false;
    tests[i].c2 = false;
    tests[i].c3 = false;
    tests[i].c4 = false;
}
*/
out << "*************** GBFS ***************\n";

   for(int i = 0; i < 5; i++)
    {
        out << "Test " << i+1 << ": Start State: ("<< tests[i].agent_pos.row << ", " << tests[i].agent_pos.col << "), Fuel: " << tests[i].fuel << "\n";
        GBFS(tests[i], goal, out);
    }
    out.close();
    return 0;
  
}