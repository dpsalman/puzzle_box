/*
*/

#ifndef _UnderPressureGame_h
#define _UnderPressureGame_h

#include "Game.h"
#include "SevenSegmentDisplay.h"

class UnderPressureGame : public Game 
{
  private:
    byte analog_input;
    float avg_val;
    float update_weight;
    float prev_weight;
    int last_pressure_achieved_time;
    int pressure_value_mode;
    int pressure_achieved_count;
    SevenSegmentDisplay *ssd_display_ptr;
    int get_smooth_pressure_read();
    int nth_digit(int number, int pos);
    void display_pressure_value(int value);
  public:
    UnderPressureGame() : Game() { 
      avg_val = 1023; 
      update_weight = 0.001; 
      prev_weight = 1.0 - update_weight;
      last_pressure_achieved_time, pressure_value_mode, pressure_achieved_count = 0; 
    };
    void init(byte analog_input_pin, SevenSegmentDisplay *ssd_ptr);
    void execute();
};

extern UnderPressureGame;

#endif
