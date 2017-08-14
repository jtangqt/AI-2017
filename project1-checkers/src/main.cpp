#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>

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

Tree determine_move(list<Tree> leaves){

	list<Tree>::iterator it; 
	list<Tree>::iterator select_leaf;
	int val, row, col, i = 0, j = 0; 

	cout<<"Which move would you like to make?"<<endl;;

	for(it = leaves.begin(); it != leaves.end(); it++){
		print_list(it -> share_move(), i);
		i++;
	}

	while(j == 0){
		cin>>val;
		if(val >= 0 && val < i){
			select_leaf = leaves.begin();
			advance(select_leaf, val); 
			j = 1;
		}
		else{
			cout<<"Invalid input, please try again."<<endl;
		}
	}

	return (*select_leaf); 
	
}

void determine_surrender(Tree &leaf){
	int win = leaf.evaluate_board(); 
	cout << "HAHAHA I HAVE DEFEATED YOU!!\n"<< win <<endl; 
	if (win > 0){
		cout << "At this current state, you would've lost by: " << win << ".\n"; 
	}
	else if (win == 0){
		cout << "At this current state, we are even in score.\n";
	}
	else{
		cout << "At this current state, you would've won by: " << win << ".\n";
	}
}

void determine_draw(Tree &leaf){
	int win = leaf.evaluate_board(); 
	if (win > 0){
		cout << "At this current state, you would've lost by: " << win << ".\n"; 
	}
	else if (win == 0){
		cout << "At this current state, we are even in score.\n";
	}
	else{
		cout << "At this current state, you would've won by: " << win << ".\n";
	}
}

int main(){
	
	char val; 
	int option, end_val, x = 0, input_val = 1, ai_val, time_limit;
	Move *move_to_make;
	list<Tree> branches;
	cout << "Type 'A' for a new game or 'B' for a customizeable board. "; 
	cin >> val;   

	Board board(8, 8);	

	std::list<Piece> player1;
	std::list<Piece> player2;

	if(val == 'A'){
		cout << "(0,0) is top-left corner; player 1 starts at the bottom of the board." <<endl; 
		player1 = board.norm(1);
		player2 = board.norm(2);
	}
	else{
		cout<< "1. Board is up vs. down \n2. Red is always on the bottom and always player 1.\n3. 1 - Player 1 (RED) \t 2 - Player 2 (GREEN) \t 3 - Player 1 King (RED) \t 4 - Player 2 King (GREEN)"<<endl; 

		ifstream file;
		file.open("input.txt");

		int p_val, value, k = 0; 
		vector<int> temp_board; 
		std::stringstream ss; 

		while (file >> value) {
			ss<<value; 
			cout<<value; //TODO stackdumps when trying to customize the board 
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

		cout << "Which player is starting first? (1/2)"; 
		cin >> input_val;
	}

	cout<<"\n\nWhich Player is the AI? (1/2/3 for both) "; //TODO
	cin>>ai_val;

	bool ai_player[2];

	if(ai_val == 1){
		ai_player[0] = true;
		ai_player[1] = false;
	}
	else if(ai_val == 2){
		ai_player[0] = false;
		ai_player[1] = true;
	}
	else{
		cout << "In this case, I will optimize for player 1.\n";
		ai_player[0] = true;
		ai_player[1] = true;
	}

	cout << "What is the time limit? ";
	cin >> time_limit;


	Tree leaf(board.share_board(), player1, player2, 1, NULL, ai_player, NULL); //TODO for share_board(); 

	cout << "BEWARE: after both player 1 and player 2 have had a chance to move, I will prompt you to see if you want to end/surrender/request for a draw. In this scenario, picking surrender/request for draw will give you a score, ending will not give you a score.\n";

	if(input_val == 2){
		leaf.print_board(); 
		branches = leaf.find_all_leaves(2);
		leaf = determine_move(branches);
	}

	while (x == 0){
		leaf.print_board(); 
		branches = leaf.find_all_leaves(1);
		leaf = determine_move(branches);
		branches.clear(); 
		
		leaf.print_board();
		branches = leaf.find_all_leaves(2);
		leaf = determine_move(branches);
		branches.clear(); 
		leaf.print_board();
		
		cout << "Would you like to end the game/see other options/continue? (1/2/3)"<<endl;
		cout << "If you want to see your score, go to other options. ";
		cin >> end_val;
		if (end_val == 1){
			x = 1; 
		}
		if(end_val == 2){
			cout << "What would you like to do? \n1. Request a draw\n2. Surrender ";
			cin >> option; 
			if (option == 1){	
				determine_draw(leaf); 
			}
			else if(option == 2){
	 			determine_surrender(leaf);
			}
		}

		
	}
	//TODO 
	//seg fault when jumping second time from a side space
}
