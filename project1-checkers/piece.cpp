#include <iostream>
#include "piece.hpp"


Piece::Piece(string color, int num, int row, int col){
	this->num = num; 
	this->color = color; 
	isKing = false;
	val = 1.0f; 
	this->row = row; 
	this->col = col; 
}

void Piece::make_king(){
	isKing = true; 
	val = 1.8f; 
}

void Piece::set_position(int row, int col){ 
	this->row = row; 
	this->col = col; 
}

int Piece::get_row(){ return row; }
int Piece::get_col(){ return col; }