#include <iostream>
#include <list>

#include "board.hpp"


using namespace std; 

void move_piece(Board &object, list<Piece> y_turn, list<Piece> n_turn, Move *move_to_make);

list<Move*> get_all_possible_jumps(Board &object, int row, int col, int player_num){//HERE!! it's not the object part; it should be sharing an array now
	list<Move*> pos_jumps; 
	return pos_jumps; 
	//HERE!!
}

list<Move*> get_all_possible_moves(Board &object, list <Piece> y_turn){// HERE!! it's not the object part; it should be sharing an array now
	list<Move *> pos_moves;
	list<Move *> pos_jumps; 
	list<Piece>::iterator it; 
	int row, col, player_num; 

	for(it = y_turn.begin(); it != y_turn.end(); it++){
		cout << "(" << it -> get_row()  << "," << it -> get_col() << ")" << endl;

		row = it -> get_row(); 
		col = it -> get_col();
		player_num = it -> get_player_num(); 

		pos_jumps = get_all_possible_jumps(object, row, col, player_num);
		if(pos_jumps.empty()){
			//HERE!!
		}
		else{
			pos_moves.merge(pos_jumps);
		}
	}

	return pos_moves; 
}

void print_list(){
	//HERE!!
}

void determine_move(Board &object, list<Piece> y_turn, list<Piece> n_turn){

	list<Move *> p_move; 
	Move *move_to_make; 

	p_move=get_all_possible_moves(object, y_turn);
	//determine the move to make here
	move_piece(object, y_turn, n_turn, move_to_make);
}

void move_piece(Board &object, list<Piece> y_turn, list<Piece> n_turn, Move *move_to_make){
	Deleted *to_delete;

	to_delete = object.update_board(move_to_make);
	//y_turn.update_piece(*move_to_make);
	//n_turn.delete_pieces(to_delete); 
}

int main(){
	
	char val;
	std::string input_color, new_input_color;
	cout << "Type 'A' for a new game or 'B' for a customizeable board"<<endl; 
	cin >> val;   

	Board board(8, 8);	

	std::list<Piece> player1;
	std::list<Piece> player2;

	if(val == 'A'){
		player1 = board.norm(1);
		player2 = board.norm(2);
	}
	else{
		cout<< "1. Board is up vs. down \n2. Black is on the bottom and starts first unless you customize\n3. First player must always be on the bottom side of the board"<<endl; 
		cout << "'RED' or 'BLACK' starting first?. "; 
		cin >> input_color;
		
		player1 = board.cust(input_color, 1);
		
		if (input_color == "BLACK"){
			new_input_color = "RED";
			player2 = board.cust(new_input_color, 2);//HERE! create individual pieces in player
		}
		else{
			new_input_color = "BLACK";
			player2 = board.cust(new_input_color, 2);
		}
	}
	board.print_board(); 


	determine_move(board, player1, player2);

}