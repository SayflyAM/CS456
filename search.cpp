#include "search.h"
#include <queue>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

struct Node {
    State state;
    Node* parent;
    Direction action;

    Node(State s, Node* p, Direction a) {
        state = s;
        parent = p;
        action = a;
    }
};

//مقارنة بين حالتين لتجنب تكرار ال states في visited
bool comparison_state(const State &a, const State &b) {
    return a.agent_pos.row == b.agent_pos.row &&
           a.agent_pos.col == b.agent_pos.col &&
           a.fuel == b.fuel &&
           a.collected_coins == b.collected_coins;
}


SearchResult BFS(const State &start, const State &goal) {

    auto startTime = chrono::high_resolution_clock::now();

    queue<Node*> frontier;
    vector<State> visited; // لتخزين الحالات التي تم زيارتها

    Node* root = new Node(start, NULL, Direction::Up);
    frontier.push(root);
    visited.push_back(start);

    int nodes = 0;
    Node* goalNode = NULL;

    while(!frontier.empty()) {

        Node* current = frontier.front();
        frontier.pop();

        nodes++;

        if(isGoal(current->state, goal)) {
            goalNode = current;
            break;
        }

        //احضار الحالات التالية
        vector<State> nextStates = getSuccessors(current->state);

        Direction actions[4] = {
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right
        };

        for(int i = 0; i < nextStates.size(); i++) {

            bool found = false;

            //  البحث في visited
            for(int j = 0; j < visited.size(); j++) {
                if(comparison_state(nextStates[i], visited[j])) {
                    found = true;
                    break;
                }
            }

            // إذا الحالة جديدة
            if(!found) {
                Node* child = new Node(nextStates[i], current, actions[i]);
                frontier.push(child);
                visited.push_back(nextStates[i]);
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(endTime - startTime).count();

    //استخراج المسار من goalNode إلى root
    vector<Direction> path;

    if(goalNode != NULL) {
        Node* temp = goalNode;

        while(temp->parent != NULL) {
            path.push_back(temp->action);
            temp = temp->parent;
        }
    }

    //طباعة حركات المسار إذا تم العثور على الهدف
    if(goalNode != NULL) {
        cout << "Result Reached (Goal Found)!\n";
        cout << "Path Sequence:\n";

        for(int i = path.size()-1; i >= 0; i--) {
            if(path[i] == Direction::Up) cout << "UP\n";
            else if(path[i] == Direction::Down) cout << "DOWN\n";
            else if(path[i] == Direction::Left) cout << "LEFT\n";
            else if(path[i] == Direction::Right) cout << "RIGHT\n";
        }
    } else {
        cout << "No Solution\n";
    }

    cout << "\n**************\n";
    cout << "Nodes Expanded: " << nodes << endl;
    cout << "Time: " << time << " ms\n";

    return {goalNode != NULL, path, nodes, time};
}