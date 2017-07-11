#ifndef PIECE_HPP_
#define PIECE_HPP_

class Piece{
	//stores their positions 
	public: 
		Piece(string, int);
		void set_val(int);
		void make_king();
		void set_row(int);
		void set_col(int);
		int get_row();
		int get_col();
	private:
		int row, col; //
		string color; //player red or black 
		int num; //player 1 or player 2
		bool isKing; // whether king or not
		float val; // for AI stuff
};

#endif