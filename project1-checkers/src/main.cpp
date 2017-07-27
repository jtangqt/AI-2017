#include <iostream>
#include <list>
#include <fstream>
#include <vector>

#include "board.hpp"
#include "tree.hpp"


using namespace std; 

void print_list(Move* move_from_list, int i){

	Move *current = move_from_list;
	cout <<i<< ": ";
	cout << "(" << current->get_curr_row() << "," << current -> get_curr_col() << ")";
	while(current != NULL){
		cout << "->";
		cout << "(" << current->get_next_row() << "," << current -> get_next_col() << ")"; 
		current = current ->get_next(); 
	}
	cout << endl;

}

Move *determine_move(Tree &leaf, list<Piece> y_turn){

	list<Move *> p_move; 
	list<Move*>::iterator move_to_make; 
	list<Move *>::iterator it; 
	int val, row, col, i = 0, j = 0; 

	cout<<"Which move would you like to make?"<<endl;;

	for(it = p_move.begin(); it != p_move.end(); it++){
		print_list(*it, i);
		i++;
	}

	while(j ==0){
		cin>>val;
		if(val >= 0 && val < i){
			move_to_make = p_move.begin();
			advance(move_to_make, val); 
			j = 1;
		}
		else{
			cout<<"Invalid input, please try again."<<endl;
		}
	}

	return (*move_to_make); 
	
}

int main(){
	
	char val, end_val; 
	int x = 0, input_val = 1; 
	int time = 0; 
	Move *move_to_make;
	cout << "Type 'A' for a new game or 'B' for a customizeable board. "; 
	cin >> val;   

	Board board(8, 8);	

	std::list<Piece> player1;
	std::list<Piece> player2;

	if(val == 'A'){
		cout << "(0,0) is top-left corner; player 1 starts at the bottom of the board." <<endl; 
		player1 = board.norm(1);
		player2 = board.norm(2);
		board.print_board(); 
	}
	else{
		cout<< "1. Board is up vs. down \n2. Red is always on the bottom and always player 1.\n3. 1 - Player 1 (RED) \t 2 - Player 2 (GREEN) \t 3 - Player 1 King (RED) \t 4 - Player 2 King (GREEN)"<<endl; 

		ifstream file;
		file.open("../input.txt");

		int p_val, value, k = 0; 
		vector<int> temp_board; 

		while (file >> value) {
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

		board.print_board(); 

		cout << "Player '1' or '2' starting first?. "; 
		cin >> input_val;
	}

	Tree leaf(board.share_board(), player1, player2);
		
	if(input_val == 2){
		move_to_make = determine_move(leaf, player2);
		board.update_board(leaf.share_board());
		player2 = leaf.move_player_piece(player2, move_to_make);
		player1 = leaf.move_b_del_p(player1, move_to_make);
		board.print_board(); 
	}

	while (x == 0){
		move_to_make = determine_move(leaf, player1);
		board.update_board(leaf.share_board());
		player1 = leaf.move_player_piece(player1, move_to_make);
		player2 = leaf.move_b_del_p(player2, move_to_make);
		board.print_board();

		move_to_make = determine_move(leaf, player2);
		board.update_board(leaf.share_board());
		player2 = leaf.move_player_piece(player2, move_to_make);
		player1 = leaf.move_b_del_p(player1, move_to_make);
		board.print_board();
		
		cout << "Would you like to end the game?"<<endl;
		cin >> end_val;
		if (end_val == 'Y'){
			x = 1; 
		}
	}

	//TODO 
	//seg fault when jumping second time from a side space
}
