#include "grid_problem.h"



Position coins[4];
Position fuel_place;

//تحقق مما إذا كانت الحالة الحالية هي حالة الهدف أم لا
//goal state is defined as the agent being at position (1,1) and having collected all coins (C1 to C4  == 15 in binary)
bool isGoal(const State &current_state, const State &goal_state) {

    return current_state.agent_pos.row == goal_state.agent_pos.row &&
           current_state.agent_pos.col == goal_state.agent_pos.col &&
          // current_state.collected_coins == goal_state.collected_coins;
          current_state.c1 && current_state.c2 &&
          current_state.c3 && current_state.c4;
}

//الحصول على الحالات التالية الممكنة من الحالة الحالية بناءً على الحركات الأربعة (Up, Down, Left, Right)
vector<State> getSuccessors(const State &current_state)
 {  
    vector<State> next_States;// لتخزين الحالات التالية الممكنة
    Direction directions[4] = {
        Direction::Up,
        Direction::Down,
        Direction::Left,
        Direction::Right
    };

    for(int i = 0; i < 4; i++) 
    {

        if(current_state.fuel <= 0) //
        continue; // إذا نفد الوقود، لا يمكننا التحرك

        State next = current_state; // نبدأ من الحالة الحالية ونقوم بتعديلها بناءً على الحركة

        if(directions[i] == Direction::Up) 
            next.agent_pos.row--;// الحركة للأعلى تقلل من رقم الصف

        else if(directions[i] == Direction::Down)
            next.agent_pos.row++;// الحركة للأسفل تزيد من رقم الصف

        else if(directions[i] == Direction::Left)
            next.agent_pos.col--;// الحركة لليسار تقلل من رقم العمود

        else if(directions[i] == Direction::Right)
            next.agent_pos.col++;// الحركة لليمين تزيد من رقم العمود


         //grid size is 10x10 
         // إذا كانت الحركة تؤدي إلى الخروج من الشبكة، نتجاهلها
        if(next.agent_pos.row < 1 || next.agent_pos.row > 10 || next.agent_pos.col < 1 || next.agent_pos.col > 10)
            continue; 

        
        next.fuel--;// كل حركة تستهلك وقود بقيمة 1 
        
       
     // التحقق من جمع العملات
     for(int c = 0; c < 4; c++) 
     {
     if(next.agent_pos.row == coins[c].row && next.agent_pos.col == coins[c].col) 
     {
      if(c == 0) next.c1 = true;
      if(c == 1) next.c2 = true;
      if(c == 2) next.c3 = true;
      if(c == 3) next.c4 = true;
     }
  }

     // التحقق مما إذا كان الوكيل قد جمع عملة في الموقع الجديد، إذا كان كذلك، نحدث collected_coins باستخدام
    
     for(int c = 0; c < 4; c++) 
     {
       if(next.agent_pos.row == coins[c].row && next.agent_pos.col == coins[c].col) 
       {  if(next.agent_pos.row == 2 && next.agent_pos.col == 3)  next.c1 = true;
          if(next.agent_pos.row == 6 && next.agent_pos.col == 2)  next.c2 = true;
          if(next.agent_pos.row == 5 && next.agent_pos.col == 7)  next.c3 = true;
          if(next.agent_pos.row == 8 && next.agent_pos.col == 8)  next.c4 = true;
          // next.collected_coins |= (1 << c);
         }
     }
  
       if(next.agent_pos.row == fuel_place.row && next.agent_pos.col == fuel_place.col)
         {  next.fuel = 20;} //يتخقق مما إذا كان الوكيل قد وصل إلى محطة الوقود، إذا كان كذلك، يتم إعادة تعبئة الوقود
          /* يعني أي مكان تم تحديده في fuel_place
              هو اللي يعبي الوقود
            */ 
          next_States.push_back(next);// إضافة الحالة الجديدة إلى قائمة الحالات التالية
  }

 return next_States;
}
