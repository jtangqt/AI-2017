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
		void set_dimensions(int, int); 
		void print_board(); 
		std::list<Piece> cust(std::string, int);
		std::list<Piece> norm(int);
	 	void init();
	 	int **share_board(); 
	 	void update_board(int **); 
};

#endif	
