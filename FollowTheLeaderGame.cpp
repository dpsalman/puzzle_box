/*
#include "FollowTheLeaderGame.h"


void FollowTheLeaderGame::execute()
{
    switch(game_mode)
    {
        case right_dependent:
            play_right_dependent_mode();
            break;
        case left_dependent:
            play_left_dependent_mode();
            break;
        case simultaneous:
            play_simultaneous_mode();
            break;
    }

    if (current_step_index <= MAX_STEPS)
    {
        current_step_index++;
    } 
    else 
    {
        switch(game_mode)
        {
            case right_dependent:
                game_mode = left_dependent;
                break;
            case left_dependent:
                game_mode = right_dependent;
                break;
            case simultaneous:
                game_mode = simultaneous;
                break;
        }
        current_step_index = 0;
    }
}


void play_right_dependent_mode()
    
void play_left_dependent_mode()
    
void play_simultaneous_mode()

FollowTheLeaderGame;
*/