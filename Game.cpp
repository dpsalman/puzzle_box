#include "Game.h"

/* Public Methods */

Game::Game()
{
  inputs_size, outputs_size, score, strikes = 0;
  complete = false;
  id = _next_id;
  _next_id++;
}

Game::~Game()
{
  delete [] inputs_ptr;
  delete [] outputs_ptr;
}

void Game::init(byte input_pins[], int input_pin_size, byte output_pins[], int output_pin_size)
{
  // Use pointer arithmetic to find size of ins and outs
  inputs_size = input_pin_size;
  outputs_size = output_pin_size;

  // Initialize IO
  for (int i = 0; i < inputs_size; i++)
  {
    pinMode(input_pins[i], INPUT);
  }

  for (int o = 0; o < outputs_size; o++)
  {
    pinMode(output_pins[o], OUTPUT);
  }

  // Store IO in Class memeber property
  inputs_ptr = input_pins;
  outputs_ptr = output_pins;
}

void Game::execute()
{
  // index pointer
  byte *input_index_ptr = inputs_ptr;
  
  // Print which input has been activated in logger
  for (int i = 0; i < inputs_size; i++)
  {
    if (digitalRead(*(input_index_ptr)) == LOW)
    {
      digitalWrite(*(outputs_ptr + i), HIGH);
    }
    else
    {
      digitalWrite(*(outputs_ptr + i), LOW);
    }
    input_index_ptr++;
  }
}

bool Game::is_completed()
{
  return complete;
}

int Game::get_id()
{
  return id;
}

int Game::get_score()
{
  return score;
}

int Game::get_strikes()
{
  return strikes;
}

/* Protected Methods */

void Game::set_completed(bool new_complete)
{
  complete = new_complete;
}

void Game::set_id(int new_id)
{
  id = new_id;
}

void Game::set_score(int new_score)
{
  score = new_score;
}

void Game::set_strikes(int new_strikes)
{
  strikes = new_strikes;
}

void Game::play_track(int track_id)
{
  Serial1.print('#');
  Serial1.println(track_id);
}

int Game::_next_id = 1;

Game;
