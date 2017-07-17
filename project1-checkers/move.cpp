#include <iostream>
#include "move.hpp"


Move::Move(int curr_row, int curr_col, int new_row, int new_col){ 
	this -> curr_row;
	this -> curr_col;
	this -> new_row;
	this -> new_col;
	this->next_move = NULL;
}

void Move::clear_val(){
	curr_row = curr_col = new_row = new_col =  0;
}

int Move::get_curr_row(){ return curr_row; }
int Move::get_curr_col(){ return curr_col; }
int Move::get_next_row(){ return new_row; }
int Move::get_next_col(){ return new_col; }