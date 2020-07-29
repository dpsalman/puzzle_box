/*
 * This sketch is a simple version of the famous Simon Says game. You can use it and improved it adding
 * levels and everything you want to increase the diffuculty! There are n buttons connected to any 
 * sequentual digital pinouts. The buttons from A0 to A3 are used to insert the right sequence.
 *
 * When a wrong sequence is inserted all the leds will blink for three time very fast otherwhise the
 * inserted sequence is correct.

Hardware needed:

5x pushbuttons
1x Blue led
1x Yellow led
1x Red led
1x Green Led
4x 1k resistors
4x 10k resisors
10x jumpers
*/

#ifndef _SimonSaysGame_h
#define _SimonSaysGame_h

#include "Game.h"

class SimonSaysGame : public Game 
{
  private:
    const static int MAX_LEVEL = 4;
    byte generated_sequence[MAX_LEVEL];
    byte player_sequence[MAX_LEVEL];
    bool new_game;
    bool show_sequence;
    bool input_recieved;
    bool wrong_flag;
    int current_sequence;
    int level;
    int velocity;
    int last_played_sequence_time;
    int play_sequence_counter;
    int play_sequence_level;
    int last_inputed_debounce_time;
    int input_debounce_counter;
    int last_correct_response_time;
    int correct_response_counter;
    int last_incorrect_response_time;
    int incorrect_response_counter;
    void generate_sequence();
    void play_sequence();
    void get_player_sequence();
    void right_sequence();
    void wrong_sequence();
    void activate_leds();
    void reset_leds();
  public:
    SimonSaysGame() : Game() {
      last_played_sequence_time, play_sequence_counter, play_sequence_level,
      last_correct_response_time, correct_response_counter,
      last_incorrect_response_time, incorrect_response_counter, 
      last_inputed_debounce_time, input_debounce_counter = 0;
      new_game, show_sequence = true; 
      input_recieved, wrong_flag = false;
      current_sequence, level = 1; 
      velocity = 1000; 
    };
    void execute();
};

extern SimonSaysGame;

#endif
