#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <list>
#include <cstring>
#include "piece.hpp"

class Board{
	private:
		int **arr;
		int row, col;  
	public: 
		Board(int, int); //sets dimension
		void cust(int, int, int);
		std::list<Piece> norm(int);
	 	int **share_board(); 
};

#endif	
