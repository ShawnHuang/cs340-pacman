#ifndef GAME_H
#define GAME_H
#include "state.h"
#include "fsm.h"



class Game : public FSM
{
private:
    FSM gameFSM;
    void setAndAddStates();

public:
    Game();
    void update();

};




#endif // GAME_H
