#include "SevenSegmentDisplay.h"

/* Public Method */

SevenSegmentDisplay::SevenSegmentDisplay(bool common_cathode_param)
{
  // Sets digital states
  common_cathode = common_cathode_param;
}

void SevenSegmentDisplay::init(byte pin_outs[12])
{
  for (int i = 0; i < 12; i++) {
    pinMode(pin_outs[i], OUTPUT);
  };
  // Order of . A B C D E F G segment pinouts
  segment_pinouts[0] = pin_outs[0];
  segment_pinouts[1] = pin_outs[1];
  segment_pinouts[2] = pin_outs[2];
  segment_pinouts[3] = pin_outs[3];
  segment_pinouts[4] = pin_outs[4];
  segment_pinouts[5] = pin_outs[5];
  segment_pinouts[6] = pin_outs[6];
  segment_pinouts[7] = pin_outs[7];
  // Order of 1st 2nd 3rd 4th digit pinouts
  digit_pinouts[0] = pin_outs[8];
  digit_pinouts[1] = pin_outs[9];
  digit_pinouts[2] = pin_outs[10];
  digit_pinouts[3] = pin_outs[11];
}

void SevenSegmentDisplay::display_value(int value)
{
  reset_segments();
  pick_digit(1);
  pick_number(nth_digit(value,4));
  delayMicroseconds(50);
  
  reset_segments();
  pick_digit(2);
  pick_number(nth_digit(value,3));
  delayMicroseconds(50);

  reset_segments();
  pick_digit(3);
  pick_number(nth_digit(value,2));
  delayMicroseconds(50);

  reset_segments();
  pick_digit(4);
  pick_number(nth_digit(value,1));
  delayMicroseconds(50);

  reset_digits();
}

void SevenSegmentDisplay::pick_digit(int postion) 
{
  reset_digits();
  switch (postion) {
    case 1:
      digitalWrite(digit_pinouts[0], common_cathode ? HIGH : LOW);
      break;
    case 2:
      digitalWrite(digit_pinouts[1], common_cathode ? HIGH : LOW);
      break;
    case 3:
      digitalWrite(digit_pinouts[2], common_cathode ? HIGH : LOW);
      break;
    default:
      digitalWrite(digit_pinouts[3], common_cathode ? HIGH : LOW);
      break;
    };
}

void SevenSegmentDisplay::pick_number(int number) 
{
  switch (number) {
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    default:
      zero();
      break;
  };
}

void SevenSegmentDisplay::reset_digits()
{
  for (int i = 0; i < 4; i++) {
    digitalWrite(digit_pinouts[i], common_cathode ? LOW : HIGH);
  };
}

void SevenSegmentDisplay::reset_segments()
{
  for (int i = 0; i < 8; i++) {
    digitalWrite(segment_pinouts[i], common_cathode ? HIGH : LOW);
  };
}

void SevenSegmentDisplay::reset()
{
  for (int i = 1; i < 5; i++) {
    pick_digit(i);
    reset_segments();
  }
}

/* Private Methods */

int SevenSegmentDisplay::nth_digit(int number, int pos) 
{ 
    // Skip N-1 Digits in Base B 
    for (int i = 1; i < pos; i++) 
        number = number / 10; 
  
    // Nth Digit from right in Base B 
    return number % 10; 
} 

void SevenSegmentDisplay::zero()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[6], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[7], common_cathode ? HIGH : LOW);
}

void SevenSegmentDisplay::one()
{
  digitalWrite(segment_pinouts[1], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[5], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[6], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[7], common_cathode ? HIGH : LOW);
}

void SevenSegmentDisplay::two()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[6], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

void SevenSegmentDisplay::three()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[6], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

void SevenSegmentDisplay::four()
{
  digitalWrite(segment_pinouts[1], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[5], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[6], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

void SevenSegmentDisplay::five()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[6], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

void SevenSegmentDisplay::six()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[6], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

void SevenSegmentDisplay::seven()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[5], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[6], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[7], common_cathode ? HIGH : LOW);
}

void SevenSegmentDisplay::eight()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[6], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

void SevenSegmentDisplay::nine()
{
  digitalWrite(segment_pinouts[1], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[2], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[3], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[4], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[5], common_cathode ? HIGH : LOW);
  digitalWrite(segment_pinouts[6], common_cathode ? LOW : HIGH);
  digitalWrite(segment_pinouts[7], common_cathode ? LOW : HIGH);
}

SevenSegmentDisplay;
