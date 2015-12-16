#ifndef SNAKE_H_
#define SNAKE_H_

#include "application.h"

/*----------------definitions------------------*/

#define right 1
#define left 2
#define down 3
#define up 4

#define ledmatrix_length 32
#define ledmatrix_width 32
#define game_speed 15
/*----------------definitions------------------*/

/*----------------structures------------------*/
typedef struct snakebit {
	char srow;
	char scolumn;
	char direction;
} mysnake;

typedef struct food {
	char row;
	char column;
} food;
/*----------------structures------------------*/

#pragma once
class Serpent
{
public:
	Serpent();
	virtual ~Serpent();

	void
	    snake_intialization(mysnake* snake),
		clear_matrix(),
		create_border(),
		light_bit(char row, char column),
		update_body(mysnake* snake, int length),
		show_body(mysnake* temp, int length),
		adapt_body(mysnake* snake, char length),
		change_direction(mysnake* snakehead),
		happy_meal(mysnake* listhead),
		renew_apple(food* applepointer, mysnake* listhead),
		update_head(mysnake* snakehead),
		clear(mysnake* snake);
	
		
	bool
	    check_collision(food* applepointer, mysnake* listhead),
	    body_crash(mysnake* listhead);
		
		/*
		write_byte(char serial),
		write_byte(char serial),
		gameover(char* patt1, char* patt2, char* patt3, char* patt4),
		print1(char* patt1, char* patt2, char* patt3, char* patt4),
		print2(char* patt1, char* patt2, char* patt3, char* patt4),
		display(char* patt1, char* patt2, char* patt3, char* patt4),
		initialization(void);

	char
		zone_detect(char row, char column),
	

*/
};



#endif /* SNAKE_H_ */
