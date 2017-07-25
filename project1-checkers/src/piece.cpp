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

void Piece::update_piece(Move *move_to_make){

	Move *current = move_to_make;
	cout << "(" << current->get_curr_row() << "," << current -> get_curr_col() << ")";
	cout << " -> (" <<current -> get_next_row() << "," << current -> get_next_col() << ")"; 
	while(current -> get_next()){
		current = current ->get_next();  
		cout << " -> (" << current->get_next_row() << "," << current -> get_next_col() << ")";
	} 
	cout << endl;
	
	row = current -> get_next_row(); 
	col = current -> get_next_col(); 

}

void Piece::delete_pieces(std::list<Deleted> to_delete){
	//TODO
	list<Delete>::iterator it;

	for(it = to_delete.begin(); it!= to_delete.end(); it++){
		if(it -> get_row == row && it -> get_col == col){
			
		}	
	}
}
