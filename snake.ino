// This #include statement was automatically added by the Particle IDE.
#include "SparkIntervalTimer/SparkIntervalTimer.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"

// This #include statement was automatically added by the Particle IDE.
#include "RGBmatrixPanel/RGBmatrixPanel.h"

// This #include statement was automatically added by the Particle IDE.
#include "snake.h"

#include "math.h"

#define PI  3.14159265


/** Define RGB matrix panel GPIO pins **/
#if defined (STM32F10X_MD)	//Core
	#define CLK D6
	#define OE  D7
	#define LAT A4
	#define A   A0
	#define B   A1
	#define C   A2
	#define D	A3		// Only used for 32x32 panels
#endif

#if defined (STM32F2XX)	//Photon
	#define CLK D6
	#define OE  D7
	#define LAT A4
	#define A   A0
	#define B   A1
	#define C   A2
	#define D	A3		// Only used for 32x32 panels
#endif
/****************************************/


RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);



int length = 3;
bool update = true;
int Delay = 0;
int speed = game_speed;


mysnake* temp;
mysnake snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4]; //create snake matrix
mysnake* snakehead; //pointer to head of the snake
food apple;
food* applepointer;


Serpent Snake;

void setup() {
    snakehead = &snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3];
    apple.row = 3;
    apple.column = 3;
    applepointer = &apple;
    Snake.snake_intialization(snake); //initialize snake location and direction
}

void loop() {
    if (!update){
        Delay++;
        if (Delay == 10) {
            length = 0;
            Snake.clear(snake); //remove snake directions and locations
            //Snake.print1(patt1, patt2, patt3, patt4); //print game
        } 
        else if (Delay == 20) {
            //Snake.print2(patt1, patt2, patt3, patt4); //print over
        } 
        else if (Delay == 30) {
            Snake.snake_intialization(snake); //initialize snake location and direction
            Snake.renew_apple(applepointer, snakehead); //change apple location
            while (apple.row == snakehead -> srow) { //keep apple and snake at different rows
                Snake.renew_apple(applepointer, snakehead);
            }
            length = 3;
            Delay = 0;
            update = true; //start new game
        }
    }
    
    if (update){
        Snake.clear_matrix();
        Snake.create_border();
        Snake.light_bit(applepointer -> row, applepointer -> column);
        Snake.update_body(snake, length);
        Snake.show_body(snake, length); //switch on body leds at led matrix
        Snake.adapt_body(snake, length); //update body direction
        /**********check change at snake direction & update snake head direction***********/
        Snake.change_direction(snakehead);
        /**********check change at snake direction& update snake head direction***********/
        
        if ((snakehead->srow == apple.row) && (snakehead->scolumn == apple.column)) {
            Snake.happy_meal(&snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1]);
            length++;
            Snake.renew_apple(applepointer, snakehead); //update apple location
        }
        while (Snake.check_collision(applepointer, snakehead)) { //check if apple location is proper
            temp--;
            //Snake.renew_apple(applepointer, temp);
        }
      temp = snakehead;
      Snake.update_head(snakehead); //update head location
      Snake.light_bit(snakehead -> srow, snakehead -> scolumn); //switch on snake head LED
      if ((snakehead -> srow == 1) || (snakehead -> srow == ledmatrix_length) || (snakehead -> scolumn == 1) || (snakehead -> scolumn == ledmatrix_width) || Snake.body_crash(snakehead)) //check for game over
      {
        update = false;
      }
    }
}