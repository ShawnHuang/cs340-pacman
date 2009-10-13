#include "game.h"


Game::Game()
{
}



void Game::setAndAddStates()
{
    State menuState("MENU");
    State initState("INITPLAY");         //creating INIT state
    State playState("PLAY");            // creating play state
    State outroState("OUTRO");
    State quitState("QUIT");
    State insructState("INST");

    //Menu State and the events that can occur
    menuState.addEventAndNextState("click_start", "INITPLAY");
    menuState.addEventAndNextState("click_quit", "QUIT");
    menuState.addEventAndNextState("click_instr", "INST");
    menuState.setProperty("display");

    //Initialize game and then move state to begin the game
    initState.addEventAndNextState("init_timeout", "PLAY");
    initState.setProperty("steady");

    //Actual play begins here until game has ended
    playState.addEventAndNextState("begin_game","PLAY");
    playState.setProperty("gameplay");
    playState.addEventAndNextState("game_over", "OUTRO");
    playState.addEventAndNextState("click_quit", "MENU");

    outroState.addEventAndNextState("display_scores", "SCORES");
    outroState.addEventAndNextState("click_okay", "MENU");

}

void Game::update()
{

}

















