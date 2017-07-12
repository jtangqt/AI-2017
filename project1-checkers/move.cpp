#include <iostream>
#include "move.hpp"


Move::Move(int curr_x, int curr_y, int new_x, int new_y, int num){ 
	this -> curr_x;
	this -> curr_y;
	this -> new_x;
	this -> new_y;
	this -> num = num;
	this->next_move = NULL;
}

void Move::clear_val(){
	curr_x = curr_y = new_x = new_y = num = 0;
}