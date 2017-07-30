#include <iostream>
#include "tree.hpp"
#include "colormod.h"

Color::Modifier m_red(Color::FG_RED);
Color::Modifier m_green(Color::FG_GREEN);
Color::Modifier m_def(Color::FG_DEFAULT);

Tree::Tree(int **a_board, list<Piece> y_turn, list<Piece> n_turn, int p_num, Move *branch_move, bool ai_player[2]){
	arr = (int **)malloc(row*sizeof(int *));
	for(int i = 0; i<8; i++){
		arr[i] = (int*)malloc(col*sizeof(int));
		memcpy(arr[i], a_board[i], col*sizeof(int));
	}

	if(p_num == 1){
		player1.splice(player1.begin(), y_turn);
		player2.splice(player2.begin(), n_turn);
	}
	else{
		player2.splice(player2.begin(), y_turn);
		player1.splice(player1.begin(), n_turn);
	}

	ai_player = ai_player; 

	move_to_make = branch_move; 

}

list<Move*> Tree::get_possible_jumps(int **a_board, int row, int col, int player_num, bool is_king){//HERE!! it's not the object part; it should be sharing an array now
	list<Move*> pos_jumps; 
	int temp_board[8][8];
	list<Move *>::iterator it;

	if((is_king==1 || player_num == 1) && a_board[row-1][col-1] % 2 == player_num-1 && a_board[row-1][col-1] && row-1>=0 && col-1>=0){ // If player 2 piece is there (even)
		if(a_board[row-2][col-2] == 0 && row-2>=0 && col-2>=0){	// Can jump
			memcpy(temp_board, a_board, 8*sizeof(int*)); // Copy board
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
			memcpy(temp_board, a_board, 8*sizeof(int*)); // Copy board
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
			memcpy(temp_board, a_board, 8*sizeof(int*)); // Copy board
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
			memcpy(temp_board, a_board, 8*sizeof(int*)); // Copy board
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
		//cout << "(" << row<< ","<< col << ")"<<endl; 

		pos_jumps = get_possible_jumps({this -> share_board()}, row, col, player_num, is_king);
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

list<Piece> Tree::move_player_piece(list<Piece> y_turn, Move *move_to_make){
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

std::list<Deleted> Tree::update_and_delete(list<Piece> n_turn){
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
		current = current -> get_next();  
	} 
	
	int p_val = arr[beg_row][beg_col];
	arr[beg_row][beg_col] = 0; 

	if((p_val == 1 && new_row == 0) || (p_val == 2 && new_row == 7)){
		p_val = p_val + 2;  
	}

	arr[new_row][new_col] = p_val;
	
	return to_delete; 
} 

std::list<Piece> Tree::delete_player(list<Piece> n_turn, list<Deleted> to_delete){
	list<Piece>::iterator n_it; 
	list<Deleted>::iterator d_it; 

	for(n_it = n_turn.begin(); n_it != n_turn.end(); n_it++){
		for(d_it = to_delete.begin(); d_it != to_delete.end(); d_it++){
			if((n_it -> get_row() == d_it -> get_row()) && (n_it -> get_col() == d_it -> get_col())){
				n_it = n_turn.erase(n_it);
			}
		}	
	}

	return n_turn;
}

void Tree::update_player(list<Piece> y_turn, list<Piece>n_turn, int p_num){
	player1.clear(); 
	player2.clear(); 

	if(p_num == 1){
		player1.splice(player1.begin(), y_turn);
		player2.splice(player2.begin(), n_turn);
	}
	else{
		player2.splice(player2.begin(), y_turn);
		player1.splice(player1.begin(), n_turn);
	}
}

std::list<Tree> Tree::find_all_leaves(int p_num){
	list<Move *> p_move;
	list<Move *>::iterator it; 
	list<Piece> y_turn, n_turn; 
	int **a_board = {this->share_board()};

	if(p_num == 1){
		y_turn.splice(y_turn.begin(), player1);
		n_turn.splice(n_turn.begin(), player2);
	}
	else{
		y_turn.splice(y_turn.begin(), player2);
		n_turn.splice(n_turn.begin(), player1);
	}
	
	p_move = get_all_possible_moves(y_turn);

	for(it = p_move.begin(); it != p_move.end(); it++){		

		Tree *leaf = create_new(a_board, y_turn, n_turn, p_num, (*it));
			
		branches.push_back(*leaf);
	}

	return branches; 
}

Tree *Tree::create_new(int **a_board, list<Piece> y_turn, list<Piece> n_turn, int p_num, Move *move_to_make){
	int temp_board[8][8];
	memcpy(temp_board, a_board, 8*sizeof(int*));
	list<Piece> new_y_turn, new_n_turn;
	list<Deleted> to_delete; 

	Tree *leaf = new Tree((int**)temp_board, y_turn, n_turn, p_num, move_to_make, this -> ai_player); 
		
	new_y_turn = leaf -> move_player_piece(y_turn, move_to_make);
	to_delete = leaf -> update_and_delete(n_turn);
	new_n_turn = leaf -> delete_player(n_turn, to_delete); 

	leaf -> update_player(new_y_turn, new_n_turn, p_num);

	return leaf; 
}

int **Tree::share_board(){
	int **dest = (int**)malloc(row*sizeof(int*));
	memcpy(dest, arr, row*sizeof(int*));
	return dest;
}

std::list<Tree> Tree::share_branches(){ return branches; } 

Move *Tree::share_move(){ return move_to_make; }

void Tree::print_board(){
	cout << "_________________" << endl;
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				cout << "|";
				switch(arr[i][j]){
					case 0:
						cout << " ";
						break;
					case 1:
						cout << m_red << "*" << m_def;
						break;
					case 2:
						cout << m_green << "*" << m_def;
						break;
					case 3:
						cout << m_red << "O" << m_def;
						break;
					case 4:
						cout << m_green << "O" << m_def;
				}
			}
			cout << "|" << endl;
		}
		cout << "-----------------" << endl;
}

int Tree::evaluate_board(){
	int a; 
	return a; 
}

void Tree::update_ai(bool ai_player[2]){
	this -> ai_player = ai_player; 
}