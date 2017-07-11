#include <iostream>
#include "piece.hpp"


Piece::Piece(string color, int num){
	this->num = num; 
	this->color = color; 
	isKing = false;
	val = 1.0f; 
}

void Piece::set_val(int val){
	this->val = val;
}

void Piece::make_king(){
	isKing = true; 
	val = 1.8f; 
}

void Piece::set_val(int x, int y){ 
	this->x = x; 
	this->y = y; 
} //HERE!! I need to set x's and y's

int Piece::get_x(){ return x; }
int Piece::get_y(){ return y; }