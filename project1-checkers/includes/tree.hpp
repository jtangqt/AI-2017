#ifndef TREE_HPP_
#define TREE_HPP_

#include <list>
#include "board.hpp"

using namespace std; 

class Tree{
	private:
		int **arr;
		int row = 8, col = 8; 
		Move *move_to_make;
 		std::list<Tree> branches;
 		std::list<Piece> player1;
 		std::list<Piece> player2; 
 		int time_limit; 
 		bool *ai_player; 
	public: 
		/*Constructor*/
		Tree(int**, std::list<Piece>, std::list<Piece>, int, Move *, bool[2]);
		
		/* Gets all possible moves and jumps */
		std::list<Move*> get_all_possible_moves(std::list <Piece>);
		std::list<Move*> get_possible_jumps(int**, int, int, int, bool); 
		
		/*Moves y_turn, n_turn and the board*/
		std::list<Piece> move_player_piece(std::list<Piece>, Move *); //this makes a move by updating the piece and returning the list of players
		std::list<Deleted> update_and_delete(std::list<Piece>); 
		std::list<Piece> delete_player(std::list<Piece>, std::list<Deleted>);
		void update_player(std::list<Piece>, std::list<Piece>, int);
		
		/*Finds all trees*/
		std::list<Tree> find_all_leaves(int);
		Tree *create_new(int**, std::list<Piece>, std::list<Piece>, int, Move*);	
		
		/*Shares the information in the leaf*/
		void print_board(); 	
		Move *share_move();
		int **share_board(); //this shares the board so that we can save it into the object
		std::list<Tree> share_branches(); 

		/*AI Portion*/
		int evaluate_board(); //takes in the arr/player and determines the score (can be simple)
		void update_ai(bool[2]); 
		void iterative_deepening(std::list<Tree>); 
};

#endif		