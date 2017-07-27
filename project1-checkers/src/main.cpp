#include <iostream>
#include <list>
#include <fstream>
#include <vector>

#include "board.hpp"


using namespace std; 

void move_piece(Board &object, list<Piece> y_turn, list<Piece> n_turn, Move *move_to_make);

list<Move*> get_possible_jumps(int **a_board, int row, int col, int player_num, bool is_king){//HERE!! it's not the object part; it should be sharing an array now
	list<Move*> pos_jumps; 
	int temp_board[8][8];
	list<Move *>::iterator it;

	cout << "(" << row<< ","<< col << ")"<<endl; 

	if((is_king==1 || player_num == 1) && a_board[row-1][col-1] % 2 == player_num-1 && a_board[row-1][col-1] && row-1>=0 && col-1>=0){ // If player 2 piece is there (even)
		if(a_board[row-2][col-2] == 0 && row-2>=0 && col-2>=0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row-2][col-2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row-1][col-1] = 0;

			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row-2, col-2, player_num, is_king);
			if(sub_jumps.empty()){
				Move *j = new Move(row, col, row-2, col-2);
				pos_jumps.push_back(j);
			}
			else{
				for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
					Move *j = new Move(row, col, row-2, col-2);
					j->set_next(*it);
					pos_jumps.push_back(j);
				}	
			}
		}
	}
	if((is_king==1 || player_num == 1) && a_board[row-1][col+1] % 2 == player_num-1 && a_board[row-1][col+1] && row-1>=0 && col+1<=7){ // If player 2 piece is there (even)
		if(a_board[row-2][col+2] == 0 && row-2>=0 && col+2<=7){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row-2][col+2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row-1][col+1] = 0;;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row-2, col+2, player_num, is_king);
			if(sub_jumps.empty()){
				Move *j = new Move(row, col, row-2, col+2);
				pos_jumps.push_back(j);
			}
			else{
				for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
					Move *j = new Move(row, col, row-2, col+2);
					j->set_next(*it);
					pos_jumps.push_back(j);
				}	
			}
		}
	}
	if((is_king==1 || player_num == 2) && (a_board[row+1][col-1] % 2 == player_num-1) && a_board[row+1][col-1] && row+1<=7 && col-1>=0){ // If king and player 2 piece is there (even)
		if(a_board[row+2][col-2] == 0 && row+2<=7 && col-2>=0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row+2][col-2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row+1][col-1] = 0;;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row+2, col-2, player_num, is_king);
			if(sub_jumps.empty()){
				Move *j = new Move(row, col, row+2, col-2);
				pos_jumps.push_back(j);
			}
			else{
				for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
					Move *j = new Move(row, col, row+2, col-2);
					j->set_next(*it);
					pos_jumps.push_back(j);
				}	
			}
		}
	}
	if((is_king==1 || player_num == 2) && (a_board[row+1][col+1] % 2 == player_num-1) && a_board[row+1][col+1] && row+1<=7 && col+1<= 7){ // If king and player 2 piece is there (even)
		if(a_board[row+2][col+2] == 0 && row+2<=7 && col+2<=7){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[row+2][col+2] = temp_board[row][col]; // Update board
			temp_board[row][col] = 0;
			temp_board[row+1][col+1] = 0;;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, row+2, col+2, player_num, is_king);
			if(sub_jumps.empty()){
				Move *j = new Move(row, col, row+2, col+2);
				pos_jumps.push_back(j);
			}
			else{
				for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
					Move *j = new Move(row, col, row+2, col+2);
					j->set_next(*it);
					pos_jumps.push_back(j);
				}	
			}
		}
	}	
	return pos_jumps; 
}

list<Move*> get_all_possible_moves(Board &object, list <Piece> y_turn){// HERE!! it's not the object part; it should be sharing an array now
	list<Move *> pos_moves, all_pos_jumps, pos_jumps; 
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
		all_pos_jumps.merge(pos_jumps);
	}

	if(all_pos_jumps.empty()){
		for(it = y_turn.begin(); it != y_turn.end(); it++){

			row = it -> get_row(); 
			col = it -> get_col();
			player_num = it -> get_player_num(); 
			is_king = it -> is_king(); 

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
	}
	else{
		pos_moves.merge(all_pos_jumps);
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


Move *determine_move(Board &object, list<Piece> y_turn){

	list<Move *> p_move; 
	list<Move*>::iterator move_to_make; 
	list<Move *>::iterator it; 
	int val, row, col, i = 0, j = 0; 

	p_move=get_all_possible_moves(object, y_turn);

	cout<<"Which move would you like to make?"<<endl;;

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

	return (*move_to_make); 
	
}

list<Piece> move_player_piece(list<Piece> y_turn, Move *move_to_make){
	list<Piece>::iterator y_it;

	int curr_row = move_to_make -> get_curr_row();
	int curr_col = move_to_make -> get_curr_col(); 

	for(y_it = y_turn.begin(); y_it != y_turn.end(); y_it++){
		if(y_it -> get_row() == curr_row && y_it -> get_col() == curr_col){
			y_it -> update_piece(move_to_make);
		}
	}

	return y_turn; 
}

list<Piece> move_b_del_p(Board &object, list<Piece> n_turn, Move *move_to_make){
	list<Deleted> to_delete;
	
	list<Piece>::iterator n_it; 
	list<Deleted>::iterator d_it; 

	to_delete = object.update_board(move_to_make);

	/* Testing print stuff */
	//move_to_make = new Move(1,1, 3,3);
	//move_to_make->set_next(new Move(3,3, 2,2));
	//move_to_make->get_next()->set_next(new Move(2,2, 4,4));
	
	for(n_it = n_turn.begin(); n_it != n_turn.end(); n_it++){
		for(d_it = to_delete.begin(); d_it != to_delete.end(); d_it++){
			if((n_it -> get_row() == d_it -> get_row()) && (n_it -> get_col() == d_it -> get_col())){
				n_it = n_turn.erase(n_it);
			}
		}	
	}	

	return n_turn; 
}

int main(){
	
	char val, end_val; 
	int x = 0, input_val = 1; 
	int time = 0; 
	Move *move_to_make;
	cout << "Type 'A' for a new game or 'B' for a customizeable board. "; 
	cin >> val;   

	Board board(8, 8);	

	std::list<Piece> player1;
	std::list<Piece> player2;

	if(val == 'A'){
		cout << "(0,0) is top-left corner; player 1 starts at the bottom of the board." <<endl; 
		player1 = board.norm(1);
		player2 = board.norm(2);
		board.print_board(); 
	}
	else{
		cout<< "1. Board is up vs. down \n2. Red is always on the bottom and always player 1.\n3. 1 - Player 1 (RED) \t 2 - Player 2 (GREEN) \t 3 - Player 1 King (RED) \t 4 - Player 2 King (GREEN)"<<endl; 

		ifstream file;
		file.open("../input.txt");

		int p_val, value, k = 0; 
		vector<int> temp_board; 

		while (file >> value) {
			temp_board.push_back(value);
		}
		
		file.close(); 

		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				p_val = temp_board[k++];
				board.cust(p_val, i, j);
				if(p_val == 1){
					Piece piece("RED", p_val, i, j);
					player1.push_back(piece);
				}
				else if(p_val == 2){
					Piece piece("GREEN", p_val, i, j);
					player2.push_back(piece);
				}
				else if(p_val == 3){
					Piece piece("RED", p_val-2, i, j);
					piece.make_king(); 
					player1.push_back(piece);
				}
				else if(p_val == 4){
					Piece piece("GREEN", p_val-2, i, j);
					piece.make_king(); 
					player2.push_back(piece);	
				}
			}
		}

		board.print_board(); 

		cout << "Player '1' or '2' starting first?. "; 
		cin >> input_val;
	}
		
	if(input_val == 2){
		move_to_make = determine_move(board, player2);
		player2 = move_player_piece(player2, move_to_make);
		player1 = move_b_del_p(board, player1, move_to_make);
		board.print_board();
	}

	while (x == 0){
		move_to_make = determine_move(board, player1);
		player1 = move_player_piece(player1, move_to_make);
		player2 = move_b_del_p(board, player2, move_to_make);
		board.print_board();

		move_to_make = determine_move(board, player2);
		player2 = move_player_piece(player2, move_to_make);
		player1 = move_b_del_p(board, player1, move_to_make);
		board.print_board();
		
		cout << "Would you like to end the game?"<<endl;
		cin >> end_val;
		if (end_val == 'Y'){
			x = 1; 
		}
	}

	//TODO 
	//seg fault when jumping second time from a side space
}
