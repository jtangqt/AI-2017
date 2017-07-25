#include <iostream>
#include <move.hpp>

Move::Move(int curr_row, int curr_col, int next_row, int next_col){
	this -> curr_row = curr_row;
	this -> curr_col = curr_col;
	this -> next_row = next_row;
	this -> next_col = next_col; 
	next_move = NULL;
}

void Move::set_next(Move * next_move){
	this -> next_move = next_move;
} 

void Move::clear_val(){ 
	curr_row = curr_col =  next_col = next_row = 0;
	next_move = NULL; 
}

int Move::get_curr_row(){ return curr_row; }
int Move::get_curr_col(){ return curr_col; }
int Move::get_next_row(){ return next_row; }
int Move::get_next_col(){ return next_col; } 
Move *Move::get_next(){ return next_move; }