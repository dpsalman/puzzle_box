/* Puzzle Box Game IO List 
 */

// Game Manager - Stats Input Pins
#define GM_SCORE_INPUT 14
#define GM_STRIK_INPUT 15

// Game Manager - Seven Segment Display Segment Pins
#define GM_OUTPUT_SSD_P 38
#define GM_OUTPUT_SSD_A 39
#define GM_OUTPUT_SSD_B 40
#define GM_OUTPUT_SSD_C 41
#define GM_OUTPUT_SSD_D 42
#define GM_OUTPUT_SSD_E 43
#define GM_OUTPUT_SSD_F 44
#define GM_OUTPUT_SSD_G 45

// Game Manager - Seven Segment Display Digit Pins
#define GM_OUTPUT_SSD_D1 46
#define GM_OUTPUT_SSD_D2 47
#define GM_OUTPUT_SSD_D3 48
#define GM_OUTPUT_SSD_D4 49

// Adafruit SoundFX Soundboard - Manual Reset Pin
#define AF_SFX_RST 20

// Simon Says Game - Button Input Pins
#define SSG_GAME_INPUT_1 A3
#define SSG_GAME_INPUT_2 A2
#define SSG_GAME_INPUT_3 A1
#define SSG_GAME_INPUT_4 A0

// Simon Says Game -  Output Pins
#define SSG_GAME_OUTPUT_1 10
#define SSG_GAME_OUTPUT_2 11
#define SSG_GAME_OUTPUT_3 12
#define SSG_GAME_OUTPUT_4 13

// Under Pressure Game - Analog Pullup Input
#define UPG_GAME_INPUT_1 A15

// Under Pressure Game - Seven Segment Display Segment Pins
#define UPG_GAME_OUTPUT_SSD_P 38
#define UPG_GAME_OUTPUT_SSD_A 39
#define UPG_GAME_OUTPUT_SSD_B 40
#define UPG_GAME_OUTPUT_SSD_C 41
#define UPG_GAME_OUTPUT_SSD_D 42
#define UPG_GAME_OUTPUT_SSD_E 43
#define UPG_GAME_OUTPUT_SSD_F 44
#define UPG_GAME_OUTPUT_SSD_G 45

// Under Pressure Game - Seven Segment Display Digit Pins
#define UPG_GAME_OUTPUT_SSD_D1 50
#define UPG_GAME_OUTPUT_SSD_D2 51
#define UPG_GAME_OUTPUT_SSD_D3 52
#define UPG_GAME_OUTPUT_SSD_D4 53

// Follow The Leader Game - Input Pins
#define FTLG_GAME_INPUT_1 A3
#define FTLG_GAME_INPUT_2 A2
#define FTLG_GAME_INPUT_3 A1
#define FTLG_GAME_INPUT_4 A0

// Follow The Leader Game - Output Pins
#define FTLG_GAME_OUTPUT_1 10
#define FTLG_GAME_OUTPUT_2 11
#define FTLG_GAME_OUTPUT_3 12
#define FTLG_GAME_OUTPUT_4 13

/* Adafruit SoundFX Soundboard Usage:
 */

#include "Adafruit_Soundboard.h"
Adafruit_Soundboard af_sfx = Adafruit_Soundboard(&Serial1, nullptr, AF_SFX_RST);

/* Game Manager Usage:
 */

// Seven Segemet Display Class Usage:
#include "SevenSegmentDisplay.h"
SevenSegmentDisplay gm_ssd_display = SevenSegmentDisplay();

// Seven Segement Display Setup:
byte gm_ssd_output[12] = { GM_OUTPUT_SSD_P, GM_OUTPUT_SSD_A, GM_OUTPUT_SSD_B, GM_OUTPUT_SSD_C, GM_OUTPUT_SSD_D, GM_OUTPUT_SSD_E, GM_OUTPUT_SSD_F, GM_OUTPUT_SSD_G, GM_OUTPUT_SSD_D1, GM_OUTPUT_SSD_D2, GM_OUTPUT_SSD_D3, GM_OUTPUT_SSD_D4 };
enum GMDisplayState { score, strike };
GMDisplayState gm_display_stat = score;

/* Game Class Usage: 
 * #include "Game.h"
 * Game game = Game();
 */
 
// Simon Says Game Class Usage:
#include "SimonSaysGame.h"
SimonSaysGame simon_says_game = SimonSaysGame();

// Simon Says Game Setup:
byte ssg_game_input[4] = { SSG_GAME_INPUT_1, SSG_GAME_INPUT_2, SSG_GAME_INPUT_3, SSG_GAME_INPUT_4 };
byte ssg_game_output[4] = { SSG_GAME_OUTPUT_1, SSG_GAME_OUTPUT_2, SSG_GAME_OUTPUT_3, SSG_GAME_OUTPUT_4 };

// Under Pressure Game Class Usage:
#include "UnderPressureGame.h"
UnderPressureGame under_pressure_game = UnderPressureGame();

// Under Pressure Game Setup:
byte upg_game_input = UPG_GAME_INPUT_1;
byte upg_game_ssd_output[12] = { UPG_GAME_OUTPUT_SSD_P, UPG_GAME_OUTPUT_SSD_A, UPG_GAME_OUTPUT_SSD_B, UPG_GAME_OUTPUT_SSD_C, UPG_GAME_OUTPUT_SSD_D, UPG_GAME_OUTPUT_SSD_E, UPG_GAME_OUTPUT_SSD_F, UPG_GAME_OUTPUT_SSD_G, UPG_GAME_OUTPUT_SSD_D1, UPG_GAME_OUTPUT_SSD_D2, UPG_GAME_OUTPUT_SSD_D3, UPG_GAME_OUTPUT_SSD_D4 };
SevenSegmentDisplay *upg_ssd_display_ptr = new SevenSegmentDisplay();

// Follow The Leader Game Class Usage:
#include "FollowTheLeaderGame.h"
FollowTheLeaderGame follow_the_leader_game = FollowTheLeaderGame();

byte ftlg_game_input[4] = { FTLG_GAME_INPUT_1, FTLG_GAME_INPUT_2, FTLG_GAME_INPUT_3, FTLG_GAME_INPUT_4 };
byte ftlg_game_output[4] = { FTLG_GAME_OUTPUT_1, FTLG_GAME_OUTPUT_2, FTLG_GAME_OUTPUT_3, FTLG_GAME_OUTPUT_4 };

void setup() 
{
  /* Serial Monitor Initialization:
   */
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for intial serial 1 port to initialize
  }
  Serial.println("Serial 0 Initialized!");

  /* Serial Controller Initializtion for SoundFX Soundboard:
   */
   
  Serial1.begin(9600);
  while (!Serial1) {
    ; // wait for intial serial 2 port to initialize
  }
  Serial.println("Serial 1 Initialized!");

  /* Game Manager Initialization:
   */

  pinMode(GM_SCORE_INPUT, INPUT);
  pinMode(GM_STRIK_INPUT, INPUT);
  gm_ssd_display.init(gm_ssd_output);
  
  /* Game Class Initialization:
   * game.init(game_input, sizeof(game_input)/sizeof(byte), game_output, sizeof(game_output)/sizeof(byte));
   */

  // Simon Says Game 
  simon_says_game.init(ssg_game_input, sizeof(ssg_game_input)/sizeof(byte), ssg_game_output, sizeof(ssg_game_output)/sizeof(byte));

  // Under Pressure Game
  upg_ssd_display_ptr->init(upg_game_ssd_output);
  under_pressure_game.init(upg_game_input, upg_ssd_display_ptr);  

  // Follow The Leader Game
  follow_the_leader_game.init(ftlg_game_input, sizeof(ftlg_game_input)/sizeof(byte), ftlg_game_output, sizeof(ftlg_game_output)/sizeof(byte));
} 
 
void loop()
{
  /* Game Execution:
   * game.execute();
   */

  // Simon Says Game
  simon_says_game.execute();

  // Under Pressure Game
  under_pressure_game.execute();

  // Follow The Leader Game
  follow_the_leader_game.execute();

  /* Game Manager:
   */
  
  int total_score = 0;
  int total_strikes = 0;
  total_score += simon_says_game.get_score() + under_pressure_game.get_score() + follow_the_leader_game.get_score();
  total_strikes += simon_says_game.get_strikes() + under_pressure_game.get_strikes() + follow_the_leader_game.get_strikes();
 
  if (digitalRead(GM_SCORE_INPUT) == LOW)
  {
    gm_display_stat = score;
  }
  else if (digitalRead(GM_STRIK_INPUT) == LOW)
  {
    gm_display_stat = strike;
  }

  switch(gm_display_stat)
  {
    case score:
      gm_ssd_display.display_value(total_score);
      break;
    case strike:
      gm_ssd_display.display_value(total_strikes);
      break;
    default:
      break;
  }
}
