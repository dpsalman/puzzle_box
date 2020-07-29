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
    const static int MAX_STEPS = 20;
    const byte left_mode_sequence[MAX_STEPS] = { 5, 10, 15, 20, 4, 9, 14, 19, 3, 8, 13, 18, 2, 7, 12, 17, 1, 6, 11, 16 };
    const byte right_mode_sequence[MAX_STEPS] = { 1, 6, 11, 16, 2, 7, 12, 17, 3, 8, 13, 18, 4, 9, 14, 19, 5, 10, 15, 20 };
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
