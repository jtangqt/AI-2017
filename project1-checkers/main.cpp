#include <iostream>
#include <string> 
#include <list>
#include <cstring>
#include "piece.hpp"
#include "move.hpp"
#include "board.hpp"


using namespace std;

int i, j, k; 


list<Move *> get_possible_jumps(int **a_board, int x, int y, bool is_king, int p_num){
	list<Move *> pos_jumps;
	int temp_board[8][8];
	list<Move *>::iterator it;

	cout<< x<<" "<<y << " "<<is_king << " "<< p_num<<endl;

	if((is_king==1 || p_num == 1) && a_board[y-1][x-1] % 2 == p_num-1){ // If player 2 piece is there (even)
		cout << "hi4"<<endl; 
		if(a_board[y-2][x-2] == 0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[y-2][x-2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y-1][x-1] = 0;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, x-2, y-2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(x, y, x-2, y-2, 0);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	if((is_king==1 || p_num == 1) && a_board[y-1][x+1] % 2 == p_num-1){ // If player 2 piece is there (even)
		cout<<"hi5"<<endl;
		if(a_board[y-2][x+2] == 0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[y-2][x+2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y-1][x+1] = 0;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, x+2, y-2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(x, y, x+2, y-2, 0);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	if((is_king==1 || p_num == 2) && (a_board[y+1][x-1] % 2 == p_num-1)){ // If king and player 2 piece is there (even)
		cout<<"hi6"<<endl; 
		if(a_board[y+2][x-2] == 0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[y+2][x-2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y+1][x-1] = 0;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, x-2, y+2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(x, y, x-2, y+2, 0);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	if((is_king==1 || p_num == 2) && (a_board[y+1][x+1] % 2 == p_num-1)){ // If king and player 2 piece is there (even)
		cout<<"hi7"<<endl;
		if(a_board[y+2][x+2] == 0){	// Can jump
			memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
			temp_board[y+2][x+2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y+1][x+1] = 0;
		
			/** Recursion **/
			list<Move *> sub_jumps = get_possible_jumps((int**)temp_board, x+2, y+2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move *j = new Move(x, y, x+2, y+2, 0);
				j->set_next(*it);
				pos_jumps.push_back(j);
			}
		}
	}
	cout<<"hi8"<<endl;
	return pos_jumps;
}

/** Pass in list of pieces for a player **/
list<Move*> get_all_possible_moves(list<Piece> l_pieces, int **a_board, int p_num){
 	list<Move *> pos_moves;
 	
 	list<Piece>::iterator it;
 	
	for(it = l_pieces.begin(); it != l_pieces.end(); it++){
 		list<Move *> pos_jumps = get_possible_jumps(a_board, it->get_col(), it->get_row(), it->is_king(), p_num);
 		cout <<"hello"<<endl; 
		int x = it-> get_col();
 		int y = it -> get_row(); 
 		if(pos_jumps.empty()){
 			// Cannot jump, can only make a single move
 			if((it->is_king() || p_num == 1) && a_board[y-1][x-1] == 0){
 				Move *m = new Move(x, y, x-1, y-1, 0);
 				pos_moves.push_back(m);
 			}
 			if((it->is_king() || p_num == 1) && a_board[y-1][x+1] == 0){
 				Move *m = new Move(x, y, x+1, y-1, 0);
 				pos_moves.push_back(m);
 			}
 			if((it->is_king() || p_num == 2) && a_board[y+1][x-1] == 0){
 				Move *m = new Move(x, y, x-1, y+1, 0);
 				pos_moves.push_back(m);
 			}
 			if((it->is_king() || p_num == 2) && a_board[y+1][x+1] == 0){
 				Move *m = new Move(x, y, x+1, y+1, 0);
 				pos_moves.push_back(m);
 			}
 		}else{
 			cout << "hi9"<<endl;
			pos_moves.merge(pos_jumps);
 		}
 	}
	return pos_moves; 
 }

int **move_piece(list<Piece> player_num, Move *make_move, int **a_board, int row, int col){
//recursive function for the piece
	//list::pop_front
	//create a temporary board and put it into move_piece and take the front of p_move as the move
	int temp_board[8][8];

	int next_row = make_move->get_next_row();
	int next_col = make_move -> get_curr_row(); 

	memcpy(temp_board, a_board, 8*8*sizeof(int)); // Copy board
	temp_board[next_row][next_col] = temp_board[row][col]; // Update board
	temp_board[row][col] = 0;

	if((next_row - row)%2 == 0){//if they jumped over the piece
		int val_row = next_row - row;
		int val_col = next_col -col; 
	}


	if(make_move->get_next() != NULL){
		return move_piece(player_num, make_move->get_next(), (int **)temp_board, next_row, next_col);
	}
	else{
		return (int**)temp_board;	
	}
}

void print_list(Move* move_from_list){
	cout << move_from_list->get_curr_row() << move_from_list->get_curr_col()<<endl; 
	if(move_from_list->get_next() != NULL){
		print_list(move_from_list->get_next()); 
	}
	else{
		cout << move_from_list->get_next_row() << move_from_list-> get_next_row()<<endl;		
	}

}

int **determine_move(list<Piece> player_piece, int **a_board, int p_num){//HERE!! make up valid name for function
	//the user chooses what to move
	//updates in move, piece and board

	list<Move *> p_move; 
	p_move=get_all_possible_moves(player_piece, a_board, p_num);
	int i = 1; 

	cout<<"Which piece would you like to move?"<<endl; 
	Move *move_to_make; 
	list<Move*>::iterator it; 
	for(it = p_move.begin(); it != p_move.end(); it++){//HERE!! may change the structure of "move" lists
		cout << i; 
		i++; 
		print_list(*it);		
		//print the move
		//need to indicate if it is a move after a move; how to display sub moves? 
	}
	//HERE!! how to get the *move_to_make move object

	int row = move_to_make ->get_curr_row(); 
	int col = move_to_make -> get_curr_col();
	return move_piece(player_piece, move_to_make, a_board, row, col);
	//here, this will move the piece: update player_piece and a_board

}


int main(void){

	char val;
	std::string input_color, new_input_color;
	cout << "Type 'A' for a new game or 'B' for a customizeable board"<<endl; 
	cin >> val;   

	Board board;
	board.set_dimensions(8,8); 
	board.init(); 	

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

	board.update_board(determine_move(player1, board.share_board(), 1));
	board.update_board(determine_move(player2, board.share_board(), 2)); 	

	//1. write a function for which player moves
	//function includes printing all moves for that player
	//2. after player determines which move it wants to make, update board, update the values in pieces

	//HERE!! ADD: 
	//ADD ENDGAME OPTIONS AFTER EACH PRINTBOARD
	//1. request draw 
	//2. restart (shows score)
	//3. quit (shows score)
	//4. watch me play on my own
	

	return 0; 
	
}
