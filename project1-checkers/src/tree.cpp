#include <iostream>
#include "tree.hpp"

Tree::Tree(int **a_board, list<Piece> player1, list<Piece> player2){
	arr = (int **)malloc(row*col*sizeof(int *));
	for(int i = 0; i<8; i++){
		arr[i] = (int*)malloc(col*sizeof(int));
	}

	memcpy(arr, a_board, row*col*sizeof(int));

	this -> player1 = player1; 
	this -> player2 = player2; 

}

list<Move*> Tree::get_possible_jumps(int **a_board, int row, int col, int player_num, bool is_king){//HERE!! it's not the object part; it should be sharing an array now
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

list<Move*> Tree::get_all_possible_moves(list <Piece> y_turn){// HERE!! it's not the object part; it should be sharing an array now
	list<Move *> pos_moves, all_pos_jumps, pos_jumps; 
	list<Piece>::iterator it; 
	int row, col, player_num;
	bool is_king;  

	for(it = y_turn.begin(); it != y_turn.end(); it++){

		row = it -> get_row(); 
		col = it -> get_col();
		player_num = it -> get_player_num(); 
		is_king = it -> is_king(); 

		pos_jumps = get_possible_jumps(arr, row, col, player_num, is_king);
		all_pos_jumps.merge(pos_jumps);
	}

	if(all_pos_jumps.empty()){
		for(it = y_turn.begin(); it != y_turn.end(); it++){

			row = it -> get_row(); 
			col = it -> get_col();
			player_num = it -> get_player_num(); 
			is_king = it -> is_king(); 

			if((it->is_king() || player_num == 1) && (arr[row-1][col-1] == 0) && row-1>= 0 && col-1 >=0){
				Move *m = new Move(row, col, row-1, col-1);
				pos_moves.push_back(m);
			}
			if((it->is_king() || player_num == 1) && (arr[row-1][col+1] == 0) && row-1>= 0 && col+1 <=7){ 
				Move *m = new Move(row, col, row-1, col+1);
				pos_moves.push_back(m);
			}
			if((it->is_king() || player_num == 2) && (arr[row+1][col-1] == 0) && row+1<=7 && col-1 >=0){
				Move *m = new Move(row, col, row+1, col-1);
				pos_moves.push_back(m);
			}
			if((it->is_king() || player_num == 2) && (arr[row+1][col+1] == 0) && row+1<=7 && col+1 <=7){
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

list<Piece> move_b_del_p(list<Piece> n_turn, Move *move_to_make){
	list<Deleted> to_delete;
	
	list<Piece>::iterator n_it; 
	list<Deleted>::iterator d_it; 

	to_delete = leaf.update_board(move_to_make); //TODO

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


int **Tree::share_board(){
	int **dest = (int**)malloc(row*col*sizeof(int));
	memcpy(dest, arr, row*col*sizeof(int));
	return dest; 
} //this shares the board so that we can save it into the object


std::list<Deleted> Tree::make_temp_board(Move *move_to_make){
	list<Deleted> to_delete; 
	int del_row, del_col, curr_row, curr_col, new_row, new_col, beg_row, beg_col; 
	Move *current = move_to_make;

	beg_row = current -> get_curr_row();
	beg_col = current -> get_curr_col(); 
	
	while(current){
		curr_row = current -> get_curr_row();
		curr_col = current -> get_curr_col();
		new_row = current -> get_next_row();
		new_col = current -> get_next_col(); 
		
		if(abs(new_row - curr_row) ==2){
			del_row = (new_row - curr_row)/2 + curr_row;
			del_col = (new_col - curr_col)/2 + curr_col; 

			arr[del_row][del_col] = 0;

			Deleted new_delete(del_row, del_col);
			to_delete.push_back(new_delete);
		}
		current = current ->get_next();  
	} 
	
	int p_val = arr[beg_row][beg_col];
	arr[beg_row][beg_col] = 0; 

	if((p_val == 1 && new_row == 0) || (p_val == 2 && new_row == 7)){
		p_val = p_val + 2;  
	}

	arr[new_row][new_col] = p_val; 
	
	return to_delete; 
} //TODO