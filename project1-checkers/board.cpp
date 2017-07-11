#include <iostream>
#include "colormod.h"


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
		int **cust(string, int);
		int **norm();
	 	int **init();
};

void Board::set_dimensions(int x, int y){
	row = x;
	col = y; 
}

int **Board::init(){
	arr = new int*[row];
	for(i = 0; i < row; ++i){
		arr[i] = new int [col];
	}
	return arr; 
}

void Board::add_piece(){}//HERE!!
void Board::delete_piece(){}//HERE!!

int **Board::cust(string player_color, int player_num){
	i = 0; 
	string next, king; 
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
			if((0<input_col) && (input_col<= col) && (((input_col+input_row)%2) == 0)){
				cout << "Type 'Y' if that piece is a king and 'N' if not. ";
				cin >> king; 
				if (king == "Y"){
					arr[input_row-1][input_col-1] = player_num+2;
				}
				else{
					arr[input_row-1][input_col-1] = player_num;
				}
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
	return arr; 
}

int **Board::norm(){
	
	//player 1 on the bottom (BLACK)
	//player 2 on top (RED)

	for(i = 0; i <row; i++){
		for(j = 0; j< col; j++){
			if ((i < 3) && (i+j)%2 == 0){
				arr[i][j] = 2; 
			}
			if((i > 4) && ((i+j)%2 == 0)){
				arr[i][j] = 1; 
			}
		}
	}

	return arr; 
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

class Move{
	int curr_x, curr_y, new_x, new_y, num;//num = where it is on the list
	Move *next_move; 
	public:
		void set_curr_x, set_curr_y, set_new_x, set_new_y, set_num;
};

void Move::set_val(int curr_x, int curr_y, int new_x, int new_y, int num){ 
	this -> curr_x;
	this -> curr_y;
	this -> new_x;
	this -> new_y;
	this -> num = num;
}

void Move::clear_val(){
	curr_x = curr_y = new_x = new_y = set_num = 0;
}


list<Move> Board::hyp_moves(int row, int col, int c, bool d){//HERE!! how to output few moves?
	//no piece there (moves the piece)
	//your piece there (doesn't print anything)
	//other player piece there (eats the piece)
	int x, y, z; 

	std::list<Move> move_pieces;

	x=arr[row][col]; 
	if(c = 1){
		i = row-1; 
		j = row -2; 
	}
	else{
		i = row+1; 
		j = row+2; 
	}
	y = arr[i][col+1];
	z =arr[i][col-1];
	k = 0;
	if((y == x+1) || (y== x-1) ||(z == x+1) || (z == x-1)){
		if((y == x+1) && (y== x-1) &&(z == x+1) && (z == x-1)){
			cout<< "Move piece #" <<c<<" at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col-2<<endl;
			cout<< "Move piece #" <<c<<"  at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col+2<<endl;
			Move eat_piece, eat_piece2;
			eat_piece.set_val(row, col, j, col-2, k);
			k++;
			eat_piece2.set_val(row, col, j, col+2, k);
			k++;
			move_pieces.push_back(move_pieces.end(), {eat_piece, eat_piece2});
		}
		else if((z == x+1) || (z == x-1)){
			cout<< "Move piece #" <<c<<" at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col-2<<endl; 
			Move eat_piece;
			eat_piece.set_val(row, col, j, col-2, k);
			move_pieces.push_back(eat_piece);
			k++;
		}
		else{
			cout<< "Move piece #"<<c<< " at row " << row <<"and column " << col << "to row "<<j<<"and column "<<col+2<<endl; 
			Move eat_piece;
			eat_piece.set_val(row, col, j, col+2, k);
			move_pieces.push_back(eat_piece);
			k++;
		}
	}
	if(y == NULL|| z== NULL){ //when the box diagonal is empty
		if((z == NULL) && (y== NULL)){
			cout<< "Move piece #" <<c<<" at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col-1<<endl;
			cout<< "Move piece #" <<c<< " at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col+1<<endl;
			Move move_piece, move_piece2;
			move_piece.set_val(row, col, j, col-1, k);
			k++;
			move_piece2.set_val(row, col, j, col+1, k);
			k++;			
			move_pieces.push_back(move_pieces.end(), {move_piece, move_piece2});
		}
		else if(z == NULL){
			cout<< "Move piece #"<<c<< " at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col-1<<endl; 
			Move move_piece;
			move_piece.set_val(row, col, j, col-1, k);
			k++;
			move_pieces.push_back(move_piece);
		}
		else{
			cout<< "Move piece #" <<c<< " at row " << row <<"and column " << col << "to row "<<i<<"and column "<<col+1<<endl; 
			Move move_piece;
			move_piece.set_val(row, col, j, col+1, k);
			k++;
			move_pieces.push_back(move_piece);
		}
	}
	//HERE!! check for wall 
	return move_pieces;
}

void Board::player_move(int a, int b){
	int x, int y, int z; 

	x=arr[a][b];
	y = arr[a+1][b+1];
	z =arr[a+1][b-1];
	
}

class Piece{
	//stores their positions 
	public: 
		Piece(string, int);
		void set_val(int);
		void make_king();
		void set_x(int);
		void set_y(int);
		int get_x();
		int get_y();
	private:
		int x, y;
		string color; //player red or black 
		int num; //player 1 or player 2
		bool isKing; // whether king or not
		float val; // for AI stuff
};

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

int determine_move(int player_num, list<Piece> & pieces){ //HERE!!
//for all of the pieces for one player, determine all of the moves it can make
	int c; 
	std::list<Move> move; 
	std::list<Move> move_pieces; 
	for(i = 0; i< pieces.size(); i++){
		int x = pieces[i].get_x();
		int y = pieces[i].get_y(); 
		
		if(pieces[i].isKing == true){
			j =1;
		}
		else{
			j = 0; 
		}

		move_pieces = board.hyp_moves(x, y, player_num, j);//HERE!! what kind of function do i need to return a move object?
		move.splice(move.end(), move_pieces); 
		}
	}
	cout << "Which move do you want to make?" << endl; //HERE!! continue on 
}

void customize_board(Board object, list<Piece> &player1, list<Piece> &player2){

	string input_color, new_input_color;

	cout<< "1. Board is up vs. down \n2. Black is on the bottom and starts first unless you customize\n3. First player must always be on the bottom side of the board"<<endl; 
	cout << "'RED' or 'BLACK' starting first?. "; 
	cin >> input_color;
	
	board.cust(input_color, 1);
	
	if (input_color == "BLACK"){
		new_input_color = "RED";
		board.cust(new_input_color, 2);//HERE! create individual pieces in player
	}
	else{
		new_input_color = "BLACK";
		board.cust(new_input_color, 2);
	}
}

void normal_board(Board object, list<Piece> &player1, list<Piece> &player2){
	board.norm();
	// player1.setvalues(BLACK, 1); HERE!! Create objects 
	// player2.setvalues(RED, 2);
}

int main(void){

	char val;
	cout << "Type 'A' for a new game or 'B' for a customizeable board"<<endl; 
	cin >> val;   

	Board board;
	board.set_dimensions(8,8); 
	board.init(); 	

	std::list<Piece> player1;
	std::list<Piece> player2;

	if(val == 'A'){
		normal_board(board, player1, player2);
	}
	else{
		customize_board(board, player1, player2); 
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
