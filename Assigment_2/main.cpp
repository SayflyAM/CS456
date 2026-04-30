class State{
	int x,y;
	int fuel;
	bool coins[4];



};



int coin_places[4][2] ={
	{1,4} 
	{5,7}
	{4,9}
	{6,5}

};



int maxManhattanDistance(&State s){
	int distance_larg =0;
	for(int i=0 ; i<4;i++){

		if(s.coins[i] ==false){
			int dist = abs(s.x -coin_places[i][0]) + abs(s.y - coin_places[i][1]);
		if(dist > distance_larg){
			distance_larg = dist;
		}	
		}
	}
	return distance_larg;
}