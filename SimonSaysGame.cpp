#include "SimonSaysGame.h"

/* Public Methods */

void SimonSaysGame::execute()
{ 
  if (level <= MAX_LEVEL)
  {
    if (new_game)
    {
      generate_sequence();
    }
    if (show_sequence)
    {
      play_sequence();
    }
    if (wrong_flag)
    {
      wrong_sequence();
    }
    if (current_sequence <= level)
    {
      get_player_sequence();
    }
    if (current_sequence > level)
    {
      right_sequence();
    }
  }
  else
  {
    set_completed(true);
    activate_leds();
  }
}

/* Private Methods */

void SimonSaysGame::generate_sequence()
{
  /* Conditon for generate_sequence requires new_game boolean to be true. */
  
  // Collect all possible outputs to randomly select
  int possible_outputs[outputs_size];
  for (int i = 0; i < outputs_size; i++)
  {
    possible_outputs[i] = *(outputs_ptr + i);
  }
  
  // Generate random selection and store generated sequence
  randomSeed(millis());
  for (int i = 0; i < MAX_LEVEL; i++)
  {
    int random_choice = random(0, outputs_size);
    generated_sequence[i] = possible_outputs[random_choice] ;
  }

  // Reset conditions and variables
  new_game = false;
}

void SimonSaysGame::play_sequence()
{
  /* Conditon for play_sequence requires show_sequence boolean to be true. */
  
  // Play sequence non-blocking
  if (play_sequence_level < level && millis() > last_played_sequence_time + velocity * 0.5)
  {
    if (play_sequence_counter % 2 != 0)
    {
      digitalWrite(generated_sequence[play_sequence_level], HIGH);
    }
    else 
    {
      digitalWrite(generated_sequence[play_sequence_level], LOW);
    }
    if (play_sequence_counter > 1)
    {
      play_sequence_level += 1;
      play_sequence_counter = 0;
    } 
    else
    {
      play_sequence_counter += 1;    
      last_played_sequence_time = millis();
    }
  }
  
  // Reset condition and variables
  if (play_sequence_level == level)
  {
    play_sequence_level = 0;
    show_sequence = false;
  }
}

void SimonSaysGame::get_player_sequence()
{
  // Input reader loop
  for (int i = 0; i < inputs_size; i++)
  {
    if (digitalRead(*(inputs_ptr + i)) == LOW)
    {
      input_recieved = true;
      player_sequence[current_sequence - 1] = *(outputs_ptr + i);
    }
  }
  
  // Input debounce time & feedback
  if (input_recieved && millis() > last_inputed_debounce_time + 250)
  {
    if (input_debounce_counter % 2 != 0)
    {
      digitalWrite(player_sequence[current_sequence - 1], HIGH);
    }
    else
    {
      digitalWrite(player_sequence[current_sequence - 1], LOW);
    }
    if (input_debounce_counter > 1)
    {
      input_recieved = false;
      input_debounce_counter = 0;
      if (generated_sequence[current_sequence - 1] == player_sequence[current_sequence - 1])
      {
        current_sequence += 1;
      }
      else 
      {
        wrong_flag = true;
      }
    } 
    else
    {
      input_debounce_counter += 1;
      last_inputed_debounce_time = millis();
    }
  }
}

void SimonSaysGame::right_sequence()
{
  if (millis() > last_correct_response_time + (correct_response_counter % 2 != 0 ? 500 : 250))
  {
    if (correct_response_counter % 2 != 0)
    {
      activate_leds();
    }
    else
    {
      reset_leds();
    }
    if (correct_response_counter > 1)
    {
      correct_response_counter = 0;
      wrong_flag = false;
      input_recieved = false;
      current_sequence = 1;
      show_sequence = true;
      velocity -= 75;
      level += 1;
    
      int new_score = get_score() + 10;
      set_score(new_score);
    }
    else
    {      
      correct_response_counter += 1;
      last_correct_response_time = millis();
    }
  }
}

void SimonSaysGame::wrong_sequence()
{
  if (millis() > last_incorrect_response_time + 250)
  {
    if (incorrect_response_counter % 2 != 0)
    {
      activate_leds();
    }
    else
    {
      reset_leds();
    }
    if (incorrect_response_counter > 5)
    {
      incorrect_response_counter = 0;
      wrong_flag = false;
      input_recieved = false;
      level = 1;
      velocity = 1000;
      current_sequence = 1;
      new_game = true;
      show_sequence = true;
    
      int new_score = get_score() - 5;
      int new_strikes = get_strikes() + 1;
      if (new_score < 0)
      {
        new_score = 0;
      }
      set_score(new_score);
      set_strikes(new_strikes);
    }
    else
    {
      incorrect_response_counter += 1;
      last_incorrect_response_time = millis();   
    }
  }
}

void SimonSaysGame::activate_leds()
{
  for (int i = 0; i < outputs_size; i++)
  {
    digitalWrite(*(outputs_ptr + i) , HIGH);
  }
}

void SimonSaysGame::reset_leds()
{
  for (int i = 0; i < outputs_size; i++)
  {
    digitalWrite(*(outputs_ptr + i), LOW);
  }
}

SimonSaysGame;
