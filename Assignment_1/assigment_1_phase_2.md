<img width="962" height="315" alt="image" src="https://github.com/user-attachments/assets/9727c911-6ccd-4cec-809a-8979ad86ae91" />Pass by value:
This so bad because when we will use BFS and it expands 100,000 nodes, this will triggered 100,000 massive memory.
bool isGoal(State s ) {
    retrun s.fuel == 0;
}
To fix this we need to pass by Const Reference
what this mean?
pass the memory address, don't copy the data.

bool isGoal(const State& s) {
    rturen s.fuel ==0;
}





____________________________________________________________________________________________________
**********************explain code ************************
in main 
 The target state was determined, which is reaching the location (1,1) while collecting all the coins, then a set of different states was created, and after that, the algorithm function was called.


 in grid_problem.h 
It contains basic definitions such as the state representing the agent's location, fuel, and coins, in addition to defining possible movement directions using an enum, and defining basic functions such as isGoal to check for reaching the goal and getSuccessors to generate the next states.

in grid_problem.cpp
The getSuccessors function generates all possible states from the current state by trying the four moves, while checking the grid boundaries and fuel consumption, in addition to updating the coin state when they are collected, and refueling when reaching the gas station.

in search.h
The BFS function was defined in file , and the type void was used, and the second definition was commented out, as well as the struct in the Grid Problem file, because the results are printed directly inside the function.


in search.cpp
The BFS function explores states using a queue according to the FIFO principle, where the next states are generated using getSuccessors, with duplication prevented using visited, and upon reaching the goal, the path is extracted by tracing the parents (parent pointers), then the path and the remaining data are printed.

____________________________________________________________________________________________________اريد توضيح علاش كتبت التالي لكي افهم 
bool c1, c2, c3, c4;// تم استخدام 4 متغيرات بوليانية لتمثيل جمع كل عملة بشكل منفصل بدلاً من استخدام
____________________________________________________________________________________________________

goal.agent_pos = {1,1};// الهدف هو الوصول إلى (1,1)

ممكن توضيح كيف عرفت انه 
 جواب : موجود في فايل  الاسايمنت ورقة 2  
 State: < X -pos, Y -pos, Fuel,C1, C2, C3, C4 >  
Goal: < 1, 1, ?, t, t, t, t>
 

(1,1) that is the goal why do not  be like (  1, 1, ?, t, t, t, t )
--------------------------------------------------------------------------------------------------
ممكن شرح لهدا شنو

جواب : هذا ال10 حالات يلي بنختبروهم لكل الخوارزميات  وموجود ف كومنت تمثيل متاعه
// { {tests[i].agent_pos.row, tests[i].agent_pos.col}, tests[i].fuel, tests[i].collected_coins }

ويكافئ هذا 
 State: < X -pos, Y -pos, Fuel,C1, C2, C3, C4 > 
 
 بس لان انت ف بداية استخدمت Bitmasks وانا مش فاهمة طريقة استخدامه مية ف مية مع ان فهمت معناه وان افضل  من bool  بس مش متعودة بيه ف درت bool وقلت بعد م نتاكد من كود تمام يشتغل ونفهم طريقته bitmasks عادي  نلغوا كومنت ونردوه  
 
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
  -----------------------------------------------------------------------------------------------
  //تحقق مما إذا كانت الحالة الحالية هي حالة الهدف أم لا
//goal state is defined as the agent being at position (1,1) and having collected all coins (C1 to C4  == 15 in binary)
bool isGoal(const State &current_state, const State &goal_state) {

    return current_state.agent_pos.row == goal_state.agent_pos.row &&
           current_state.agent_pos.col == goal_state.agent_pos.col &&
          // current_state.collected_coins == goal_state.collected_coins;
          current_state.c1 && current_state.c2 &&
          current_state.c3 && current_state.c4;
}

تمام هنا مشتغله صح بخصوص  
collected all coins (C1 to C4  == 15 in binary)

لكن في ملف 
grid_problem.h
سطر 29 
علاش كاتبه bool 
 جواب : 
  bool c1, c2, c3, c4;// تم استخدام 4 متغيرات بوليانية لتمثيل جمع كل عملة بشكل منفصل بدلاً من استخدام
  هنا لان نبي نمثل عملات ب t or f يعني يلي يهمني وان وصلت للقول كلهم يتغيروا للترو  مش جمع ونتاكد ان وصلت  لل 15 in binary
--------------------------------------------------------------------------------------------------

 
جواب : قصدك تعريف دالة ؟؟ علاش غيرته لفويد لان حطيت طباعة فيه ودرتله استدعاء ف ميين  قلت ليش لازم يرجعلي بالبيانات للمين معنديش شي ثاتي بعده بنخدمه ف خليته يطبع ف نفس دالة وخلاص 
ولو قصدك ك دالة كاملة تو نشرخ تمام 
نبي شرح لهدا كيف درتيه بطريقة الهادي void BFS(const State &start, const State &goal) 
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

---------------------------------------------------------------------------------------------------
