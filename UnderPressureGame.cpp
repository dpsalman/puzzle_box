#include "UnderPressureGame.h"

/* Public Methods */

void UnderPressureGame::init(byte analog_input_pin, SevenSegmentDisplay *ssd_ptr)
{
  ssd_display_ptr = ssd_ptr;
  analog_input = analog_input_pin;
  pinMode(analog_input, INPUT_PULLUP);
}

void UnderPressureGame::execute()
{
  int pressure_val = get_smooth_pressure_read();
  ssd_display_ptr->display_value(pressure_val);
  
  switch(pressure_value_mode) {
    case 0:
      if (pressure_val > 2000 && pressure_val < 3000 && millis() > last_pressure_achieved_time + 1000)
      {
        if (pressure_achieved_count % 2 != 0)
        {
          play_track(0);
        } else {
          play_track(3);
        }
        pressure_achieved_count += 1;
        last_pressure_achieved_time = millis();
      } else if (pressure_val > 3000) {
        play_track(4);
      }
      break;
    case 1:
      if (pressure_val > 4000 && pressure_val < 5000 && millis() > last_pressure_achieved_time + 1000)
      {
        if (pressure_achieved_count % 2 != 0)
        {
          play_track(1);
        } else {
          play_track(3);
        }
        pressure_achieved_count += 1;
        last_pressure_achieved_time = millis();
      } else if (pressure_val > 5000){
        play_track(4);
      }
      break;
    case 2:
      if (pressure_val > 6000 && pressure_val < 7000 && millis() > last_pressure_achieved_time + 1000)
      {
        if (pressure_achieved_count % 2 != 0)
        {
          play_track(2);
        } else {
          play_track(3);
        }
        pressure_achieved_count += 1;
        last_pressure_achieved_time = millis();
      } else if(pressure_val > 7000){
        play_track(4);
      }
      break;
    default:
      break;
  }

  if(pressure_achieved_count > 5)
  {
    pressure_achieved_count = 0;
    pressure_value_mode += 1;
  }
  if (pressure_value_mode > 2)
  {
    pressure_value_mode = 0;
  }
}

/* Private Methods */

int UnderPressureGame::get_smooth_pressure_read()
{
  uint16_t sensor_val = analogRead(analog_input);
  avg_val = (update_weight * sensor_val) + (prev_weight * avg_val);
  int out_val = (1024 - uint16_t(avg_val));
  out_val = map(out_val, 20, 1024, 0, 9999);
  return out_val;
}


UnderPressureGame;
