class State{
	int x,y;
	int fuel;
	bool coins[4];
	int stpes;



};

enum dirction{
	up;
	down;
	left;
	right;
}



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

}

int wall_places[4][2]{

	{2,3},
	{3,5},
	{9,7},
	{1,5},

}



int maxManhattanDistance(State s){
	int distance_larg =0;
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
	return distance_larg;
}

int minNigbour(State s){

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
		int distance_short=100000;


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
		coin_to_collect--;
		

	}

	
	return total_distance;
}


bool is_fuel(State s){
	for(i=0;i<4;i++){
		if(s.x == fuel_places[i][0] and s.y == fuel_places[i][1]){
			return false;
		}
		
	}
	return true;
}
bool is_wall(State s){
	for(i=0;i<4;i++){
		if(s.x == wall_places[i][0] and s.y == wall_places[i][1]){
			return true;
		}
		
	}
	return false;

}

bool is_same_state(State s, State b){
	
	if((s.x == b.x)&& (s.y == b.y){
		for(int i=0;i<4;i++){
			if(s.coins[i]!=b.coins[i]){
				return false;	
			}
		}
	    return true;

    return false;
    }
}


State neighbor_genration(State s,int new_x,int new_y){
	State next_state = s;
	for(int i=0; i<4;i++){
		if(coin_places[i][0]==new_x)&&(coin_places[i][1]==new_y){
			
				next_state.coins[i]=true;
			
		}
	}
	return next_state;
}




int main(){
	State s;


	int f = s.stpes + maxManhattanDistance(s);

	if(s.fuel > 0 && (new_x > =1 and new_x <= 10) && (new_y > =1 and new_y <= 10) && !is_wall )



	if(!is_fuel(s) and !is_wall(s))


}