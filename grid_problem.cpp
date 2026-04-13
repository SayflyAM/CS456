#include "grid_problem.h"
bool isGoal(const State &current_state, const State &goal_state) {

    return current_state.agent_pos.row == goal_state.agent_pos.row &&
           current_state.agent_pos.col == goal_state.agent_pos.col &&
           current_state.collected_coins == goal_state.collected_coins;
}

vector<State> getSuccessors(const State &current_state) {

    vector<State> next_States;

    Direction directions[4] = {
        Direction::Up,
        Direction::Down,
        Direction::Left,
        Direction::Right
    };

    for(int i = 0; i < 4; i++) {

        if(current_state.fuel <= 0) continue; // لا يمكن التحرك إذا نفد fual

        State next = current_state; // نسخ الحالة الحالية لتعديلها بناءً على الحركة الجديدة

        if(directions[i] == Direction::Up)
            next.agent_pos.row--;

        else if(directions[i] == Direction::Down)
            next.agent_pos.row++;

        else if(directions[i] == Direction::Left)
            next.agent_pos.col--;

        else if(directions[i] == Direction::Right)
            next.agent_pos.col++;

         //grid size is 10x10 
        if(next.agent_pos.row < 1 || next.agent_pos.row > 10 ||
           next.agent_pos.col < 1 || next.agent_pos.col > 10)
            continue; // لمنع حالات من تجاوز حواف ال grid

        
        next.fuel--;//-1 للfuel بعد كل حركة
        
        // مزال ال coins لم يتم جمعها


        // example: محطة الوقود في (3,8)
        // عند وصول الى محطة وقود وهيا 3.8 يتم اعادة تعبئة ال fuel الى 20
        if(next.agent_pos.row == 3 && next.agent_pos.col == 8) {next.fuel = 20;}

        
        next_States.push_back(next);// إضافة الحالة الجديدة إلى قائمة الحالات التالية
    }

    return next_States;
}
