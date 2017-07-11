#ifndef PIECE_HPP_
#define PIECE_HPP_

class Piece{
	//stores their positions 
	public: 
		Piece(string, int);
		void set_val(int);
		void make_king();
		void set_x(int);
		void set_y(int);
		int get_x();
		int get_y();
	private:
		int x, y;
		string color; //player red or black 
		int num; //player 1 or player 2
		bool isKing; // whether king or not
		float val; // for AI stuff
};

#endif