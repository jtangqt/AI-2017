#include <iostream>
#include <list>

#include "board.hpp"


using namespace std; 

void move_piece(Board &object, list<Piece> y_turn, list<Piece> n_turn, Move *move_to_make);

list<Move*> get_possible_jumps(int **a_board, int row, int col, int player_num, bool is_king){//HERE!! it's not the object part; it should be sharing an array now
	list<Move*> pos_jumps; 
	int temp_board[8][8];
	list<Move *>::iterator it;

	if((is_king==1 || player_num == 1) && a_board[row-1][col-1] % 2 == player_num-1 && a_board[row-1][col-1] && row-1>=0 && col-1>=0){ // If player 2 piece is there (even)
		if(a_board[row-2][col-2] == 0 && row-2>=0 && col-2>=0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row-2][col-2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row-1][col-1] = 0;
			cout<<"hi1";

			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row-2, col-2, player_num, is_king);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(row, col, row-2, col-2);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	if((is_king==1 || player_num == 1) && a_board[row-1][col+1] % 2 == player_num-1 && a_board[row-1][col+1] && row-1>=0 && col+1<=7){ // If player 2 piece is there (even)
		if(a_board[row-2][col+2] == 0 && row-2>=0 && col+2<=7){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row-2][col+2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row-1][col+1] = 0;
			cout<< "hi2";
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row-2, col+2, player_num, is_king);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(row, col, row-2, col+2);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	if((is_king==1 || player_num == 2) && (a_board[row+1][col-1] % 2 == player_num-1) && a_board[row+1][col-1] && row+1<=7 && col-1>=0){ // If king and player 2 piece is there (even)
		if(a_board[row+2][col-2] == 0 && row+2<=7 && col-2>=0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row+2][col-2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row+1][col-1] = 0;
			cout<<"hi3";
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row+2, col-2, player_num, is_king);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(row, col, row+2, col-2);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	if((is_king==1 || player_num == 2) && (a_board[row+1][col+1] % 2 == player_num-1) && a_board[row+1][col+1] && row+1<=7 && col+1<= 7){ // If king and player 2 piece is there (even)
		if(a_board[row+2][col+2] == 0 && row+2<=7 && col+2<=7){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row+2][col+2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row+1][col+1] = 0;
			cout <<"hi4";
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row+2, col+2, player_num, is_king);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(row, col, row+2, col+2);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	return pos_jumps; 
}

list<Move*> get_all_possible_moves(Board &object, list <Piece> y_turn){// HERE!! it's not the object part; it should be sharing an array now
	list<Move *> pos_moves;
	list<Move *> pos_jumps; 
	list<Piece>::iterator it; 
	int row, col, player_num;
	bool is_king;  
	int **a_board = {object.share_board()}; 


	for(it = y_turn.begin(); it != y_turn.end(); it++){

		row = it -> get_row(); 
		col = it -> get_col();
		player_num = it -> get_player_num(); 
		is_king = it -> is_king(); 

		pos_jumps = get_possible_jumps(a_board, row, col, player_num, is_king);
		if(pos_jumps.empty()){
			if((it->is_king() || player_num == 1) && (a_board[row-1][col-1] == 0) && row-1>= 0 && col-1 >=0){
 				Move *m = new Move(row, col, row-1, col-1);
 				pos_moves.push_back(m);
 			}
 			if((it->is_king() || player_num == 1) && (a_board[row-1][col+1] == 0) && row-1>= 0 && col+1 <=7){ 
 				Move *m = new Move(row, col, row-1, col+1);
 				pos_moves.push_back(m);
 			}
 			if((it->is_king() || player_num == 2) && (a_board[row+1][col-1] == 0) && row+1<=7 && col-1 >=0){
 				Move *m = new Move(row, col, row+1, col-1);
 				pos_moves.push_back(m);
 			}
 			if((it->is_king() || player_num == 2) && (a_board[row+1][col+1] == 0) && row+1<=7 && col+1 <=7){
 				Move *m = new Move(row, col, row+1, col+1);
 				pos_moves.push_back(m);
 			}
		}
		else{
			pos_moves.merge(pos_jumps);
		}
	}

	return pos_moves; 
}

void print_list(Move* move_from_list, int i){

	Move *current = move_from_list;
	cout <<i<< ": ";
	cout << "(" << current->get_curr_row() << "," << current -> get_curr_col() << ")";
	while(current != NULL){
		cout << "->";
		cout << "(" << current->get_next_row() << "," << current -> get_next_col() << ")"; 
		current = current ->get_next(); 
	}
	cout << endl;

}


void determine_move(Board &object, list<Piece> y_turn, list<Piece> n_turn){

	list<Move *> p_move; 
	list<Move*>::iterator move_to_make; 
	list<Move *>::iterator it; 
	int val, row, col, i = 0, j = 0; 

	p_move=get_all_possible_moves(object, y_turn);

	cout<<"Which move would you like to make?"<<endl; 

	for(it = p_move.begin(); it != p_move.end(); it++){
		print_list(*it, i);
		i++;
	}

	while(j ==0){
		cin>>val;
		if(val >= 0 && val < i){
			move_to_make = p_move.begin();
			advance(move_to_make, val); 
			j = 1;
		}
		else{
			cout<<"Invalid input, please try again."<<endl;
		}
	}
	
	move_piece(object, y_turn, n_turn, *move_to_make);

}

void move_piece(Board &object, list<Piece> y_turn, list<Piece> n_turn, Move *move_to_make){
	list<Deleted> to_delete;
	list<Piece>::iterator y_it;
	list<Piece>::iterator n_it; 
	list<Deleted>::iterator d_it; 
	int curr_row, curr_col; 

	to_delete = object.update_board(move_to_make);

	curr_row = move_to_make -> get_curr_row();
	curr_col = move_to_make -> get_curr_col(); 

	/* Testing print stuff */
	//move_to_make = new Move(1,1, 3,3);
	//move_to_make->set_next(new Move(3,3, 2,2));
	//move_to_make->get_next()->set_next(new Move(2,2, 4,4));
	
	for(y_it = y_turn.begin(); y_it != y_turn.end(); y_it++){
		if(y_it -> get_row() == curr_row && y_it -> get_col() == curr_col){
			y_it -> update_piece(move_to_make);
		}
	}
	for(n_it = n_turn.begin(); n_it != n_turn.end(); n_it++){
		for(d_it = to_delete.begin(); d_it != to_delete.end(); d_it++){
			if((n_it -> get_row() == d_it -> get_row()) && (n_it -> get_col() == d_it -> get_col())){
				n_it = n_turn.erase(n_it);
			}
		}	
	}
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


	determine_move(board, player2, player1);
	board.print_board();

	//TODO 
	//loop through until someone wants to end the game


}