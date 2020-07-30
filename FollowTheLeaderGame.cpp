#include "FollowTheLeaderGame.h"

/* Public Methods */

void FollowTheLeaderGame::execute()
{
  switch (game_mode) 
  {
    case left_dependent:
      check_left_dependent_mode(*(inputs_ptr + 0), *(outputs_ptr + 0), 1);
      check_left_dependent_mode(*(inputs_ptr + 1), *(outputs_ptr + 5), 6);
      check_left_dependent_mode(*(inputs_ptr + 2), *(outputs_ptr + 10), 11);
      check_left_dependent_mode(*(inputs_ptr + 3), *(outputs_ptr + 15), 16);
      check_left_dependent_mode(*(inputs_ptr + 4), *(outputs_ptr + 1), 2);
      check_left_dependent_mode(*(inputs_ptr + 5), *(outputs_ptr + 6), 7);
      check_left_dependent_mode(*(inputs_ptr + 6), *(outputs_ptr + 11), 12);
      check_left_dependent_mode(*(inputs_ptr + 7), *(outputs_ptr + 16), 17);
      check_left_dependent_mode(*(inputs_ptr + 8), *(outputs_ptr + 2), 3);
      check_left_dependent_mode(*(inputs_ptr + 9), *(outputs_ptr + 7), 8);
      check_left_dependent_mode(*(inputs_ptr + 10), *(outputs_ptr + 12), 13);
      check_left_dependent_mode(*(inputs_ptr + 11), *(outputs_ptr + 17), 18);
      check_left_dependent_mode(*(inputs_ptr + 12), *(outputs_ptr + 3), 4);
      check_left_dependent_mode(*(inputs_ptr + 13), *(outputs_ptr + 8), 9);
      check_left_dependent_mode(*(inputs_ptr + 14), *(outputs_ptr + 13), 14);
      check_left_dependent_mode(*(inputs_ptr + 15), *(outputs_ptr + 18), 19);
      check_left_dependent_mode(*(inputs_ptr + 16), *(outputs_ptr + 4), 5);
      check_left_dependent_mode(*(inputs_ptr + 17), *(outputs_ptr + 9), 10);
      check_left_dependent_mode(*(inputs_ptr + 18), *(outputs_ptr + 14), 15);
      check_left_dependent_mode(*(inputs_ptr + 19), *(outputs_ptr + 19), 20);
      break;
    case right_dependent:
      check_right_dependent_mode(*(inputs_ptr + 0), *(outputs_ptr + 0), 1);
      check_right_dependent_mode(*(inputs_ptr + 1), *(outputs_ptr + 5), 6);
      check_right_dependent_mode(*(inputs_ptr + 2), *(outputs_ptr + 10), 11);
      check_right_dependent_mode(*(inputs_ptr + 3), *(outputs_ptr + 15), 16);
      check_right_dependent_mode(*(inputs_ptr + 4), *(outputs_ptr + 1), 2);
      check_right_dependent_mode(*(inputs_ptr + 5), *(outputs_ptr + 6), 7);
      check_right_dependent_mode(*(inputs_ptr + 6), *(outputs_ptr + 11), 12);
      check_right_dependent_mode(*(inputs_ptr + 7), *(outputs_ptr + 16), 17);
      check_right_dependent_mode(*(inputs_ptr + 8), *(outputs_ptr + 2), 3);
      check_right_dependent_mode(*(inputs_ptr + 9), *(outputs_ptr + 7), 8);
      check_right_dependent_mode(*(inputs_ptr + 10), *(outputs_ptr + 12), 13);
      check_right_dependent_mode(*(inputs_ptr + 11), *(outputs_ptr + 17), 18);
      check_right_dependent_mode(*(inputs_ptr + 12), *(outputs_ptr + 3), 4);
      check_right_dependent_mode(*(inputs_ptr + 13), *(outputs_ptr + 8), 9);
      check_right_dependent_mode(*(inputs_ptr + 14), *(outputs_ptr + 13), 14);
      check_right_dependent_mode(*(inputs_ptr + 15), *(outputs_ptr + 18), 19);
      check_right_dependent_mode(*(inputs_ptr + 16), *(outputs_ptr + 4), 5);
      check_right_dependent_mode(*(inputs_ptr + 17), *(outputs_ptr + 9), 10);
      check_right_dependent_mode(*(inputs_ptr + 18), *(outputs_ptr + 14), 15);
      check_right_dependent_mode(*(inputs_ptr + 19), *(outputs_ptr + 19), 20);
      break;
    default:
      break;  
  }
  if (current_step_index == MAX_STEPS)
  {
    current_step_index = 0;
    switch(game_mode)
    {
      case left_dependent:
        game_mode = right_dependent;
        break;
      case right_dependent:
        game_mode =  left_dependent;
      default:
        break;    
    }
  }
}       
    
/* Private Methods */
    
void FollowTheLeaderGame::check_left_dependent_mode(byte input_pin, byte output_pin, byte mapped_value)
{
  if (digitalRead(input_pin) == HIGH)
  {
    if (left_mode_sequence[current_step_index] == mapped_value)
    {
      digitalWrite(output_pin, HIGH);
      current_step_index++;
    } 
  } 
  else 
  {
    if (left_mode_sequence[current_step_index] == mapped_value)
    {
        pulse(output_pin);
    }
    else
    { 
      if (!check_completed(output_pin))
      {
        digitalWrite(output_pin, LOW);
      }
    }
  }  
}

void FollowTheLeaderGame::check_right_dependent_mode(byte input_pin, byte output_pin, byte mapped_value)
{
  if (digitalRead(input_pin) == LOW)
  {
    if (left_mode_sequence[current_step_index] == mapped_value)
    {
      digitalWrite(output_pin, HIGH);
      current_step_index++;
    } 
  } 
  else 
  {
    if (left_mode_sequence[current_step_index] == mapped_value)
    {
        pulse(output_pin);
    }
    else
    { 
      if (!check_completed(output_pin))
      {
        digitalWrite(output_pin, LOW);
      }
    }
  }  
}

void FollowTheLeaderGame::pulse(byte output_pin)
{
  if (millis() > last_pulse_time + 500)
  {
    if (pulse_counter % 2 != 0)
    {
        digitalWrite(output_pin, HIGH);
    } 
    else
    {
        digitalWrite(output_pin, LOW);
    }
    if (pulse_counter > 2)
    {
        pulse_counter = 0;
    }
    else
    {
        pulse_counter++;
        last_pulse_time = millis();
    }
  }
}

bool FollowTheLeaderGame::check_completed(byte output_pin)
{
  bool return_val = false;
  for (int i = 0; i < current_step_index; i++)
  {
    switch(game_mode)
    {
      case left_dependent:
        if (left_mode_sequence[current_step_index] == output_pin)
        {
          return_val = true;
        } 
        break;
      case right_dependent:
        if (right_mode_sequence[current_step_index] == output_pin)
        {
          return_val = true;
        } 
        break;
      default:
        break;
    }
  }
  return return_val;
}

FollowTheLeaderGame;
