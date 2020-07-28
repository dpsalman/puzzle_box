/*
 * Base class used for storing the different metrics of a standard game. 
 * All games will inherit the properties of this class to be later used to 
 * aggregate these metrics to the GameManager Class.
 * 
 * Single Layer Heirarchy
 * 
 *                                         Game 
 *                                          |
 *        ----------------------------------------------------------------
 *        |                |                |                |           |
 *  UnderPressureGame SimonSaysGame FollowTheLeaderGame PushPullGame DialItInGame
 */

#ifndef _Game_h
#define _Game_h

#include "Arduino.h"

class Game
{
  protected:
    bool complete;
    byte *inputs_ptr;
    byte *outputs_ptr;
    int inputs_size;
    int outputs_size;
    int id;
    int score;
    int strikes;
    void set_completed(bool new_complete); 
    void set_id(int new_id);
    void set_score(int new_score);
    void set_strikes(int new_strikes);
    void play_track(int track_id);
  public:
    Game();
    ~Game();
    bool is_completed();
    int get_id();
    int get_score();
    int get_strikes();
    virtual void init(byte input_pins[], int input_pin_size, byte output_pins[], int output_pin_size);
    virtual void execute();
    static int _next_id;
};

extern Game;

#endif
