#include "search.h"
#include <queue>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

struct Node {
    State state;// الحالة الحالية
    Node* parent;//بوينتر إلى الأب في شجرة البحث
    Direction action; // الحركة التي أدت إلى هذه الحالة
    int frontier_size;//
   
    // Constructor
    Node(State s, Node* p, Direction a, int f ) 
    {
        state = s;
        parent = p;
        action = a;
        frontier_size = f;
    }
};

//مقارنة بين حالتين لتجنب تكرار ال states في visited
bool comparison_state(const State &a, const State &b) {
    return a.agent_pos.row == b.agent_pos.row &&
           a.agent_pos.col == b.agent_pos.col &&
           a.fuel == b.fuel &&
           a.collected_coins == b.collected_coins;
           
}

//display the coins 
void printCoins(uint8_t coins) 
{
   for(int i = 0; i < 4; i++) {
     if(coins & (1 << i))  cout << "t";
      else cout << "f";

    if(i < 3) cout << ",";// للفصل بين العملات في طباعة 
    }
}


 void BFS(const State &start, const State &goal) 
{
    
    int nodes = 0;
    Node* goalNode = NULL;

    auto startTime = chrono::high_resolution_clock::now();// بدء قياس الوقت

    queue<Node*> frontier; //لتخزين العقد التي سيتم استكشافها
    vector<State> visited; // لتخزين الحالات التي تم زيارتها

    Node* root = new Node(start, NULL, Direction::none, 0);//تم إنشاء عقدة الجذر باستخدام الحالة الابتدائية، لا يوجد أب لها ولا حركة وعدد فرونتير =0
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
                Node* child = new Node(nextStates[i], current, actions[i], frontier.size());// إنشاء عقدة جديدة للحالة التالية، مع الإشارة إلى الأب  والحركة التي أدت إليها وعدد الفرونتير الحالي 
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
        printCoins(n->state.collected_coins);cout << ")" ;
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