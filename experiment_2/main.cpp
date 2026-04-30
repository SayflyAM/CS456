#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool PRINT_VISITED_STATES = false;


struct Position {
    int x;
    int y;
};

struct State {
    int x;
    int y;
    int fuel;
    int coinsMask;   // 4 bits for 4 coins
};

struct SearchResult {
    bool found;
    vector<State> visitedStates;
    vector<State> path;
    int nodesExpanded;
    int uniqueVisited;
    int maxFrontier;
    int solutionDepth;
    int depthLimitReached;

    SearchResult() {
        found = false;
        nodesExpanded = 0;
        uniqueVisited = 0;
        maxFrontier = 0;
        solutionDepth = -1;
        depthLimitReached = -1;
    }
};

// Game class

class GridGame {
private:
    int width;
    int height;
    int maxFuel;

    Position goal;
    Position fuelStation;

    vector<Position> coins;
    vector<Position> walls;

public:
    GridGame() {

        width = 10;
        height = 10;
        maxFuel = 20;

        goal = {1, 1};
        fuelStation = {4, 9};

        // coins
        coins.push_back({2, 9}); // C1
        coins.push_back({8, 9}); // C2
        coins.push_back({5, 7}); // C3
        coins.push_back({9, 2}); // C4

        // walls
        walls.push_back({3, 6});
        walls.push_back({3, 7});
        walls.push_back({3, 8});
        walls.push_back({6, 8});
        walls.push_back({7, 4});
        walls.push_back({8, 4});
    }

    // check if cell is inside grid
    bool inBounds(int x, int y) {
        return x >= 1 && x <= width && y >= 1 && y <= height;
    }

    // check wall
    bool isWall(int x, int y) {
        for (int i = 0; i < (int)walls.size(); i++) {
            if (walls[i].x == x && walls[i].y == y) {
                return true;
            }
        }
        return false;
    }

    // check fuel station
    bool isFuelStation(int x, int y) {
        return x == fuelStation.x && y == fuelStation.y;
    }

    // Find coin index
    int getCoinIndex(int x, int y) {
        for (int i = 0; i < (int)coins.size(); i++) {
            if (coins[i].x == x && coins[i].y == y) {
                return i;
            }
        }
        return -1;
    }

    // start state fix
    State normalizeState(State s) {
        if (s.fuel < 0) s.fuel = 0;
        if (s.fuel > maxFuel) s.fuel = maxFuel;

        // if start on fuel station
        if (isFuelStation(s.x, s.y)) {
            s.fuel = maxFuel;
        }

        // if start on coin
        int coinIndex = getCoinIndex(s.x, s.y);
        if (coinIndex != -1) {
            s.coinsMask = s.coinsMask | (1 << coinIndex);
        }

        return s;
    }

    // goal test
    bool isGoal(State s) {
        int allCoins = 15; // 1111
        return s.x == goal.x && s.y == goal.y && s.coinsMask == allCoins;
    }

    // make state key
    string encodeState(State s) {
        return to_string(s.x) + "," +
               to_string(s.y) + "," +
               to_string(s.fuel) + "," +
               to_string(s.coinsMask);
    }

    // print state as text
    string stateToString(State s) {
        string text = "<";
        text += to_string(s.x) + ", ";
        text += to_string(s.y) + ", ";
        text += to_string(s.fuel);

        for (int i = 0; i < 4; i++) {
            bool gotCoin = (s.coinsMask & (1 << i)) != 0;
            text += ", ";
            text += (gotCoin ? "t" : "f");
        }

        text += ">";
        return text;
    }

    // get next states
    vector<State> getNextStates(State s) {
        vector<State> nextStates;

        if (s.fuel <= 0) {
            return nextStates;
        }

        // order: Up, Right, Down, Left
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};

        for (int i = 0; i < 4; i++) {
            int newX = s.x + dx[i];
            int newY = s.y + dy[i];

            if (!inBounds(newX, newY)) {
                continue;
            }

            if (isWall(newX, newY)) {
                continue;
            }

            State next;
            next.x = newX;
            next.y = newY;
            next.fuel = s.fuel - 1;
            next.coinsMask = s.coinsMask;

            // refill fuel
            if (isFuelStation(newX, newY)) {
                next.fuel = maxFuel;
            }

            // collect coin
            int coinIndex = getCoinIndex(newX, newY);
            if (coinIndex != -1) {
                next.coinsMask = next.coinsMask | (1 << coinIndex);
            }

            nextStates.push_back(next);
        }

        return nextStates;
    }

    // build path
    vector<State> buildPath(string startKey,
                            string goalKey,
                            unordered_map<string, string>& parent,
                            unordered_map<string, State>& savedStates) {
        vector<State> path;

        string current = goalKey;
        path.push_back(savedStates[current]);

        while (current != startKey) {
            current = parent[current];
            path.push_back(savedStates[current]);
        }

        reverse(path.begin(), path.end());
        return path;
    }

    // BFS

    SearchResult bfs(State startInput) {
        SearchResult result;

        State start = normalizeState(startInput);
        string startKey = encodeState(start);

        queue<State> frontier;
        unordered_set<string> visited;
        unordered_map<string, string> parent;
        unordered_map<string, State> savedStates;

        frontier.push(start);
        visited.insert(startKey);
        savedStates[startKey] = start;

        result.maxFrontier = 1;

        while (!frontier.empty()) {
            State current = frontier.front();
            frontier.pop();

            string currentKey = encodeState(current);

            result.visitedStates.push_back(current);
            result.nodesExpanded++;

            if (isGoal(current)) {
                result.found = true;
                result.path = buildPath(startKey, currentKey, parent, savedStates);
                result.solutionDepth = (int)result.path.size() - 1;
                result.uniqueVisited = (int)visited.size();
                return result;
            }

            vector<State> nextStates = getNextStates(current);

            for (int i = 0; i < (int)nextStates.size(); i++) {
                State next = nextStates[i];
                string nextKey = encodeState(next);

                if (visited.find(nextKey) == visited.end()) {
                    visited.insert(nextKey);
                    parent[nextKey] = currentKey;
                    savedStates[nextKey] = next;
                    frontier.push(next);
                }
            }

            if ((int)frontier.size() > result.maxFrontier) {
                result.maxFrontier = (int)frontier.size();
            }
        }

        result.uniqueVisited = (int)visited.size();
        return result;
    }

    // DFS

    SearchResult dfs(State startInput) {
        SearchResult result;

        State start = normalizeState(startInput);
        string startKey = encodeState(start);

        stack<State> frontier;
        unordered_set<string> visited;
        unordered_map<string, string> parent;
        unordered_map<string, State> savedStates;

        frontier.push(start);
        visited.insert(startKey);
        savedStates[startKey] = start;

        result.maxFrontier = 1;

        while (!frontier.empty()) {
            State current = frontier.top();
            frontier.pop();

            string currentKey = encodeState(current);

            result.visitedStates.push_back(current);
            result.nodesExpanded++;

            if (isGoal(current)) {
                result.found = true;
                result.path = buildPath(startKey, currentKey, parent, savedStates);
                result.solutionDepth = (int)result.path.size() - 1;
                result.uniqueVisited = (int)visited.size();
                return result;
            }

            vector<State> nextStates = getNextStates(current);

            // Reverse because stack is LIFO
            for (int i = (int)nextStates.size() - 1; i >= 0; i--) {
                State next = nextStates[i];
                string nextKey = encodeState(next);

                if (visited.find(nextKey) == visited.end()) {
                    visited.insert(nextKey);
                    parent[nextKey] = currentKey;
                    savedStates[nextKey] = next;
                    frontier.push(next);
                }
            }

            if ((int)frontier.size() > result.maxFrontier) {
                result.maxFrontier = (int)frontier.size();
            }
        }

        result.uniqueVisited = (int)visited.size();
        return result;
    }

    // IDS helper

    bool depthLimitedDFS(State current,
                         int depthLimit,
                         vector<State>& currentPath,
                         unordered_set<string>& pathStates,
                         unordered_map<string, int>& bestDepth,
                         unordered_set<string>& allVisited,
                         SearchResult& result) {
        string currentKey = encodeState(current);

        // Avoid repeated state in same limit
        if (bestDepth.find(currentKey) != bestDepth.end()) {
            if (bestDepth[currentKey] >= depthLimit) {
                return false;
            }
        }

        bestDepth[currentKey] = depthLimit;

        result.visitedStates.push_back(current);
        result.nodesExpanded++;
        allVisited.insert(currentKey);

        if ((int)currentPath.size() > result.maxFrontier) {
            result.maxFrontier = (int)currentPath.size();
        }

        if (isGoal(current)) {
            result.path = currentPath;
            return true;
        }

        if (depthLimit == 0) {
            return false;
        }

        vector<State> nextStates = getNextStates(current);

        for (int i = 0; i < (int)nextStates.size(); i++) {
            State next = nextStates[i];
            string nextKey = encodeState(next);

            if (pathStates.find(nextKey) != pathStates.end()) {
                continue;
            }

            pathStates.insert(nextKey);
            currentPath.push_back(next);

            bool found = depthLimitedDFS(next,
                                         depthLimit - 1,
                                         currentPath,
                                         pathStates,
                                         bestDepth,
                                         allVisited,
                                         result);

            if (found) {
                return true;
            }

            currentPath.pop_back();
            pathStates.erase(nextKey);
        }

        return false;
    }

    // IDS

    SearchResult ids(State startInput, int maxDepth = 200) {
        SearchResult result;

        State start = normalizeState(startInput);
        string startKey = encodeState(start);

        unordered_set<string> allVisited;

        for (int depth = 0; depth <= maxDepth; depth++) {
            vector<State> currentPath;
            currentPath.push_back(start);

            unordered_set<string> pathStates;
            pathStates.insert(startKey);

            unordered_map<string, int> bestDepth;

            bool found = depthLimitedDFS(start,
                                         depth,
                                         currentPath,
                                         pathStates,
                                         bestDepth,
                                         allVisited,
                                         result);

            if (found) {
                result.found = true;
                result.solutionDepth = (int)result.path.size() - 1;
                result.uniqueVisited = (int)allVisited.size();
                result.depthLimitReached = depth;
                return result;
            }
        }

        result.uniqueVisited = (int)allVisited.size();
        return result;
    }

    // print result
    void printResult(string name, SearchResult result) {
        cout << "\n----------------------------------------\n";
        cout << "Algorithm: " << name << endl;
        cout << "Found Goal: " << (result.found ? "Yes" : "No") << endl;
        cout << "Nodes Expanded: " << result.nodesExpanded << endl;
        cout << "Unique Visited States: " << result.uniqueVisited << endl;
        cout << "Max Frontier / Depth: " << result.maxFrontier << endl;

        if (result.found) {
            cout << "Solution Depth: " << result.solutionDepth << endl;
        }

        if (name == "IDS" && result.found) {
            cout << "Depth Limit Reached: " << result.depthLimitReached << endl;
        }

        if (PRINT_VISITED_STATES) {
            cout << "\nVisited States:\n";
            for (int i = 0; i < (int)result.visitedStates.size(); i++) {
                cout << i + 1 << ". " << stateToString(result.visitedStates[i]) << endl;
            }
        }

        if (result.found) {
            cout << "\nSolution Path:\n";
            for (int i = 0; i < (int)result.path.size(); i++) {
                cout << i + 1 << ". " << stateToString(result.path[i]) << endl;
            }
        }

        cout << "\nSummary: " << name
             << ", Found = " << (result.found ? "Yes" : "No")
             << ", Depth = " << result.solutionDepth
             << ", Expanded = " << result.nodesExpanded
             << ", Visited = " << result.uniqueVisited
             << endl;
    }
};



int main() {
    GridGame game;

    // 5 start states
    vector<State> startStates;
    startStates.push_back({2, 2, 20, 0});
    startStates.push_back({4, 5, 20, 0});
    startStates.push_back({6, 6, 20, 0});
    startStates.push_back({8, 8, 20, 0});
    startStates.push_back({10, 1, 20, 0});

    for (int i = 0; i < (int)startStates.size(); i++) {

        cout << "\n========================================\n";

        cout << "TEST CASE " << i + 1 << endl;

        cout << "========================================\n";

        State start = game.normalizeState(startStates[i]);
        cout << "Start State: " << game.stateToString(start) << endl;

        SearchResult bfsResult = game.bfs(startStates[i]);
        game.printResult("BFS", bfsResult);

        SearchResult dfsResult = game.dfs(startStates[i]);
        game.printResult("DFS", dfsResult);

        SearchResult idsResult = game.ids(startStates[i], 200);
        game.printResult("IDS", idsResult);
    }

    return 0;
}