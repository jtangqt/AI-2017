#include <iostream>
#include "piece.hpp"


Piece::Piece(std::string color, int num, int row, int col){
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

int Piece::get_row(){ return row; }
int Piece::get_col(){ return col; }
bool Piece::is_king(){ return isKing; }