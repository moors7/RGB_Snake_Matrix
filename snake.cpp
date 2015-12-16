// This #include statement was automatically added by the Particle IDE.
#include "SparkIntervalTimer/SparkIntervalTimer.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"

// This #include statement was automatically added by the Particle IDE.
#include "RGBmatrixPanel/RGBmatrixPanel.h"

#include "snake.h"



Serpent::Serpent()
{
}


Serpent::~Serpent()
{
}

void Serpent::snake_intialization(mysnake * snake) {
	int k;
	for (k = 0; k < ((ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4); k++) {
		snake[k].srow = 0;
		snake[k].scolumn = 0;
		snake[k].direction = 0;
	}
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3].srow = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3].scolumn = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3].direction = right;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 2].srow = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 2].scolumn = 4;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 2].direction = right;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 1].srow = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 1].scolumn = 3;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 1].direction = right;

}

void Serpent::clear_matrix() {
    //clear matrix
    matrix.fillScreen(matrix.Color444(0, 0, 0));
    matrix.swapBuffers(true);
}

void Serpent::create_border() {
    //create border
    // x,y,width, height
    // matrix.drawRect(0, 0, 32, 32, matrix.Color333(0, 255, 0));
    // //matrix.drawRect(1, 1, 31, 31, matrix.Color333(0, 255, 0));
    // matrix.swapBuffers(true);
}

void Serpent::light_bit(char row, char column) {
    //light bit
//   matrix.drawPixel(row, column, matrix.Color333(255, 150, 0));
//   matrix.swapBuffers(true);
}

void Serpent::update_body(mysnake *snake, int length) {
	int i;
	for (i = (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1; i < (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3; i++){
    	switch (snake[i + 1].direction) {
    		case 1:
    			++(snake[i].scolumn);
    			break;
    		case 2:
    			--(snake[i].scolumn);
    			break;
    		case 3:
    			++(snake[i].srow);
    			break;
    		case 4:
    			--(snake[i].srow);
    			break;
    	}
	}
}

void Serpent::show_body(mysnake * snake, int length) {
	int i;
	for (i = (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1; i < (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3; i++) {
		light_bit(snake[i].srow, snake[i].scolumn);
	}
}

void Serpent::adapt_body(mysnake * snake, char length) {
	int i;
	for (i = (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1; i < (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3; i++) {
		snake[i].direction = snake[i + 1].direction;
	}
}

void Serpent::change_direction(mysnake *snakehead) {
	switch (snakehead -> direction) {
    	case up:
    	{
    // 		if (Button(&PORTD, rightpin, 1, 1)) {
    // 			snakehead -> direction = right;
    // 			break;
    // 		}
    // 		if (Button(&PORTD, leftpin, 1, 1)) {
    // 			snakehead -> direction = left;
    // 			break;
    // 		}
    	}
    	break;
    	case down:
    	{
    // 		if (Button(&PORTD, rightpin, 1, 1)) {
    // 			snakehead - > direction = right;
    // 			break;
    // 		}
    // 		if (Button(&PORTD, leftpin, 1, 1)) {
    // 			snakehead - > direction = left;
    // 			break;
    // 		}
    	}
    	break;
    	case right:
    	{
    // 		if (Button(&PORTD, uppin, 1, 1)) {
    // 			snakehead - > direction = up;
    // 			break;
    // 		}
    // 		if (Button(&PORTD, downpin, 1, 1)) {
    // 			snakehead - > direction = down;
    // 			break;
    // 		}
    	}
    	break;
    	case left:
    	{
    // 		if (Button(&PORTD, uppin, 1, 1)) {
    // 			snakehead - > direction = up;
    // 			break;
    // 		}
    // 		if (Button(&PORTD, downpin, 1, 1)) {
    // 			snakehead - > direction = down;
    // 			break;
    // 		}
    	}
    	break;
	}
}

void Serpent::happy_meal(mysnake *listhead) {
	mysnake *temp;
	temp = listhead - 1;

	switch (listhead->direction) {
    	case 1:
        	{
        		temp->srow = listhead->srow;
        		temp->scolumn = (listhead->scolumn) - 1;
        	} //right
        break;
    	case 2:
        	{
        		temp->srow = listhead->srow;
        		temp->scolumn = (listhead->scolumn) + 1;
        	} //left
        break;
    	case 3:
        	{
        		temp->srow = (listhead->srow) - 1;
        		temp->scolumn = listhead->scolumn;
        	} //down
        break;
    	case 4:
        	{
        		temp->srow = (listhead->srow) + 1;
        		temp->scolumn = listhead->scolumn;
        	}; //up
        break;
	}
	temp->direction = listhead->direction;

}

void Serpent::renew_apple(food * applepointer, mysnake * listhead) {
  applepointer->row = random(32);
  applepointer->column = random(32);
}

bool Serpent::check_collision(food* applepointer, mysnake* listhead) {
	mysnake* temp;
	temp = listhead;
	while (temp -> direction != 0) {
		if ((applepointer -> row == temp -> srow) && (applepointer -> column == temp -> scolumn)) {
			return 1;
		}
		--temp;
	}
	return 0;
}

void Serpent::update_head(mysnake* snakehead) {
	switch (snakehead -> direction) {
    	case 1:
    		++(snakehead -> scolumn); //right
    	break;
    	case 2:
    		--(snakehead -> scolumn); //left
    	break;
    	case 3:
    		++(snakehead -> srow); //down
    	break;
    	case 4:
    		--(snakehead -> srow); //up
    	break;
	}
}

bool Serpent::body_crash(mysnake* listhead) {
	mysnake* temp;
	temp = listhead - 1;
	while (temp -> direction != 0) {
		if ((listhead -> srow == temp -> srow) && (listhead -> scolumn == temp -> scolumn))
			return 1;
		--temp;
	}
	return 0;
}

void Serpent::clear(mysnake * snake) {
	int k;
	for (k = 0; k < ((ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4); k++) {
		snake[k].srow = 0;
		snake[k].scolumn = 0;
		snake[k].direction = 0;
	}
}
/*

char Serpent::zone_detect(char row, char column) {
	if (column <= 8)
		return 1;
	if (column > 8 && column <= 16)
		return 2;
	if (column > 16 && column <= 24)
		return 3;
	if (column > 24 && column <= 32)
		return 4;
}


void Serpent::write_byte(char serial) {
	int i;
	for (i = 7; i >= 0; i--) {
		data = ((serial >> i) & 1);
		clk = 1;
		clk = 0;
	}
	latch = 1;
	latch = 0;
}


void Serpent::gameover(char * patt1, char * patt2, char * patt3, char * patt4) {
	char i;
	for (i = 0; i < 16; i++)
		patt1[i] = 0;
	for (i = 0; i < 16; i++)
		patt2[i] = 0;
	for (i = 0; i < 16; i++)
		patt3[i] = 0;
	for (i = 0; i < 16; i++)
		patt4[i] = 0;
}


void Serpent::print1(char * patt1, char * patt2, char * patt3, char * patt4) {
	char i;
	char symbol1[16] = {
		0xe7, 0xdb, 0xbd, 0xbd, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,
		0xbf, 0xb8, 0xbd, 0xbd, 0xbd, 0xdb, 0xe7
	}; //g
	char symbol2[16] = {
		0xE7, 0xC3, 0x81, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0x81,
		0x81, 0x81, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd
	}; //a
	char symbol3[16] = {
		0xff, 0x99, 0x81, 0xa5, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd,
		0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xff
	}; //m
	char symbol4[16] = {
		0x81, 0x81, 0x81, 0x9f, 0x9f, 0x9f, 0x9f, 0x81, 0x81,
		0x81, 0x9f, 0x9f, 0x9f, 0x81, 0x81, 0x81
	}; //e;
	for (i = 0; i < 16; i++) {
		patt1[i] = symbol1[i];
	}
	for (i = 0; i < 16; i++) {
		patt2[i] = symbol2[i];
	}
	for (i = 0; i < 16; i++) {
		patt3[i] = symbol3[i];
	}
	for (i = 0; i < 16; i++) {
		patt4[i] = symbol4[i];
	}

}


void Serpent::print2(char * patt1, char * patt2, char * patt3, char * patt4) {
	char i;
	char symbol1[16] = {
		0xe7, 0xc3, 0x81, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x99, 0x99, 0x99, 0x99, 0x81, 0xc3, 0xe7
	}; //o
	char symbol2[16] = {
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x99, 0x99, 0x99, 0x99, 0x81, 0xc3, 0xe7
	}; //v
	char symbol3[16] = {
		0x81, 0x81, 0x81, 0x9f, 0x9f, 0x9f, 0x9f, 0x81, 0x81,
		0x81, 0x9f, 0x9f, 0x9f, 0x81, 0x81, 0x81
	}; //e;
	char symbol4[16] = {
		0xc7, 0xdb, 0xdd, 0xdd, 0xdb, 0xd7, 0xcf, 0xcf, 0xd7,
		0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
	};
	for (i = 0; i < 16; i++) {
		patt1[i] = symbol1[i];
	}
	for (i = 0; i < 16; i++) {
		patt2[i] = symbol2[i];
	}
	for (i = 0; i < 16; i++) {
		patt3[i] = symbol3[i];
	}
	for (i = 0; i < 16; i++) {
		patt4[i] = symbol4[i];
	}
}


void Serpent::display(char * patt1, char * patt2, char * patt3, char * patt4) {
	char row, zone, j;
	for (row = 1; row < 5; row++) {
		for (zone = 1; zone < 5; zone++) {
			for (j = 3; j >= 0; j--) {
				switch (zone) {
				case 1:
					write_byte(patt1[(4 * (j)) + row - 1]);
					break;
				case 2:
					write_byte(patt2[(4 * (j)) + row - 1]);
					break;
				case 3:
					write_byte(patt3[(4 * (j)) + row - 1]);
					break;
				case 4:
					write_byte(patt4[(4 * (j)) + row - 1]);
					break;
				}
			}
		}
		a3 = 1;
		switch (row) {
		case 1:
		{
			a1 = 0;
			a2 = 0;
		}
		break;
		case 2:
		{
			a1 = 1;
			a2 = 0;
		}
		break;
		case 3:
		{
			a1 = 0;
			a2 = 1;
		}
		break;
		case 4:
		{
			a1 = 1;
			a2 = 1;
		}
		break;
		}
		delay_ms(1);
		a3 = 0;
	}
}


void Serpent::initialization(void) {
	ansela = 0;
	anselb = 0;
	anseld = 0;
	trisa = 0;
	trisb = 0;
	trisd = 0xff;
	a3 = 1;
	clk = 0;
	latch = 0;
}

*/