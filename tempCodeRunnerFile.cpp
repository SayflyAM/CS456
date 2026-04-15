#include "search.h"
#include <iostream>

using namespace std;

int main() {
     int num_algorithm;
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
   


   // display
 cout << "1-BFS, 2-DFS, 3-IDS\n";
 cout << "Enter the number of the search algorithm you want to use: "; cin >> num_algorithm;

  if(num_algorithm == 1) 
  {
    for(int i = 0; i < 10; i++)
     {
        cout << "\n****** test " << i+1 << " ********\n";
        cout << "Start State: ("<< tests[i].agent_pos.row << ","<< tests[i].agent_pos.col << ", fuel:" << tests[i].fuel << ")\n";
        BFS(tests[i], goal); cout << endl;
     }
   }
 else if(num_algorithm == 2)
 {
    for(int i = 0; i < 10; i++) {
        cout << "\n****** test " << i+1 << " ********\n";
        cout << "Start State: ("<< tests[i].agent_pos.row << ","<< tests[i].agent_pos.col<< ", fuel:" << tests[i].fuel << ")\n";
        DFS(tests[i], goal);cout << endl;
    }
  }
 else if(num_algorithm == 3)
 {
    for(int i = 0; i < 10; i++) {
        cout << "\n****** test " << i+1 << " ********\n";
        cout << "Start State: ("<< tests[i].agent_pos.row << ","<< tests[i].agent_pos.col << ", fuel:" << tests[i].fuel << ")\n";
        IDS(tests[i], goal); cout  << endl;
    }
 }
  else {cout << "invalid choice!\n";}

    return 0;
}

******************************************قريد يروبلم اتشش *****************************
#pragma once
#include <vector>// لتخزين الحالات التالية والحالات التي تم زيارتها
#include <cstdint> // For unit8_t // لتخزين حالة جمع العملات باستخدام bitmask
#include <iostream>
using namespace std;

enum class Direction
{

    Up,
    Down,
    Left,
    none,// تم اضافتها لتمثل الحالة الأولية (عقدة الجذر ) حيث لا توجد حركة 
    Right
};

struct Position
{
    int row;
    int col;
};

struct State
{
    Position agent_pos;
    int fuel;
    // We have Using bool for every coins C1-C4 but it not good  for memory, that way we have used a bitmask for coins to save memory.
    //uint8_t collected_coins;
    bool c1, c2, c3, c4;// تم استخدام 4 متغيرات بوليانية لتمثيل جمع كل عملة بشكل منفصل بدلاً من استخدام
};
struct Node {
    State state;// الحالة الحالية
    Node* parent;//بوينتر إلى الأب في شجرة البحث
    Direction action; // الحركة التي أدت إلى هذه الحالة
    int frontier_size;
    int depth;// used for IDS
   
    // Constructor
    Node(State s, Node* p, Direction a, int f, int d ) 
    {
        state = s;
        parent = p;
        action = a;
        frontier_size = f;
        depth = d;
    }
};
/*struct SearchResult
{

    bool found_solution;
    vector<Direction> path;
    int nodes_expanded;
    double execution_time_ms;
};
*/
// Here we declare a function that takes a State, we have used it as Const not  just State so we do not copy of state just use what we have only.

bool isGoal(const State &current_state, const State &goal_state);

vector<State> getSuccessors(const State &current_state);

**************************************** قريد يروبلم  سيبيبي *****************************

#include "grid_problem.h"

//تحقق مما إذا كانت الحالة الحالية هي حالة الهدف أم لا
//goal state is defined as the agent being at position (1,1) and having collected all coins (C1 to C4  == 15 in binary)
bool isGoal(const State &current_state, const State &goal_state) {

    return current_state.agent_pos.row == goal_state.agent_pos.row &&
           current_state.agent_pos.col == goal_state.agent_pos.col &&
          // current_state.collected_coins == goal_state.collected_coins;
          current_state.c1 && current_state.c2 &&
          current_state.c3 && current_state.c4;
}

//الحصول على الحالات التالية الممكنة من الحالة الحالية بناءً على الحركات الأربعة (Up, Down, Left, Right)
vector<State> getSuccessors(const State &current_state)
 {  
    vector<State> next_States;// لتخزين الحالات التالية الممكنة
    Direction directions[4] = {
        Direction::Up,
        Direction::Down,
        Direction::Left,
        Direction::Right
    };

    for(int i = 0; i < 4; i++) {

        if(current_state.fuel <= 0) //
        continue; // إذا نفد الوقود، لا يمكننا التحرك

        State next = current_state; // نبدأ من الحالة الحالية ونقوم بتعديلها بناءً على الحركة

        if(directions[i] == Direction::Up) 
            next.agent_pos.row--;// الحركة للأعلى تقلل من رقم الصف

        else if(directions[i] == Direction::Down)
            next.agent_pos.row++;// الحركة للأسفل تزيد من رقم الصف

        else if(directions[i] == Direction::Left)
            next.agent_pos.col--;// الحركة لليسار تقلل من رقم العمود

        else if(directions[i] == Direction::Right)
            next.agent_pos.col++;// الحركة لليمين تزيد من رقم العمود


         //grid size is 10x10 
         // إذا كانت الحركة تؤدي إلى الخروج من الشبكة، نتجاهلها
        if(next.agent_pos.row < 1 || next.agent_pos.row > 10 ||
           next.agent_pos.col < 1 || next.agent_pos.col > 10)
            continue; 

        
        next.fuel--;// كل حركة تستهلك وقود بقيمة 1 
        
        // تعريف مواقع العملات (حاليا بعديت يتغيروا راندوم )
        Position coins[4] = {
        {2,3}, // C1 
        {6,2}, // C2 
        {5,7}, // C3
        {8,8}  // C4
     };

     // التحقق مما إذا كان الوكيل قد جمع عملة في الموقع الجديد، إذا كان كذلك، نحدث collected_coins باستخدام
     for(int c = 0; c < 4; c++) 
     {
       if(next.agent_pos.row == coins[c].row && next.agent_pos.col == coins[c].col) 
       {  if(next.agent_pos.row == 2 && next.agent_pos.col == 3)  next.c1 = true;
          if(next.agent_pos.row == 6 && next.agent_pos.col == 2)  next.c2 = true;
          if(next.agent_pos.row == 5 && next.agent_pos.col == 7)  next.c3 = true;
          if(next.agent_pos.row == 8 && next.agent_pos.col == 8)  next.c4 = true;
          // next.collected_coins |= (1 << c);
         }
     }

        // example)(x,y): محطة الوقود في (3,8)
        if(next.agent_pos.row == 3 && next.agent_pos.col == 8) {next.fuel = 20;}//يتم إعادة تعبئة الوقود إلى 20 عند الوصول إلى محطة الوقود في (3,8)

  next_States.push_back(next);// إضافة الحالة الجديدة إلى قائمة الحالات التالية
  }

 return next_States;
}
****************************************سيرش اتش *****************************

#pragma once
#include "grid_problem.h"
//SearchResult BFS(const State &start, const State &goal);
void BFS(const State &start, const State &goal);
void DFS(const State &start, const State &goal);
void IDS(const State &start, const State &goal);
****************************************سيرش اتش سيبيبي *****************************


#include "search.h"
#include "grid_problem.h"
#include <queue> //used for BFS
#include <vector>// used for visited and path
#include <chrono>// used for measuring execution time
#include <iostream>
#include <stack> // used for DFS

using namespace std;

//مقارنة بين حالتين لتجنب تكرار ال states في visited
bool comparison_state(const State &a, const State &b) {
    return a.agent_pos.row == b.agent_pos.row &&
           a.agent_pos.col == b.agent_pos.col &&
           a.fuel == b.fuel &&
           //a.collected_coins == b.collected_coins;
            a.c1 == b.c1 && a.c2 == b.c2 && a.c3 == b.c3 &&a.c4 == b.c4;
}

//display the coins 
/*void printCoins(uint8_t coins) 
{
   for(int i = 0; i < 4; i++) {
     if(coins & (1 << i))  cout << "t";
      else cout << "f";

    if(i < 3) cout << ",";// للفصل بين العملات في طباعة 
    }
}
*/ // لو استخدمت بوليان مش ح نختاجها 
//SearchResult BFS(const State &start, const State &goal);
 void BFS(const State &start, const State &goal) 
{
    
    int nodes = 0;
    Node* goalNode = NULL;

    auto startTime = chrono::high_resolution_clock::now();// بدء قياس الوقت

    queue<Node*> frontier; //لتخزين العقد التي سيتم استكشافها
    vector<State> visited; // لتخزين الحالات التي تم زيارتها

    Node* root = new Node(start, NULL, Direction::none, 0,0);//تم إنشاء عقدة الجذر باستخدام الحالة الابتدائية، لا يوجد أب لها ولا حركة وعدد فرونتير =0
    frontier.push(root);
    visited.push_back(start);//in the beginning we have only the start state in visited  
    

    while(!frontier.empty()) {

        Node* current = frontier.front(); //
        frontier.pop();
        nodes++;

        if(isGoal(current->state, goal))
         {
            goalNode = current;
            break;//تم العثور على الهدف، نخرج من  حلقة التكرار
        }

        //احضار الحالات التالية
        vector<State> nextStates = getSuccessors(current->state);//الحصول على الحالات التالية الممكنة من الحالة الحالية بناءً على الحركات الأربعة

        Direction actions[4] = {
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right
        };

        for(int i = 0; i < nextStates.size(); i++) // لكل حالة تالية
        {

            bool found = false;// للتحقق مما إذا كانت الحالة التالية قد تم زيارتها بالفعل

            //  البحث في visited
            for(int j = 0; j < visited.size(); j++)
             {
                if(comparison_state(nextStates[i], visited[j])) // إذا تم العثور على الحالة في visited، نعتبرها حالة مكررة
                {
                    found = true;// تم العثور على الحالة في visited، نعتبرها حالة مكررة
                    break;// نخرج من البحث في visited
                }
            }

            // إذا الحالة جديدة
            if(!found) 
            {
                Node* child = new Node(nextStates[i], current, actions[i], frontier.size(),0);// إنشاء عقدة جديدة للحالة التالية، مع الإشارة إلى الأب  والحركة التي أدت إليها وعدد الفرونتير الحالي 
                frontier.push(child);// إضافة العقدة الجديدة إلى الفرونتير 
                visited.push_back(nextStates[i]); // إضافة الحالة التالية إلى لمنع زيارتها مرة أخرى في المستقبل
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now(); // نهاية قياس الوقت
    double time = chrono::duration<double, milli>(endTime - startTime).count();// حساب الوقت المنقضي بالميلي ثانية

    //استخراج المسار من goalNode إلى root
    vector<Direction> path;// لتخزين حركات المسار من الهدف إلى الجذر

    if(goalNode != NULL)
     {
        Node* temp = goalNode;// بدء من عقدة الهدف

        while(temp->parent != NULL && temp->action == Direction::none) // طالما لم نصل إلى الجذر (حيث parent = NULL)
        {
            path.push_back(temp->action); // إضافة الحركة التي أدت إلى هذه العقدة إلى المسار
            temp = temp->parent;// الانتقال إلى الأب
        }
    }

    //طباعة حركات المسار إذا تم العثور على الهدف
    if(goalNode != NULL)
     {
     cout <<"The goal has been reached\n";
     cout << "Path:\n"; vector<Node*> fullPath;// لتخزين المسار الكامل من الجذر إلى الهدف

      Node* temp = goalNode;// بدء من عقدة الهدف
      while(temp != NULL) // طالما لم نصل إلى الجذر
       {
      fullPath.push_back(temp);// إضافة العقدة الحالية إلى المسار الكامل
      temp = temp->parent; // الانتقال إلى الأب
}

for(int i = fullPath.size()-1; i >= 0; i--) // طباعة المسار من الجذر إلى الهدف
{   Node* n = fullPath[i];// الحصول على العقدة الحالية من المسار الكامل

    if(n->parent != NULL) // إذا لم تكن عقدة الجذر، نطبع الحركة والحالة
    {

        // الحركة
        if(n->action == Direction::Up) cout << "UP";
        else if(n->action == Direction::Down) cout << "DOWN";
        else if(n->action == Direction::Left) cout << "LEFT";
        else if(n->action == Direction::Right) cout << "RIGHT";

        cout << " -> State: (";

        // الموقع & الوقود
        cout << n->state.agent_pos.row << ","  << n->state.agent_pos.col << ", f:" << n->state.fuel << ", ";

        // العملات
        cout << (n->state.c1 ? "t" : "f") << "," << (n->state.c2 ? "t" : "f") << "," << (n->state.c3 ? "t" : "f") << "," << (n->state.c4 ? "t" : "f"); cout << ")" ;
       // printCoins(n->state.collected_coins);cout << ")" ;
        cout << " frontier: " << n->frontier_size  << endl;
        
}
}
    } else
     {
        cout << "No Solution\n";
    }

    cout << "nodes Expanded: " << nodes << endl;
    cout << "time: " << time << " ms\n";
    return ;

    //return {goalNode != NULL, path, nodes, time};// إرجاع نتيجة البحث
}
#include <stack>

void DFS(const State &start, const State &goal) 
{
    int nodes = 0;// عداد للعقد التي تم توسيعها
    Node* goalNode = NULL; // لتخزين عقدة الهدف إذا تم العثور عليها

    auto startTime = chrono::high_resolution_clock::now(); // بدء قياس الوقت

    stack<Node*> frontier;// لتخزين العقد التي سيتم استكشافها
    vector<State> visited; // لتخزين الحالات التي تم زيارتها لمنع تكرار ال states في visited

    Node* root = new Node(start, NULL, Direction::none, 0,0);// تم إنشاء عقدة الجذر باستخدام الحالة الابتدائية، لا يوجد أب لها ولا حركة وعدد فرونتير =0
    frontier.push(root);// إضافة عقدة الجذر إلى الفرونتير
    visited.push_back(start); //اضافة الحالة الابتدائية إلى visited لمنع زيارتها مرة أخرى 

    while(!frontier.empty())
     {

        Node* current = frontier.top();
        frontier.pop();
        nodes++;

        //  تحقق الهدف
        if(isGoal(current->state, goal)) // إذا تم العثور على الهدف، نخرج من حلقة التكرار
        {
            goalNode = current;
            break;
        }

        vector<State> nextStates = getSuccessors(current->state);// الحصول على الحالات التالية الممكنة من الحالة الحالية بناءً على الحركات الأربعة 

        Direction actions[4] = {
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right
        };
        //cout << "next states: " << nextStates.size() << endl;
        for(int i = nextStates.size() - 1; i >= 0; i--) // لكل حالة تالية (نبدأ من النهاية لضمان استكشاف الحالات بالترتيب الصحيح في DFS)
         {

            bool found = false;// فلاق للتحقق مما إذا كانت الحالة التالية قد تم زيارتها بالفعل

            for(int j = 0; j < visited.size(); j++) // البحث في visited
            {
                if(comparison_state(nextStates[i], visited[j])) // إذا تم العثور على الحالة في visited، نعتبرها حالة مكررة
                {
                    found = true;
                    break;
                }
            }

            if(!found) // إذا الحالة جديدة يتم الإنشاء
            {
                Node* child = new Node(nextStates[i], current, actions[i], frontier.size(),0);//
                frontier.push(child);
                visited.push_back(nextStates[i]);
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();// نهاية قياس الوقت
    double time = chrono::duration<double, milli>(endTime - startTime).count();// حساب الوقت  بالميلي ثانية

    // display 
    if(goalNode != NULL)
    {
        cout << "Result Reached (Goal Found)\n";
        cout << "Path:\n";

        vector<Node*> fullPath;
        Node* temp = goalNode;

        while(temp != NULL) {
            fullPath.push_back(temp);
            temp = temp->parent;
        }

        for(int i = fullPath.size()-1; i >= 0; i--) {

            Node* n = fullPath[i];

            if(n->parent != NULL) {

                if(n->action == Direction::Up) cout << "UP";
                else if(n->action == Direction::Down) cout << "DOWN";
                else if(n->action == Direction::Left) cout << "LEFT";
                else if(n->action == Direction::Right) cout << "RIGHT";

                cout << " -> State: ("; cout << n->state.agent_pos.row << ","  << n->state.agent_pos.col << ", f:" << n->state.fuel << ", ";

                cout << (n->state.c1 ? "t" : "f") << "," << (n->state.c2 ? "t" : "f") << ","  << (n->state.c3 ? "t" : "f") << "," << (n->state.c4 ? "t" : "f");cout << ")";

                cout << " frontier: " << n->frontier_size << endl;
            }
        }
    }
    else
    {
        cout << "No Solution\n";
    }

    cout << "Nodes Expanded: " << nodes << endl;
    cout << "time: " << time << " ms\n";
}


// تم استخدام دالة مساعدة للتحكم في عمق البحث في IDS
Node*control_depth_limited(const State &start, const State &goal, int limit)
{
    stack<Node*> frontier;
    vector<State> visited;

    Node* root = new Node(start, NULL, Direction::none, 0, 0);
    frontier.push(root);

    while(!frontier.empty()) {

        Node* current = frontier.top();
        frontier.pop();

        //اذا تم العثور على الهدف، نرجع العقدة الحالية
        if(isGoal(current->state, goal)) {
            return current;
        }

        // إذا تجاوزنا الحد الأقصى للعمق، لا نتابع استكشاف هذه العقدة
        if(current->depth >= limit)
            continue;

        vector<State> nextStates = getSuccessors(current->state);// الحصول على الحالات التالية الممكنة من الحالة الحالية بناءً على الحركات الأربعة

        Direction actions[4] = {
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right
        };

        for(int i = nextStates.size()-1; i >= 0; i--) 
        {

            bool found = false;// للتحقق مما إذا كانت الحالة التالية قد تم زيارتها بالفعل

             // البحث في visited
            for(int j = 0; j < visited.size(); j++) {
                if(comparison_state(nextStates[i], visited[j])) {
                    found = true;// تم العثور على الحالة في visited، نعتبرها حالة مكررة
                    break;
                }
            }

            if(!found) 
            {   // إذا الحالة جديدة يتم الإنشاءوزيادة العمق ب 1
                Node* child = new Node( nextStates[i], current,actions[i], frontier.size(),current->depth + 1);
                frontier.push(child);
                visited.push_back(nextStates[i]);// إضافة الحالة التالية إلى لمنع زيارتها مرة أخرى في المستقبل
            }
        }
    }

    return NULL;
}


void IDS(const State &start, const State &goal)
{
    auto startTime = chrono::high_resolution_clock::now();// بدء قياس الوقت

    for(int depth = 0; depth <= 50; depth++)
     {
        // استدعاء دالة البحث المحدود التي تتحكم في عمق البحث وبها زيادة في العمق ب 1 في كل مرة حتى نصل إلى الحد الأقصى للعمق أو نجد الهدف
        Node* result = control_depth_limited(start, goal, depth);
        if(result != NULL)
         { cout << "goal found \n";
           cout << "depth now : " << depth << endl;

            vector<Node*> path;// لتخزين المسار من الهدف إلى الجذر
            Node* temp = result;// بدء من عقدة الهدف

            while(temp != NULL)
             {
                path.push_back(temp);// إضافة العقدة الحالية إلى المسار
                temp = temp->parent;// الانتقال إلى الأب
            }

            for(int i=path.size()-1;i>= 0;i--) 
            {
                 Node* n = path[i];// الحصول على العقدة الحالية من المسار

                if(n->parent != NULL)
                 {
                    if(n->action == Direction::Up) cout << "UP";
                    else if(n->action == Direction::Down) cout << "DOWN";
                    else if(n->action == Direction::Left) cout << "LEFT";
                    else if(n->action == Direction::Right) cout << "RIGHT";

                    cout << " -> ("  << n->state.agent_pos.row << "," << n->state.agent_pos.col << ")" << ", f:" << n->state.fuel << "  ";
                     cout <<"("<<(n->state.c1 ? "t" : "f") << "," << (n->state.c2 ? "t" : "f") << "," << (n->state.c3 ? "t" : "f") << "," << (n->state.c4 ? "t" : "f"); cout << ")" ;
                    // printCoins(n->state.collected_coins);cout << ")" ;
                     cout << " frontier: " << n->frontier_size  << endl;
        
                }
            }

            break;// تم العثور على الهدف، نخرج من حلقة التكرار
        }
    }

    auto endTime = chrono::high_resolution_clock::now();// نهاية قياس الوقت
    double time = chrono::duration<double, milli>(endTime - startTime).count();// حساب الوقت  بالميلي ثانية

    cout << "time: " << time << " ms\n";
}