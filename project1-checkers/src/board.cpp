#include <iostream>
#include <board.hpp>
#include "colormod.h"

Color::Modifier m_red(Color::FG_RED);
Color::Modifier m_green(Color::FG_GREEN);
Color::Modifier m_def(Color::FG_DEFAULT);

Board::Board(int row, int col){  //sets dimension and initializes the board
	this -> row = row;
	this -> col = col; 
	arr = (int **)malloc(row * col * sizeof(int *));
}

void Board::print_board(){
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

std::list<Piece> Board::cust(std::string player_color, int player_num){
	int i = 0; 
	std::string next, king; 
	std::list <Piece> cust_pieces;
	
	while(i ==0){
		int input_row, input_col; 
		std::cout<<"Type row of " << player_color <<  " from 1-8 or 0 to quit. "; 
		std::cin >> input_row; 
		
		if (input_row == 0){
			i++; //HERE!! what if they just want to quit and restart 
			cust_pieces.clear(); 
		}
		else if((0< input_row) && (input_row<= row)){ 
			cout<< "Type col of "<< player_color << " from 0-7. ";
			cin>> input_col; 
			Piece piece(player_color, player_num, input_row, input_col); 

			/* input col is > 0 and <= 7; input col + input row is divisible by 2; there is no other value in the spot */
			if((0<input_col) && (input_col<= col) && (((input_col+input_row)%2) == 0 && arr[input_row][input_col] == 0)){
				cout << "Type 'Y' if that piece is a king and 'N' if not. ";
				cin >> king; 
				
				if (king == "Y"){
					arr[input_row][input_col] = player_num+2;
					piece.make_king();
				}
				else{
					arr[input_row][input_col] = player_num;
				}
				cust_pieces.push_back(piece);
				
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
	return cust_pieces; 
}

std::list<Piece> Board::norm(int player_num){
	list<Piece> norm_pieces;
	std::string color;

	int k;
	if (player_num == 1){
		k = 5;
		color = "BLACK";
	}
	if (player_num == 2){
		k = 0; 
		color = "RED";
	}

	for(int i = 0; i <row; i++){
		for(int j = 0; j< col; j++){
			if ((k <= i) && (i <= k+2) && ((i+j)%2 == 0)){ 
				arr[i][j] = player_num;
				Piece normal_pieces(color, player_num, i, j);//HERE!!
				norm_pieces.push_back(normal_pieces);
			}
		}
	}
	return norm_pieces; 
}

int **Board::share_board(){
	int **dest = (int**)malloc(row*col*sizeof(int));
	memcpy(dest, arr, row*col*sizeof(int));
	return dest; 
}

Deleted *Board::update_board(Move *move_to_make){
	//TODO
}