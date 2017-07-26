#ifndef PIECE_HPP_
#define PIECE_HPP_

#include <string>
#include "move.hpp"
#include "deleted.hpp"


class Piece{
	//stores their positions 
	public: 
		Piece (std::string, int, int, int);
		void make_king();
		int get_row();
		int get_col();
		int get_player_num();
		bool is_king();
		void update_piece(Move *);
	private:
		int row, col; //
		bool isKing; // whether king or not
		float val; // for AI stuff
		int player_num;
		std::string color; 
};

#endif