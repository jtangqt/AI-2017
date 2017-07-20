#include <iostream>
#include <list>
#include "colormod.h"
#include "board.hpp"

using namespace std;

//player 1 and player 2
//player 1 - black unless starting in the middle of the game
//player 2 - red

Color::Modifier m_red(Color::FG_RED);
Color::Modifier m_green(Color::FG_GREEN);
Color::Modifier m_def(Color::FG_DEFAULT);


void Board::set_dimensions(int row, int col){
	this -> row = row;
	this -> col = col; 
}

void Board::init(){
	arr = new int*[row];
	for(int i = 0; i < row; ++i){
		arr[i] = new int [col];
	}
}

//void Board::add_piece(){}//HERE!!
//void Board::delete_piece(){}//HERE!!

typename std::list <Piece> Board::cust(std::string player_color, int player_num){ //HERE!! I need to set x's and y's inside piece object
	int i = 0; 
	std::string next, king; 
	std::list <Piece> player_pieces;
	while(i ==0){
		int input_row, input_col; 
		std::cout<<"Type row of " << player_color <<  " from 1-8 or 0 to quit. "; 
		std::cin >> input_row; 
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

	int k;
	if (player_num = 1){
		k = 5;
		color = "BLACK";
	}
	else{
		k = 0; 
		color = "RED";
	}

	for(int i = 0; i <row; i++){
		for(int j = 0; j< col; j++){
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

void Board::update_board(int **updated_arr){ memcpy(arr, updated_arr, 8*8*sizeof(int)); }

int **Board::share_board(){ return arr; }