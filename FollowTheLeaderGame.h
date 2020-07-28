/*

#ifndef _FollowLeaderGame_h
#define _FollowLeaderGame_h

#include "Arduino.h"

enum FollowModes {
    right_depenedent,
    left_dependent,
    simultaneous
}

class FollowTheLeaderGame
{
  private:
    const static int MAX_STEPS = 4;
    const byte right_mode_sequence[MAX_STEPS] = { 4, 3, 2, 1 };
    const byte left_mode_sequence[MAX_STEPS] = { 1, 2, 3, 4 };
    conts byte simultaneous_mode_sequence[2][MAX_STEPS] = { { 4, 3, 2, 1 }, { 1, 2, 3, 4 } };
    FollowModes game_mode;
    int current_step_index;
    void play_right_dependent_mode();
    void play_left_dependent_mode();
    void play_simultaneous_mode();   
  public:
    FollowTheLeaderGame() : Game() {
        game_mode = right_depenedent;
        current_step_index = 0;
    };
    void execute();
};

extern FollowTheLeaderGame;

#endif
*/