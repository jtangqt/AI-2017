#include <iostream>
#include "colormod.h"


using namespace std;

//end game
//1. request draw 
//2. restart
//3. quit
//4. watch me play on my own

//player 1 and player 2
//player 1 - black unless starting in the middle of the game
//player 2 - red

//legal moves implementation

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
	for(int i = 0; i < row; ++i){
		arr[i] = new int [col];
	}
	return arr; 
}

int **Board::cust(string player_color, int player_num){
	int i = 0; 
	string next; 
	while(i < 1){
		int input_row, input_col; 
		cout<<"Type row of " << player_color <<  " from 1-8 or 0 to quit"<<endl; 
		cin >> input_row; 
		if (input_row == 0){
			i ++; //HERE!! what if they just want to quit and restart 
		}
		else if(0< input_row <= row){ //This is where they input the column
			cout<< "Type col of "<< player_color << " from 1-8"<< endl;
			cin>> input_col; 
			if((0<input_col<= col) && (((input_col+input_row)%2) == 0)){
				arr[input_row][input_col] = player_num; //HERE! how to declare player and add king 
				if(player_num == 1){ //if it is the first player to input, then we give the user the option to go to next player
					cout<< "Are you done? 'Y' for next player's positions and 'N' to continue"<<endl; 
				}
				else{
					cout << "Are you done? 'Y' to start the game, 'N' to continue" <<endl;
				}
				cin >> next; 
				if (next == "Y"){
					i ++; 
				}
			}
			else{
				cout<< "that's an invalid input, please try again" <<endl; 
			}
		}
		else{
			cout<< "that's an invalid input, please try again" <<endl; 
		}
	}
	return arr; 
}

int **Board::norm(){ //HERE!! didnt determine form of player yet
	//i want to find if they want to start with normal board 
	return arr; 
}

void Board::print_board(){

	for(int i = 0; i<row+1; i++){ 
		cout  <<"\n\n" <<i << "\t"; 
		for(int j = 0; j<col; j++){
			if (i == 0){
				cout <<j+1<<"\t"; 
			}
			else{
				cout<< arr[i-1][j] << "\t";
			}
		}
	}
	cout << endl; 
}

//ADD ENDGAME OPTIONS AFTER EACH PRINTBOARD

class Player{
	//stores their positions 
	int **arr;
	char color; //player red or black 
	void move_player(); 
	void move_king();  
	void start_position(); 
};



int main(void){


	char val;
	string input_color, new_input_color;
	cout << "Type 'A' for a new game or 'B' for a customizeable board"  << endl;
	cin >> val;  

	Board board;
	board.set_dimensions(8,8); 
	board.init(); 

	if(val == 'A'){
		board.norm();
	}
	else{
		cout << "'RED' or 'BLACK' starting first?"<<endl;
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


	return 0; 
	
}