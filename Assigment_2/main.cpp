#include <iostream> 
#include <queue>// for priority queue
#include <vector> // for explored set
#include <cmath>// for abs function
#include <chrono> // for  time
#include <fstream>//
using namespace std;

class State{
public:

	int x,y;// position of the agent
	int fuel;// amount of fuel
	bool coins[4];
	int steps;
	int f_score;

	bool operator<(const State& other ) 
	const  {return this->f_score > other.f_score;} 
};

void printState(State s, ofstream &out);

enum dirction{
	up,
	down,
	left,
	right,
};

int coin_places[4][2] ={
	{1,4},
	{5,7},
	{4,9},
	{6,5},

};

int fuel_places[4][2] ={
	{1,3}, 
	{4,5},
	{3,7},
	{2,5},

};

int wall_places[4][2]{

	{2,3},
	{3,5},
	{9,7},
	{1,5},

};




int maxManhattanDistance(State s){
	int distance_larg =0;
	bool allcollected = true;
	//int distance_short=0;
	for(int i=0 ; i<4;i++){

		if(s.coins[i] ==false){
			int dist = abs(s.x -coin_places[i][0]) + abs(s.y - coin_places[i][1]);
		if(dist > distance_larg){
			distance_larg = dist;
		//if(dist < distance_short ){
			//distance_short= dist;
		//}
		}	
		}
	}
	for (int i=0 ; i < 4 ; i++){
		if (!s.coins[i]) {
			allcollected = false;
		}
	}

	if (allcollected) {
		//return  abs(s.x -1) + abs(a.y - 1);
		return abs(s.x -1) + abs(s.y -1);
	}
	return distance_larg;
}

int nearestNeighborSum(State s){

	State temp =s;
	
	
	int coin_to_collect=4;
	int total_distance = 0;
	int closet_coin=1;
	int coins=0;
	for(int i=0;i<4;i++){
		
		if(s.coins[i]==false){
			coins++;
		}
	}
	coin_to_collect = coins;

	while(coin_to_collect > 0){
		int distance_short=100;


		for(int i=0 ; i<4;i++){
		if(temp.coins[i] ==false){
			int dist = abs(temp.x -coin_places[i][0]) + abs(temp.y - coin_places[i][1]);
		
		if(dist < distance_short ){
			distance_short= dist;
			closet_coin = i;
		
		     }
	    }
	    
	}
	    temp.x = coin_places[closet_coin][0];
	    temp.y = coin_places[closet_coin][1];
	    temp.coins[closet_coin] = true;


		total_distance = total_distance + distance_short;
		//total_distance += abs(temp.x - 1) + abs(temp.y - 1);

		coin_to_collect--;
		

	}

total_distance += abs(temp.x -1) + abs(temp.y -1);	
	return total_distance;
}

State createState( int x , int y , int fuel) {
	State s;
	s.x = x;
	s.y = y;
	//s.fuel = fule;
	s.fuel = fuel;
	s.steps = 0;
	s.f_score = 0;

	for (int i=0 ; i < 4 ;i++){
		s.coins[i] = false;
	}
	return s;
}
int heuristic(State s, int heuristicType)
{
	//if (heurisitcType == 1)
	if (heuristicType == 1)
		//return nearestNighborSum(s);
		return nearestNeighborSum(s);
	else
		return maxManhattanDistance(s);

}


bool is_fuel(State s){
	for(int i=0;i<4;i++){
		if(s.x == fuel_places[i][0] and s.y == fuel_places[i][1]){
			return false;
		}
		
	}
	return true;
}


bool isFuelStation(int x, int y) {
	for (int i =0 ; i<4 ; i++)
	{

		if ( x == fuel_places[i][0] &&  y == fuel_places[i][1] ){
			return true;
		} 
	}
	return false;
}

bool is_wall(int new_x , int new_y){
	for(int i=0;i<4;i++){
		if(new_x== wall_places[i][0] and new_y == wall_places[i][1]){
			return true;
		}
		
	}
	return false;

}

bool is_same_state(State s, State b)
{
	
	if ((s.x == b.x) && (s.y == b.y) && (s.fuel == b.fuel)) 
	{
		for(int i=0;i<4;i++){
			if (s.coins[i] != b.coins[i])
			{
				return false;	
			}
		}
	    return true;
	 }

    return false;

 }
    



State neighbor_genration(State s,int new_x,int new_y){
	State next_state = s;
	for(int i=0; i<4;i++){
		if((coin_places[i][0] == new_x) && (coin_places[i][1] == new_y)){
			
				next_state.coins[i]=true;
			
		}
	}
	return next_state;
}

bool is_Goal(State s)
{

	if (s.x != 1 || s.y != 1 ) return false;

	for (int i=0; i<4 ;i++)
	{
		if (!s.coins[i]) return false;	
	}
	return true;
}

bool isInExplored(vector<State> explored_set, State s){

	for(int i=0 ; i < explored_set.size(); i++ ) {
		if ( is_same_state(explored_set[i],s))
		{
			return true;
		}
	}

	return false;

}



void A_star(State initial_state, int  heuristicType,ofstream &out)
{
	vector<State> explored_set;
	priority_queue<State> pq;
	int expanded_nodes = 0;
    int frontier_size = 0;
   
	auto startTime = chrono::high_resolution_clock::now();
	int visited_count = 0;


    //initial_state = initial_state.steps + heuristic(initial_state, heuristicType);
	initial_state.f_score =initial_state.steps +heuristic(initial_state, heuristicType);
	pq.push(initial_state); 

	while(!pq.empty()){
		State current_state = pq.top();
		pq.pop();
		//visited_count++;

		if (isInExplored(explored_set, current_state)) {
			continue;
		}
		visited_count++;
		expanded_nodes++;
		printState(current_state, out);


		//if(maxManhattanDistance(current_state)==0){
			//cout<< "Goal"<<endl;
			//cout<<"Total steps:"<<current_state.steps<<endl;
			//break;

		//}

		if (is_Goal(current_state)) {
			auto endTime =chrono::high_resolution_clock::now();double time =chrono::duration<double, milli> (endTime - startTime).count();
			out<< "Goal"<<endl;
			/*out<<"Total steps:"<<current_state.steps<<endl;
			out<<"visited state : "<< visited_count<< endl;*/

 			out << "Cost g(n): "<< current_state.steps << endl;
          //out << "Heuristic h(n): "<< heuristic(current_state, heuristicType)<< endl;
        out << "f(n): "<< current_state.f_score << endl;
        out << "Expanded Nodes: "<< expanded_nodes << endl;
        out << "Visited States: "<< visited_count << endl;
        out << "Frontier : "<< frontier_size << endl;
        out << "Time: "<< time << " ms\n";
			break;

		} 
		//printState(current_state);



		explored_set.push_back(current_state);
		int dx[4]= {1,-1,0,0};
		int dy[4]={0,0,1,-1};
		for(int i=0;i<4;i++){
			int new_x , new_y;
			new_x = current_state.x + dx[i];
			new_y = current_state.y + dy[i];
			if(current_state.fuel > 0 && (new_x >= 1 and new_x <= 10) && (new_y >=1 and new_y <= 10) && !is_wall(new_x,new_y)){
				State next_state = current_state;
				next_state.x= new_x;
				next_state.y = new_y;
				next_state.steps++;
				next_state.fuel--;
				if(isFuelStation(next_state.x, next_state.y)){
					next_state.fuel = 20;
				}

				next_state = neighbor_genration(next_state,next_state.x,next_state.y);
				next_state.f_score = next_state.steps  + heuristic(next_state,heuristicType);
				if (!isInExplored(explored_set, next_state))
				{
					pq.push(next_state);
					frontier_size = pq.size();
				}
				


			}
		}
	}
}

void GreedySearch(State initial_state, 	int heuristicType, ofstream &out)
{
	vector<State> explored_set;
	priority_queue<State> pq;
	int visited_count = 0;


    //initial_state = initial_state.steps + heuristic(initial_state, heuristicType);
	initial_state.f_score =heuristic(initial_state, heuristicType);
	pq.push(initial_state); 

	while(!pq.empty()){
		State current_state = pq.top();
		pq.pop();
		//visited_count++;

		if (isInExplored(explored_set, current_state)) {
			continue;
		}
		visited_count++;
		printState(current_state, out);


		//if(maxManhattanDistance(current_state)==0){
			//cout<< "Goal"<<endl;
			//cout<<"Total steps:"<<current_state.steps<<endl;
			//break;

		//}

		if (is_Goal(current_state)) {
			out<< "Goal"<<endl;
			out<<"Total steps:"<<current_state.steps<<endl;
			out<<"visited state : "<< visited_count<< endl;
			break;

		} 
		//printState(current_state);



		explored_set.push_back(current_state);
		int dx[4]= {1,-1,0,0};
		int dy[4]={0,0,1,-1};
		for(int i=0;i<4;i++){
			int new_x , new_y;
			new_x = current_state.x + dx[i];
			new_y = current_state.y + dy[i];
			if(current_state.fuel > 0 && (new_x >= 1 and new_x <= 10) && (new_y >=1 and new_y <= 10) && !is_wall(new_x,new_y)){
				State next_state = current_state;
				next_state.x= new_x;
				next_state.y = new_y;
				next_state.steps++;
				next_state.fuel--;
				if(isFuelStation(next_state.x, next_state.y)){
					next_state.fuel = 20;
				}

				next_state = neighbor_genration(next_state,next_state.x,next_state.y);
				next_state.f_score = heuristic(next_state, heuristicType);
				if (!isInExplored(explored_set, next_state))
				{
					pq.push(next_state);
				}
				


			}
		}
	}

}

void printState(State s, ofstream &out){
	out <<"<" <<s.x << ","<< s.y <<","<<s.fuel<< ",";

	for (int i=0; i<4; i++)
	{out << (s.coins[i] ? "t" : "f");
		if(i != 3) out << ", ";
	}

	out << "> Steps: " << s.steps<< " f: " <<s.f_score << endl;
}




int main(){
	ofstream out("output.txt");
	vector<State> tests;

	//State s;
	//s.x=1;
	//s.y=1;
	//s.steps=0;
	//s.fuel=20;
	//for(int i=0 ; i<4 ; i++){
	//	s.coins[i]= false;
	//}



	//A_star(s);

	tests.push_back(createState(1,1,20));
	tests.push_back(createState(10,10,20));
	tests.push_back(createState(2,2,14));
	tests.push_back(createState(2,7,5));
	tests.push_back(createState(9,8,15));


	for (int i=0 ; i < tests.size(); i++){

		out << "--------------------"<< "Test state "<<i+1 << "------------------------"<<endl;
	  
		out<<"*****************************A* with h1***********************************"<<endl;
		//cout <<"A* with h1"<<endl;
		A_star(tests[i],1, out);

		out<<"*****************************A* with h2***********************************"<<endl;

		//cout <<"A* with h2"<<endl;
		A_star(tests[i],2, out);

		out<<"*****************************Greedy with h1***********************************"<<endl;
		//cout <<"Greedy with h1"<<endl;
		GreedySearch(tests[i],1, out);

		//cout <<"A* with h2"<<endl;
		out<<"*****************************Greedy with h2***********************************"<<endl;
		GreedySearch(tests[i],2, out);
	}
	out.close(); 
	return 0;
}