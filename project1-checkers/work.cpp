#include <iostream>

using namespace std;


class Board {
	private:
		int row, col;
	public: 
		int **arr;
		void set_dimensions(int, int);
		void print_board();
		int ** init();
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

int main(){

	Board board;
	board.set_dimensions(8, 8);
	board.init();
	board.print_board(); 
	
}