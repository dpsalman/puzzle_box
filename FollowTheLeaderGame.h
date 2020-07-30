/*
*/

#ifndef _FollowLeaderGame_h
#define _FollowLeaderGame_h

#include "Game.h"

enum FollowModes {
    right_dependent,
    left_dependent
};

class FollowTheLeaderGame : public Game
{
  private:
    const static int MAX_STEPS = 4;
    const byte left_mode_sequence[MAX_STEPS] = { 1, 2, 3, 4 };
    const byte right_mode_sequence[MAX_STEPS] = { 4, 3, 2, 1 };
    FollowModes game_mode;
    int current_step_index;
    int last_pulse_time;
    int pulse_counter;
    void check_left_dependent_mode(byte input_pin, byte output_pin, byte mapped_value);
    void check_right_dependent_mode(byte input_pin, byte output_pin, byte mapped_value);
    void pulse(byte output_pin);
    bool check_completed(byte output_pin);
  public:
    FollowTheLeaderGame() : Game() {
        game_mode = right_dependent;
        current_step_index, last_pulse_time, pulse_counter = 0;
    };
    void execute();
};

extern FollowTheLeaderGame;

#endif
