#include <iostream>
#include <board.hpp>


Board::Board(int row, int col){  //sets dimension and initializes the board
	this -> row = row;
	this -> col = col; 
	arr = (int **)malloc(row*col * sizeof(int *));
	for(int i = 0; i<row; i++){
		arr[i] = (int*)malloc(col*sizeof(int));
	}
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