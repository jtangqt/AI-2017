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

//legal moves implementation
//need to be able to print this out

//after legal moves implementation, make .h file for include

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

int **Board::cust(string player_color, int player_num){
	i = 0; 
	string next, king; //HERE!! make sure to add king
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


void Board::hyp_moves(int a, int b, int c){
	//no piece there (moves the piece)
	//your piece there (doesn't print anything)
	//other player piece there (eats the piece)
	x=arr[a][b];
	y = arr[a+1][b+1];
	z =arr[a+1][b-1];
	if((y == x+1) || (y== x-1) ||(z == x+1) || (z == x-1)){
		if((y == x+1) && (y== x-1) &&(z == x+1) && (z == x-1)){
			cout<< "Move piece #" <<c<<" at row " << a <<"and column " << b << "to row "<<a+2<<"and column "<<b-2<<endl;
			cout<< "Move piece #" <<c<<"  at row " << a <<"and column " << b << "to row "<<a+2<<"and column "<<b+2<<endl;
		}
		else if((z == x+1) || (z == x-1)){
			cout<< "Move piece #" <<c<<" at row " << a <<"and column " << b << "to row "<<a+2<<"and column "<<b-2<<endl; 
		}
		else(){
			cout<< "Move piece #"<<c<< " at row " << a <<"and column " << b << "to row "<<a+2<<"and column "<<b+2<<endl; 
		}
	}
	else if(y == NULL|| z== NULL){
		if((z == NULL) && (y== NULL)){
			cout<< "Move piece #" <<c<<" at row " << a <<"and column " << b << "to row "<<a+1<<"and column "<<b-1<<endl;
			cout<< "Move piece #" <<c<< " at row " << a <<"and column " << b << "to row "<<a+1<<"and column "<<b+1<<endl;
		}
		else if(z == NULL){
			cout<< "Move piece #"<<c<< " at row " << a <<"and column " << b << "to row "<<a+1<<"and column "<<b-1<<endl; 
		}
		else{
			cout<< "Move piece #" <<c<< " at row " << a <<"and column " << b << "to row "<<a+1<<"and column "<<b+1<<endl; 
		}
	}
}

Board::player_move(int x, int y){
	
}

// function determine and print all possible moves for the player
// 

//ADD ENDGAME OPTIONS AFTER EACH PRINTBOARD

class Piece{
	//stores their positions 
	int x; 
	int y; 
	public: 
		Piece(string, int);
		void set_val(int);
		void make_king();
		int position_x(){return(x)};
		int position_y(){return(y)}; 
	private:
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

int determine_move(int player_num){ 
//for all of the pieces for one player, determine all of the moves it can make
	int c; 
	for(i = 0; i< lengthof(); i++){//HERE!!
		int x = piece#.position_x();
		int y = piece#.position_y(); //HERE!!
		board.hyp_moves(x, y, #);//HERE!!
	}
	cout << "Which piece number do you want to move?" << endl; 
	cin >> c;
	return c;  
}

player_turn(int player_num){
	
	int c = determine_move(player_num); 

	piece#.position_x(); //HERE!! piece #c  
	piece#.position_y(); 
	
}

int main(void){

	char val;
	string input_color, new_input_color;
	cout << "Type 'A' for a new game or 'B' for a customizeable board (note: board is up vs. down, black is on the bottom and starts first unless you customize). "; 
	cin >> val;   

	Board board;
	board.set_dimensions(8,8); 
	board.init(); 
	// Player player1;
	// Player player2; 

	if(val == 'A'){
		board.norm();
		// player1.setvalues(BLACK, 1);
		// player2.setvalues(RED, 2);
	}
	else{
		cout << "'RED' or 'BLACK' starting first?. "; 
		cin >> input_color;
		board.cust(input_color, 1);
		if (input_color == "BLACK"){
			new_input_color = "RED";
			board.cust(new_input_color, 2);
		}
		else{
			new_input_color = "BLACK";
			board.cust(new_input_color, 2);
		}
	}
	board.print_board(); 

	//HERE!! ADD: 
	//end game
	//1. request draw 
	//2. restart (shows score)
	//3. quit (shows score)
	//4. watch me play on my own
	

	return 0; 
	
}
