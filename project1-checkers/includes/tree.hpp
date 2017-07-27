#ifndef TREE_HPP_
#define TREE_HPP_

#include <list>
#include "board.hpp"

using namespace std; 

class Tree{
	private:
		int **arr;
		int row = 8, col = 8; 
 		std::list<Tree> leaf;
 		std::list<Piece> player1;
 		std::list<Piece> player2;  
	public: 
		Tree(int**, std::list<Piece>, std::list<Piece>);
		std::list<Move*> get_all_possible_moves(std::list <Piece>);
		std::list<Move*> get_possible_jumps(int**, int, int, int, bool); 
		std::list<Piece> move_player_piece(list<Piece>, Move *); //this makes a move by updating the piece and returning the list of players
		std::list<Piece> move_b_del_p(list<Piece>, Move *); //this updates the board and returns list of pieces (deleted ones are deleted)
		int **share_board(); //this shares the board so that we can save it into the object
		std::list<Deleted> make_temp_board(Move *); //TODO
};

#endif		