#include "font3x5.h"

#include "font5x5.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"

// This #include statement was automatically added by the Particle IDE.
#include "RGBmatrixPanel/RGBmatrixPanel.h"

#include "math.h"

// This #include statement was automatically added by the Particle IDE.
#include "snake.h"



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

void play_snake();
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

char topLine[40] = {"GAME OVER!"};

int length = 3;
bool update = true;
int Delay = 0;

long speed = game_speed;
long previousMillis = 0;
unsigned long currentMillis = 0;

mysnake* temp;
mysnake snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4]; //create snake matrix
mysnake* snakehead; //pointer to head of the snake
food apple;
food* applepointer;


Serpent Snake(&matrix);

//Timer snake_timer(500, play_snake);


void setup() {
    Particle.function("direction", change_direction);
    Particle.function("speed", change_speed);
    matrix.begin();
    
    
    
    matrix.fillScreen(matrix.Color444(0, 255, 0));
    matrix.swapBuffers(true);
    delay(50);
    
    snakehead = &snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3];
    apple.row = 5;
    apple.column = 5;
    applepointer = &apple;
    Snake.snake_intialization(snake); //initialize snake location and direction
    //Snake.create_border();
    //snake_timer.start();
}

void loop() {
    //Particle.publish("loop");
    // update ? snake_alive() : snake_dead();
    // delay(speed);
    
    currentMillis = millis();
 
    if(currentMillis - previousMillis > speed) {
        // save the last time you blinked the LED 
        previousMillis = currentMillis;   
        update ? snake_alive() : snake_dead();
    }
}

// void play_snake()
// {
//   update ? snake_alive() : snake_dead();
// }

int change_direction(String command){
    Snake.set_new_direction(command.toInt());
}

int change_speed(String command){
    speed = command.toInt();
}


void snake_alive(){
    Snake.clear_matrix();
    Snake.create_border();
    Snake.light_bit(applepointer -> row, applepointer -> column, 2);
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
    Snake.light_bit(snakehead -> srow, snakehead -> scolumn, 1); //switch on snake head LED
    if ((snakehead -> srow == 0) || (snakehead -> srow == ledmatrix_length-1) || (snakehead -> scolumn == 0) || (snakehead -> scolumn == ledmatrix_width-1) || Snake.body_crash(snakehead)) //check for game over
    {
        update = false;
    }
}

void snake_dead(){
    Delay++;
    if (Delay == 5) {
        length = 0;
        Snake.clear(snake); //remove snake directions and locations
        
        // matrix.setCursor(1, 0);   // start at top left, with one pixel of spacing
        // matrix.setTextSize(1);    // size 1 == 8 pixels high
        
        // print each letter with a rainbow color
        // matrix.setTextColor(matrix.Color333(255,0,0));
        // matrix.print('GAME');
        
        // matrix.setCursor(1, 9);   // next line
        // matrix.setTextColor(matrix.Color333(255,0,0)); 
        
        scrollBigMessage(topLine);
        
        // scrollMessage(topLine, 53, 0xF800);
        // matrix.drawLine(1, 1, 30, 30, matrix.Color333(255, 0, 0));
        // matrix.drawLine(1, 30, 30, 1, matrix.Color333(255, 0, 0));
        // matrix.swapBuffers(true);
        //Snake.print1(patt1, patt2, patt3, patt4); //print game
    } 
    else if (Delay == 10) {
        //Snake.print2(patt1, patt2, patt3, patt4); //print over
    } 
    else if (Delay == 15) {
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




int calc_font_displacement(uint8_t font_size)
{
	switch(font_size)
	{
	case 51:
		return 4;  //5x3 hence occupies 4 columns ( 3 + 1(space btw two characters))
		break;

	case 53:
		return 6;
		break;
		//case 56:
		//return 6;
		//break;
	default:
		return 6;
		break;
	}
}

void drawChar(int x, int y, char c, uint8_t font_size, uint16_t color)  // Display the data depending on the font size mentioned in the font_size variable
{

	uint8_t dots;
	if ((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z')) {
		c &= 0x1F;   // A-Z maps to 1-26
	} 
	else if (c >= '0' && c <= '9') {
		c = (c - '0') + 27;
	} 
	else if (c == ' ') {
		c = 0; // space
	}
	else if (c == '#'){
		c=37;
	}
	else if (c=='/'){
		c=37;
	}

	switch(font_size)
	{
	case 51:  // font size 3x5  ascii value of 3: 51

		if(c==':'){
			matrix.drawPixel(x+1,y+1,color);
			matrix.drawPixel(x+1,y+3,color);
		}
		else if(c=='-'){
			matrix.drawLine(x,y+2,3,0,color);
		}
		else if(c=='.'){
			matrix.drawPixel(x+1,y+2,color);
		}
		else if(c==39 || c==44){
			matrix.drawLine(x+1,y,2,0,color);
			matrix.drawPixel(x+2,y+1,color);
		}
		else{
			for (uint8_t row=0; row< 5; row++) {
				dots = font3x5[(uint8_t)c][row];
				for (uint8_t col=0; col < 3; col++) {
					int x1=x;
					int y1=y;
					if (dots & (4>>col))
					matrix.drawPixel(x1+col, y1+row, color);
				}    
			}
		}
		break;

	case 53:  // font size 5x5   ascii value of 5: 53

		if(c==':'){
			matrix.drawPixel(x+2,y+1,color);
			matrix.drawPixel(x+2,y+3,color);
		}
		else if(c=='-'){
			matrix.drawLine(x+1,y+2,3,0,color);
		}
		else if(c=='.'){
			matrix.drawPixel(x+2,y+2,color);
		}
		else if(c==39 || c==44){
			matrix.drawLine(x+2,y,2,0,color);
			matrix.drawPixel(x+4,y+1,color);
		}
		else{
			for (uint8_t row=0; row< 5; row++) {
				dots = font5x5[(uint8_t)c][row];
				for (uint8_t col=0; col < 5; col++) {
					int x1=x;
					int y1=y;
					if (dots & (64>>col))  // For some wierd reason I have the 5x5 font in such a way that.. last two bits are zero.. 
					matrix.drawPixel(x1+col, y1+row, color);        
				}
			}
		}          

		break;
	default:
		break;
	}
}

void drawString(int x, int y, char* c,uint8_t font_size, uint16_t color)
{
	// x & y are positions, c-> pointer to string to disp, update_s: false(write to mem), true: write to disp
	//font_size : 51(ascii value for 3), 53(5) and 56(8)
	for(uint16_t i=0; i< strlen(c); i++)
	{
		drawChar(x, y, c[i],font_size, color);
		x+=calc_font_displacement(font_size); // Width of each glyph
	}
}

void scrollMessage(char* top,uint8_t top_font_size, uint16_t top_color){

	int l = (strlen(top)*-6) - 32;
	
	for(int i=32; i > l; i--){
		Snake.clear_matrix();
		drawString(i,4,top,top_font_size, top_color);
		matrix.swapBuffers(false);
		delay(50);
		Spark.process();
	}

}



void scrollBigMessage(char *m){
    matrix.setTextSize(2);
    int l = (strlen(m)*-6) - 32;
    for(int i = 32; i > l; i--){
        Snake.clear_matrix();
        matrix.setCursor(i,8);

        matrix.print(m);
        matrix.swapBuffers(false);
        delay(50);
        Spark.process();
    }
}