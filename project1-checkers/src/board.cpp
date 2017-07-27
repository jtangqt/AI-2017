#include <iostream>
#include <board.hpp>
#include "colormod.h"

Color::Modifier m_red(Color::FG_RED);
Color::Modifier m_green(Color::FG_GREEN);
Color::Modifier m_def(Color::FG_DEFAULT);

Board::Board(int row, int col){  //sets dimension and initializes the board
	this -> row = row;
	this -> col = col; 
	arr = (int **)malloc(row*col * sizeof(int *));
	for(int i = 0; i<row; i++){
		arr[i] = (int*)malloc(col*sizeof(int));
	}
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

void Board::cust(int player_val, int piece_row, int piece_col){
	arr[piece_row][piece_col] = player_val; 
}

std::list<Piece> Board::norm(int player_num){
	list<Piece> norm_pieces;
	std::string color;

	int k;
	if (player_num == 1){
		k = 5;
		color = "RED";
	}
	if (player_num == 2){
		k = 0; 
		color = "GREEN";
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

void Board::update_board(int **arr){
	this -> arr = arr; 
}