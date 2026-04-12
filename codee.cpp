#include <iostream>
using namespace std;
const int GRID_SIZE = 10;
const int MAX_FUEL = 20;
// ميدئيا موقع ثابت  يمكن تعديله ان يكون عشوائي
const pair<int,int> FUEL_STATION = {4,9};
//state
class State {
public:
    int x, y, fuel;
    bool c1, c2, c3, c4;

    State(int x=0,int y=0,int fuel=0,
          bool c1=false,bool c2=false,bool c3=false,bool c4=false) {
        this->x=x;
        this->y=y;
        this->fuel=fuel;
        this->c1=c1;
        this->c2=c2;
        this->c3=c3;
        this->c4=c4;
    }

    string toString(){
        return to_string(x)+","+to_string(y)+","+to_string(fuel)+
               to_string(c1)+to_string(c2)+to_string(c3)+to_string(c4);
    }

    void print()  {
        cout<<"("<<x<<","<<y<<", f:"<<fuel<<", ["
            <<(c1?"t":"f")<<","<<(c2?"t":"f")<<","
            <<(c3?"t":"f")<<","<<(c4?"t":"f")<<"])";
    }
};

//node
class node {
public:
    State state;
    node* parent;
    string action;

    node(State state, node* parent, string action) {
        state = state;
        parent = parent;
        action = action;
    }
};

// environment
class environment {
private:
    pair<int,int> coins[4];
    bool walls[11][11];

public:
    environment() {
        for(int i=1;i<=10;i++)
            for(int j=1;j<=10;j++)
                walls[i][j]=false;
    }

    void setCoins(pair<int,int> p1,pair<int,int> p2,pair<int,int> p3,pair<int,int> p4) {
        coins[0]=p1;
        coins[1]=p2;
        coins[2]=p3;
        coins[3]=p4;
    }  

};

int main() {

    environment env;

    //   عملات ثابتة
    env.setCoins({2,3},{6,2},{5,7},{8,8});

    // حالة ابتدائية
    State start(9,9,15,false,false,false,false);

    cout<<"Start State: "; start.print(); cout<<endl;

    return 0;
}