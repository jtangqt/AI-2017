#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>

using namespace std; 

class Board{
	private:
		int **arr;
		int row, col;  
	public: 
		Board(int, int); //sets dimension
		void cust(int, int, int);
};


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

class Piece{
	//stores their positions 
	public: 
		Piece (std::string, int, int, int);
		void make_king();
	private:
		int row, col; //
		bool isKing; // whether king or not
		float val; // for AI stuff
		int player_num;
		std::string color; 
};

Piece::Piece(std::string color, int player_num, int row, int col){
	this -> color = color;
	this -> player_num = player_num;
	this -> row = row;
	this -> col = col; 
	isKing = false; 
	val = 1.0f; 
}

void Piece::make_king(){
	isKing = true; 
	val = 1.8f; 
}

int main (){

	Board board(8,8);

	ifstream file;
	file.open("input.txt");
	cout<<"hi"<<endl;

	int p_val, value, k = 0; 
	vector<int> temp_board; 
	list<Piece> player1;
	list<Piece> player2; 
	std::stringstream ss;

	while (file >> value) {
		ss<<value; 
		cout<<value;
		temp_board.push_back(value);
	}
		
	file.close(); 	

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			p_val = temp_board[k++];
			board.cust(p_val, i, j);
			if(p_val == 1){
				Piece piece("RED", p_val, i, j);
				player1.push_back(piece);
			}
			else if(p_val == 2){
				Piece piece("GREEN", p_val, i, j);
				player2.push_back(piece);
			}
			else if(p_val == 3){
				Piece piece("RED", p_val-2, i, j);
				piece.make_king(); 
				player1.push_back(piece);
			}
			else if(p_val == 4){
				Piece piece("GREEN", p_val-2, i, j);
				piece.make_king(); 
				player2.push_back(piece);	
			}
		}
	}
}
