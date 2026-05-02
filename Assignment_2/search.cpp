#include "search.h"
#include "grid_problem.h"
#include <queue> //used for BFS
#include <vector>// used for visited and path
#include <chrono>// used for measuring execution time
#include <iostream>
#include <stack> // used for DFS
#include <fstream>// used for output file
#include <algorithm> 
using namespace std;

//مقارنة بين حالتين لتجنب تكرار ال states في visited
bool comparison_state(const State &a, const State &b) {
    return a.agent_pos.row == b.agent_pos.row &&
           a.agent_pos.col == b.agent_pos.col &&
           a.fuel == b.fuel &&
           a.c1 == b.c1 && a.c2 == b.c2 && a.c3 == b.c3 &&a.c4 == b.c4;
}

/*الفكرة (h1):
نبدأ من موقع agent
نلقى أقرب coin اللي مازال ما تجمعش
نضيف المسافة
نتحرك له (افتراضيًا)
نكمل على الباقي
*/
//d=∣x1​−x2​∣+∣y1​−y2​∣

int manhattan(Position a, Position b) //لحساب المسافة بين نقطتين
{
    return abs(a.row - b.row) + abs(a.col - b.col);
}

int h1(const State &s)
{
    bool collected[4];// نسخ العملات المجمعة في مصفوفة حتى نعرف العملات المتبقية التي لم يتم جمعها بعد

    collected[0] = s.c1;
    collected[1] = s.c2;
    collected[2] = s.c3;
    collected[3] = s.c4;

    Position current = s.agent_pos;// نبدأ من موقع agent الحالي 

    int total = 0;

    for(int step = 0; step < 4; step++)
    {
        int bestDist = 100000;
        int bestCoin = -1;

        for(int i = 0; i < 4; i++)
        {
            if(collected[i] == false) // إذا كانت العملة لم يتم جمعها بعد، نحسب المسافة لها
            {
                int d = manhattan(current, coins[i]);// يبحث عن أقرب عملة لموقع agent الحالي باستخدام مسافة Manhattan

                if(d < bestDist) // إذا كانت هذه العملة أقرب من أي عملة أخرى وجدناها حتى الآن، نحتفظ بها كأفضل خيار
                {
                    bestDist = d; // تحديث أقرب مسافة
                    bestCoin = i; // تحديث مؤشر العملة الأقرب
                }
            }
        }

        if(bestCoin == -1) // إذا لم نجد أي عملة متبقية (كل العملات تم جمعها)، نكسر الحلقة
            break;

        total += bestDist; // نضيف المسافة إلى إجمالي المسافة التي قطعها agent

        current = coins[bestCoin]; // ننتقل إلى موقع العملة الأقرب (افتراضيًا، لأننا لا نحرك agent فعليًا في هذا الحساب)

        collected[bestCoin] = true; // نعلم أن هذه العملة تم جمعها حتى لا نبحث عنها مرة أخرى في الخطوات التالية
    }

    return total; // نعيد إجمالي المسافة التي يحتاج agent لقطعها لجمع كل العملات المتبقية بناءً على استراتيجية جمع أقرب عملة أولاً
}


void GBFS(const State &start, const State &goal, ofstream &out)
{
    int nodes = 0;
    int last_depth = 0;

    Node* goalNode = NULL;

    auto startTime = chrono::high_resolution_clock::now();

    vector<Node*> frontier; // frontier لتخزين العقد التي سيتم استكشافها
    vector<State> visited;  // visited لتجنب تكرار الحالات
    Node* root = new Node(start,NULL,Direction::none,0,0,h1(start)); // إنشاء عقدة البداية
    frontier.push_back(root); // إضافة عقدة البداية إلى frontier
    visited.push_back(start); // إضافة حالة البداية إلى visited

    while(!frontier.empty())
    {
        sort(frontier.begin(), frontier.end(),[](Node* a, Node* b) // ترتيب العقد حسب أقل heuristic
        { return a->heuristic < b->heuristic; });

        Node* current = frontier[0];// أخذ أفضل عقدة (أقل heuristic)
        frontier.erase(frontier.begin()); // حذفها من frontier
        nodes++;
        last_depth = current->depth;

        // التحقق من الوصول للهدف
        if(isGoal(current->state, goal))
        {
            goalNode = current;
            break;
        }

        // الحصول على الحالات التالية
        vector<State> nextStates =getSuccessors(current->state); // استدعاء دالة getSuccessors للحصول على الحالات التالية الممكنة من الحالة الحالية

        Direction actions[4] =
        {
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right
        };

        for(int i = 0; i < nextStates.size(); i++)
        {

            bool found = false; // التحقق مما إذا كانت الحالة التالية موجودة بالفعل في visited لتجنب تكرارها

            // البحث في visited
            for(int j = 0; j < visited.size(); j++)
            {
                if(comparison_state(nextStates[i], visited[j]))
                {
                    found = true;
                    break;
                }
            }

            // إذا الحالة جديدة
            if(!found)
            {

                int h = h1(nextStates[i]); // حساب heuristic للحالة التالية باستخدام دالة h1
                Node* child = new Node(nextStates[i],current, actions[i],frontier.size(),current->depth + 1,h); // إنشاء عقدة جديدة للحالة التالية مع تحديث المعلومات اللازمة مثل الأب، الحركة التي أدت إلى هذه الحالة، حجم frontier الحالي، العمق، والheuristic
                frontier.push_back(child); // إضافة العقدة الجديدة إلى frontier ليتم استكشافها لاحقًا
                visited.push_back(nextStates[i]);// إضافة الحالة التالية إلى visited لتجنب تكرارها في المستقبل
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();

    double time =chrono::duration<double, milli>(endTime - startTime).count();

    // إذا تم العثور على الهدف
    if(goalNode != NULL)
    {  out << "Goal Found\n"; out << "Depth: "  << goalNode->depth << endl;out << "Heuristic: "<< goalNode->heuristic << endl; out << "Path:\n";

        vector<Node*> path;
        Node* temp = goalNode;

        while(temp != NULL)
        {
            path.push_back(temp);
            temp = temp->parent;

        }

        for(int i = path.size()-1; i >= 0; i--)
        {   Node* n = path[i];

            if(n->parent != NULL)
         {  
            if(n->action == Direction::Up) out << "UP";
            else if(n->action == Direction::Down) out << "DOWN";
            else if(n->action == Direction::Left) out << "LEFT";
            else if(n->action == Direction::Right) out << "RIGHT";

          out << " -> (" << n->state.agent_pos.row << "," << n->state.agent_pos.col << ", fuel: " << n->state.fuel << ")"  << " h:" << n->heuristic<< endl;
          //  out << " -> (" << n->state.agent_pos.row << ","<< n->state.agent_pos.col<< ")"; out << " h:" << n->heuristic; out << endl;
            }

        }
    }

    else
    {
        out << "No Solution\n";
        out << "Depth: "<< last_depth << endl;
    }

    out << "Nodes Expanded: "<< nodes << endl;
    out << "Time: " << time << " ms\n";
}


