#include "search.h"
#include "grid_problem.h"
#include <queue> //used for BFS
#include <vector>// used for visited and path
#include <chrono>// used for measuring execution time
#include <iostream>
#include <stack> // used for DFS
#include <fstream>// used for output file

using namespace std;

//مقارنة بين حالتين لتجنب تكرار ال states في visited
bool comparison_state(const State &a, const State &b) {
    return a.agent_pos.row == b.agent_pos.row &&
           a.agent_pos.col == b.agent_pos.col &&
           a.fuel == b.fuel &&
           a.c1 == b.c1 && a.c2 == b.c2 && a.c3 == b.c3 &&a.c4 == b.c4;
}


 void BFS(const State &start, const State &goal, ofstream &out) 
{
     int last_depth = 0;
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
        last_depth = current->depth;

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
                Node* child = new Node(nextStates[i], current, actions[i], frontier.size(),current->depth + 1);// إنشاء عقدة جديدة للحالة التالية، مع الإشارة إلى الأب  والحركة التي أدت إليها وعدد الفرونتير الحالي 
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
     out <<"goal found\n";
     out << "Level: " << goalNode->depth << endl;
     out << "Path:\n";
     vector<Node*> fullPath;// لتخزين المسار الكامل من الجذر إلى الهدف

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
        if(n->action == Direction::Up) out << "UP";
        else if(n->action == Direction::Down) out << "DOWN";
        else if(n->action == Direction::Left) out << "LEFT";
        else if(n->action == Direction::Right) out << "RIGHT";

        out << " -> State: (";

        // الموقع & الوقود
        out << n->state.agent_pos.row << ","  << n->state.agent_pos.col << ", f:" << n->state.fuel << ", ";

        // العملات
        out << (n->state.c1 ? "t" : "f") << "," << (n->state.c2 ? "t" : "f") << "," << (n->state.c3 ? "t" : "f") << "," << (n->state.c4 ? "t" : "f"); out << ")" ;
        out << " frontier: " << n->frontier_size  << endl;
        
}
}
    } else
     { out << "No Solution\n"; 
        out << " Level : " << last_depth << endl;
    
    }
  
    out << "nodes Expanded: " << nodes << endl;
    out << "time: " << time << " ms\n";
    return ;
}


void DFS(const State &start, const State &goal, ofstream &out) 
{  int last_depth = 0;
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
        last_depth = current->depth;

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
                Node* child = new Node(nextStates[i], current, actions[i], frontier.size(),current->depth + 1);//
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
        out << "Goal Found\n";
        out << "depth: " << goalNode->depth << endl;
        out << "Path:\n";

        vector<Node*> fullPath;
        Node* temp = goalNode;

        while(temp != NULL) {
            fullPath.push_back(temp);
            temp = temp->parent;
        }

        for(int i = fullPath.size()-1; i >= 0; i--) {

            Node* n = fullPath[i];

            if(n->parent != NULL) {

                if(n->action == Direction::Up) out << "UP";
                else if(n->action == Direction::Down) out << "DOWN";
                else if(n->action == Direction::Left) out << "LEFT";
                else if(n->action == Direction::Right) out << "RIGHT";

                out << " -> State: ("; out << n->state.agent_pos.row << ","  << n->state.agent_pos.col << ", f:" << n->state.fuel << ", ";
                out << (n->state.c1 ? "t" : "f") << "," << (n->state.c2 ? "t" : "f") << ","  << (n->state.c3 ? "t" : "f") << "," << (n->state.c4 ? "t" : "f");out << ")";
                out << " frontier: " << n->frontier_size << endl;
            }
        }
    }
    else
    {
        out << "No Solution\n";
        out << "depth " << last_depth << endl;
    } 

    out << "Nodes Expanded: " << nodes << endl;
    out << "time: " << time << " ms\n";
}

// تم استخدام دالة مساعدة للتحكم في عمق البحث في IDS
Node*control_depth_limited(const State &start, const State &goal, int limit, int &nodes)
{  
    stack<Node*> frontier;
    vector<State> visited;

    Node* root = new Node(start, NULL, Direction::none, 0, 0);
    frontier.push(root);

    while(!frontier.empty()) {

        Node* current = frontier.top();
        frontier.pop();
        nodes++;

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


void IDS(const State &start, const State &goal , ofstream &out)
{   int last_depth;

    auto startTime = chrono::high_resolution_clock::now();// بدء قياس الوقت
     
    int nodes = 0;
    for(int depth = 0; depth <= 100; depth++)
     {
        nodes = 0; //  عدد العقد التي تم توسيعها في هذا العمق

        // استدعاء دالة البحث المحدود التي تتحكم في عمق البحث وبها زيادة في العمق ب 1 في كل مرة حتى نصل إلى الحد الأقصى للعمق أو نجد الهدف
        Node* result = control_depth_limited(start, goal, depth, nodes);
        last_depth= depth;

        if(result != NULL)
         { 
            
            out << "goal found \n";
            out << "depth  : " << depth << endl;

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
                    if(n->action == Direction::Up) out << "UP";
                    else if(n->action == Direction::Down) out << "DOWN";
                    else if(n->action == Direction::Left) out << "LEFT";
                    else if(n->action == Direction::Right) out << "RIGHT";

                    out << " -> ("  << n->state.agent_pos.row << "," << n->state.agent_pos.col << ")" << ", f:" << n->state.fuel << " ( ";
                    out << (n->state.c1 ? "t" : "f") << "," << (n->state.c2 ? "t" : "f") << ","  << (n->state.c3 ? "t" : "f") << "," << (n->state.c4 ? "t" : "f");out << ")";
                    out << " frontier: " << n->frontier_size  << endl;
        
                }
               
            }

           auto endTime = chrono::high_resolution_clock::now();// نهاية قياس الوقت
           double time = chrono::duration<double, milli>(endTime - startTime).count();// حساب الوقت  بالميلي ثانية

           out << "nodes Expanded: " << nodes << endl; //  فقط depth الأخير
           out << "time: " << time << " ms\n";  
          

           return; 
        }
        
    }
       out << "nodes Expanded: " << nodes << endl;
      
    // إذا لم يتم العثور على الهدف بعد استكشاف جميع الأعماق حتى الحد الأقصى، نطبع "No Solution"
     out << "No Solution\n";
    //out << "depth " << last_depth << endl;

    auto endTime = chrono::high_resolution_clock::now();// نهاية قياس الوقت
    double time = chrono::duration<double, milli>(endTime - startTime).count();// حساب الوقت  بالميلي ثانية
    
    out << "time: " << time << " ms\n"; 
}