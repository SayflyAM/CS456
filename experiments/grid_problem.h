#pragma once //lode once.

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;



//positon in the grid.

struct Position {
	int x;
	int y;

	bool operator==(const Postion& other) const {
		return x == other.x && y == other.y;
	}
};

// this full search state for th game.


struct state {

	int x;
	int y;
	int fuel;
	uint8_t coinsMask;

	bool operator == (const state& other) const {
		return x== other.x && y==other.y && fuel== other.fuel &&
		coinsMask == other.coinsMask;
	}
};
// cutom hash  so the stat can be used in unordered_set
struct StateHash{
	size_t operator()(const state& s) const noexcept;
};

class GridProblem{

public:
	GridProblem(
		int width,
		int height,
		int maxFuel,
		Position goal,
		Position fuelstation,

		const vector<Positoin>& coinPositions,
		const vector<Positoin>& blockedCells);

	bool inBounds(int x, int y) const;
	bool isBlocked(int x, int y) const;
	bool isGoal(const State& s ) const;


	// state back

	state normalizestate(const state& s ) const;

	//returns successor staes in fixed order
	//up right down left

	vector<state> getSuccessors(const state& s ) const;


	string stateToString(const state& s) const;

	void printState(const State& s) const;

	int getWidth() const {return width_;}
	int getHeight() const {return height_;}
	int getMaxFuel() const {return maxfuel_;}
	int getCoinCount() const {return static_cast<int>(coinPositions_.size());}

private:
	int width_;
	int height_;
	int maxFuel_;
	Postion goal_;
	Postion fuelStation_;
	vector<Positon> coinPositions_;
	vector<vector<bool>> blocked_;




	bool isFuelStation(int x, int y) const;
	int coinIndexAt(int x, int y) const;





		
};



