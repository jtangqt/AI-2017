#ifndef PIECE_HPP_
#define PIECE_HPP_

#include <string>

class Piece{
	//stores their positions 
	public: 
		Piece (std::string, int, int, int);
		void make_king();
		int get_row();
		int get_col();
		bool is_king();
	private:
		int row, col; //
		bool isKing; // whether king or not
		float val; // for AI stuff
};

#endif