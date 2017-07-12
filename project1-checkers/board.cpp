#include <iostream>
#include <string> 
#include <list>
#include "colormod.h"
#include "piece.hpp"
#include "move.hpp"


using namespace std;

Color::Modifier m_red(Color::FG_RED);
Color::Modifier m_green(Color::FG_GREEN);
Color::Modifier m_def(Color::FG_DEFAULT);
int i, j, k; 

//player 1 and player 2
//player 1 - black unless starting in the middle of the game
//player 2 - red


class Board{
	private:
		int **arr;
		int row, col;  
	public: 
		void set_dimensions(int, int); 
		void print_board(); 
		std::list<Piece> cust(std::string, int);
		std::list<Piece> norm(int);
	 	void init();
	 	std::list<Move> hyp_moves(int, int, int, bool);
};

void Board::set_dimensions(int row, int col){
	this -> row = row;
	this -> col = col; 
}

void Board::init(){
	arr = new int*[row];
	for(i = 0; i < row; ++i){
		arr[i] = new int [col];
	}
}

//void Board::add_piece(){}//HERE!!
//void Board::delete_piece(){}//HERE!!

std::list <Piece> Board::cust(std::string player_color, int player_num){ //HERE!! I need to set x's and y's inside piece object
	i = 0; 
	std::string next, king; 
	std::list <Piece> player_pieces;
	while(i ==0){
		int input_row, input_col; 
		cout<<"Type row of " << player_color <<  " from 1-8 or 0 to quit. "; 
		cin >> input_row; 
		if (input_row == 0){
			i++; //HERE!! what if they just want to quit and restart 
		}
		else if(0< input_row <= row){ //This is where they input the column
			cout<< "Type col of "<< player_color << " from 1-8. ";
			cin>> input_col; 
			Piece piece(player_color, player_num, input_row, input_col); 
			if((0<input_col) && (input_col<= col) && (((input_col+input_row)%2) == 0)){
				cout << "Type 'Y' if that piece is a king and 'N' if not. ";
				cin >> king; 
				if (king == "Y"){
					arr[input_row-1][input_col-1] = player_num+2;
					piece.make_king();
				}
				else{
					arr[input_row-1][input_col-1] = player_num;
				}
				player_pieces.push_back(piece);
				if(player_num == 1){ //if it is the first player to input, then we give the user the option to go to next player
					cout<< "Are you done? 'Y' for next player's positions and 'N' to continue. "; 
				}
				else{
					cout << "Are you done? 'Y' to start the game, 'N' to continue. " ;
				}
				cin >> next; 
				if (next == "Y"){
					i ++; 
				}
			}
			else{
				cout<< "that's an invalid input, please try again. " <<endl; 
			}
		}
		else{
			cout<< "that's an invalid input, please try again. " <<endl; 
		}
	}
}

std::list<Piece> Board::norm(int player_num){
	
	//player 1 on the bottom (BLACK)
	//player 2 on top (RED)
	list<Piece> norm_pieces;
	std::string color;

	if (player_num = 1){
		k = 5;
		color = "BLACK";
	}
	else{
		k = 0; 
		color = "RED";
	}

	for(i = 0; i <row; i++){
		for(j = 0; j< col; j++){
			if ((k <= i <= k+2) && (i+j)%2 == 0){
				arr[i][j] = player_num;
				Piece normal_pieces(color, player_num, i, j);//HERE!!
				norm_pieces.push_back(normal_pieces);
			}
		}
	}
	return norm_pieces; 
}

void Board::print_board(){

	cout << "_________________" << endl;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
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

/** Pass in list of pieces for a player **/
list<Move> get_all_possible_moves(list<Piece> l_pieces, int a_board[][], int p_num){
	list<Move> pos_moves = new list<Pieces>();

	list<Piece>::iterator it;
	for(it = l_pieces.begin(); it != l_pieces.end(); it++){
		list<Move> pos_jumps = get_possible_jumps(a_board, it->get_col(), it->get_row(), it->is_king(), p_num);
		if(pos_jumps.empty()){
			// Cannot jump, can only make a single move
			if((it->is_king() || p_num == 1) && a_board[y-1][x-1] == 0){
				Move m = new Move(x, y, x-1, y-1, 0);
				pos_moves.push_back(m);
			}
			if((it->is_king() || p_num == 1) && a_board[y-1][x+1] == 0){
				Move m = new Move(x, y, x+1, y-1, 0);
				pos_moves.push_back(m);
			}
			if((it->is_king() || p_num == 2) && a_board[y+1][x-1] == 0){
				Move m = new Move(x, y, x-1, y+1, 0);
				pos_moves.push_back(m);
			}
			if((it->is_king() || p_num == 2) && a_board[y+1][x+1] == 0){
				Move m = new Move(x, y, x+1, y+1, 0);
				pos_moves.push_back(m);
			}
		}else{
			pos_moves.merge(pos_jumps);
		}
	}
}

list<Move> get_possible_jumps(int a_board[][], int x, int y, bool is_king, int p_num){
	list<Move> pos_jumps = new list<Move>();
	int temp_board[8][8];
	list<Move>::iterator it;

	if((it->is_king() || p_num == 1) && a_board[y-1][x-1] % 2 == 0){ // If player 2 piece is there (even)
		if(a_board[y-2][x-2] == 0){	// Can jump
			copy(a_board, a_board+8*8, temp_board); // Copy board
			temp_board[y-2][x-2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y-1][x-1] = 0;
		
			/** Recursion **/
			list<Move> sub_jumps = get_possible_jumps(temp_board, x-2, y-2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move j = new Move(x, y, x-2, y-2, 0);
				j.set_next(it)
				pos_jumps.push_back(j);
			}
		}
	}
	if((it->is_king() || p_num == 1) && a_board[y-1][x+1] % 2 == 0){ // If player 2 piece is there (even)
		if(a_board[y-2][x+2] == 0){	// Can jump
			copy(a_board, a_board+8*8, temp_board); // Copy board
			temp_board[y-2][x+2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y-1][x+1] = 0;
		
			/** Recursion **/
			list<Move> sub_jumps = get_possible_jumps(temp_board, x+2, y-2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move j = new Move(x, y, x+2, y-2, 0);
				j.set_next(it)
				pos_jumps.push_back(j);
			}
		}
	}
	if((it->is_king() || p_num == 2) && (a_board[y+1][x-1] % 2 == 0)){ // If king and player 2 piece is there (even)
		if(a_board[y+2][x-2] == 0){	// Can jump
			copy(a_board, a_board+8*8, temp_board); // Copy board
			temp_board[y+2][x-2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y+1][x-1] = 0;
		
			/** Recursion **/
			list<Move> sub_jumps = get_possible_jumps(temp_board, x-2, y+2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move j = new Move(x, y, x-2, y+2, 0);
					j.set_next(it)
				pos_jumps.push_back(j);
			}
		}
	}
	if((it->is_king() || p_num == 2) && (a_board[y+1][x+1] % 2 == 0)){ // If king and player 2 piece is there (even)
		if(a_board[y+2][x+2] == 0){	// Can jump
			copy(a_board, a_board+8*8, temp_board); // Copy board
			temp_board[y+2][x+2] = temp_board[y][x]; // Update board
			temp_board[y][x] = 0;
			temp_board[y+1][x+1] = 0;
		
			/** Recursion **/
			list<Move> sub_jumps = get_possible_jumps(temp_board, x+2, y+2, is_king, p_num);
			for(it = sub_jumps.begin(); it != sub_jumps.end(); it++){
				Move j = new Move(x, y, x+2, y+2, 0);
				j.set_next(it)
				pos_jumps.push_back(j);
			}
		}
	}
	return pos_jumps;
}

std::list<Move> Board::hyp_moves(int row, int col, int c, bool d){
	//no piece there (moves the piece)
	//your piece there (doesn't print anything)
	//other player piece there (eats the piece)
	int x, y, z, b; 

	std::list<Move> move_pieces;

	x=arr[row][col]; 
	if(c == 1){
		i = row-1; 
		j = row-2; 
		b = 2;
	}
	else{
		i = row+1; 
		j = row+2; 
		b = 1; 
	}

	y = arr[i][col+1];
	z = arr[i][col-1];
	k = 0; //if there is a piece that is of the opp color, it has to take that move
	if((y == x+1) || (y== x-1) ||(z == x+1) || (z == x-1)){
		if(((y == x+1) || (y== x-1)) &&((z == x+1) || (z == x-1))){
			cout<< "Move piece #" <<c<<" at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col-2<<endl;
			cout<< "Move piece #" <<c<<"  at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col+2<<endl;
			Move eat_piece(row, col, j, col-2, k);
			k++;
			Move eat_piece2(row, col, j, col+2, k);
			k++;
			move_pieces.push_back(eat_piece);
			move_pieces.push_back(eat_piece2);
		}
		else if((z == x+1) || (z == x-1)){
			cout<< "Move piece #" <<c<<" at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col-2<<endl; 
			Move eat_piece(row, col, j, col-2, k);
			move_pieces.push_back(eat_piece);
			k++;
		}
		else{
			cout<< "Move piece #"<<c<< " at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col+2<<endl; 
			Move eat_piece(row, col, j, col+2, k);
			move_pieces.push_back(eat_piece);
			k++;
		}
	}
	if(y == 0|| z== 0){ //when the box diagonal is empty
		if((z == 0) && (y== 0)){
			cout<< "Move piece #" <<c<<" at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col-1<<endl;
			cout<< "Move piece #" <<c<< " at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col+1<<endl;
			Move move_piece(row, col, j, col-1, k);
			k++;
			Move move_piece2(row, col, j, col+1, k);
			k++;			
			move_pieces.push_back(move_piece);
			move_pieces.push_back(move_piece2);
		}
		else if(z == 0){
			cout<< "Move piece #"<<c<< " at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col-1<<endl; 
			Move move_piece(row, col, j, col-1, k);
			k++;
			move_pieces.push_back(move_piece);
		}
		else{
			cout<< "Move piece #" <<c<< " at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col+1<<endl; 
			Move move_piece(row, col, j, col+1, k);
			k++;
			move_pieces.push_back(move_piece);
		}
	}

	if(d = 1){
		std::list<Move> move_king; 
		move_king = this -> hyp_moves(row, col, b, 0);
		move_pieces.push_back(move_king);
	}
	//HERE!! check for wall 
	return move_pieces;
}

// void Board::player_move(int a, int b){
// 	int x, int y, int z; 

// 	x=arr[a][b];
// 	y = arr[a+1][b+1];
// 	z =arr[a+1][b-1];
	
// }

int determine_move(int player_num, list<Piece> & pieces, Board board){ //HERE!!
//for all of the pieces for one player, determine all of the moves it can make
	int c; 
	std::list<Move> move; 
	std::list<Move> move_pieces; 

	list<Piece>::iterator it = pieces.begin(); 
	for(i = 0; i< pieces.size(); i++){
		++it; 

		int row = (*it).get_row();
		int col = (*it).get_col(); 
		
		if((*it).get_king() == true){
			j =1;
		}
		else{
			j = 0; 
		}

		move_pieces = board.hyp_moves(row, col, player_num, j);
		move.splice(move.end(), move_pieces); 
	}
	
	cout << "Which move do you want to make?" << endl; //HERE!! continue on 
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

	//HERE!! ADD: 
	//ADD ENDGAME OPTIONS AFTER EACH PRINTBOARD
	//1. request draw 
	//2. restart (shows score)
	//3. quit (shows score)
	//4. watch me play on my own
	

	return 0; 
	
}