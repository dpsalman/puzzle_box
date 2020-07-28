/*
 * Class used to interface with quadruple digit displays.
 * Supports both common annode and common cathode configuration.
 * 
  Schematic/Datasheet
  
  pin 11    - A 
  pin 7     - B
  pin 4     - C
  pin 2     - D
  pin 1     - E
  pin 10    - F
  pin 5     - G
  pin 12    - first digit
  pin 9     - second digit 
  pin 8     - third digit
  pin 6     - fourth digit
  pin 3     - decimal
  
  12 11 10 9 8 7
  |  |  |  | | |
      A
       ---
    F |   | B
      | G |
       ---
    E |   | C
      |   |
       ---  . dec
      D
  | | | | | |
  1 2 3 4 5 6

 */

#ifndef _SevenSegmentDisplay_h
#define _SevenSegmentDisplay_h

#include "Arduino.h"

class SevenSegmentDisplay
{
  private:
    bool common_cathode;
    byte digit_pinouts[4];
    byte segment_pinouts[8];
    int nth_digit(int number, int pos);
    void zero();
    void one();
    void two();
    void three();
    void four();
    void five();
    void six();
    void seven();
    void eight();
    void nine();
  public:
    SevenSegmentDisplay(bool common_cathode_param = false);
    void init(byte pin_outs[12]);
    void display_value(int value);
    void pick_digit(int pos);
    void pick_number(int num);
    void reset_digits();
    void reset_segments();
    void reset();
};

extern SevenSegmentDisplay;

#endif
