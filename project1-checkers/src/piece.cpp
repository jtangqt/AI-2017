#include <iostream>
#include <piece.hpp>

Piece::Piece(std::string color, int player_num, int row, int col){
	this -> color = color;
	this -> player_num = player_num;
	this -> row = row;
	this -> col = col; 
	isKing = false; 
	val = 1.0f; 
}

void Piece::make_king(){
	isKing = true; 
	val = 1.8f; 
}

int Piece::get_row(){ return row; }
int Piece::get_col(){ return col; }
int Piece::get_player_num(){ return player_num; }
bool Piece::is_king(){ return isKing; }

void Piece::update_piece(Move *move_to_make){}
void Piece::delete_pieces(Deleted *to_delete){}