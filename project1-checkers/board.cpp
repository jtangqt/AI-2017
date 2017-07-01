#include <iostream>

using namespace std;

int **initialize_board(int sizeX, int sizeY){
	int **arr = new int*[sizeX];
	for(int i = 0; i < sizeX; ++i){
		arr[i] = new int [sizeY];
	}
	return arr; 
}

int **determine_board(){
	//i want to find if they want to start with normal board or start with different board
	char val; 
	cout << "Type 'normal' if you want to start a new game or type 'cust' to customize the board"<< endl; 
	cin >> val; 
	// if(val = "normal"){

	// }
	// else(val = "cust"){

	// }
}

void print_board(int x, int y, int **arr){
	for(int i = 0; i<x+1; i++){ 
		cout  <<"\n\n" <<i << "\t"; 
		for(int j = 0; j<y; j++){
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

	int x= 8, y=8; 
	int **board = initialize_board(x, y);

	print_board(x, y, board);

	return 0; 
}