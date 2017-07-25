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
		void print_board(); 
		std::list<Piece> cust(std::string, int);
		std::list<Piece> norm(int);
	 	int **share_board(); 
	 	std::list<Deleted> update_board(Move *); 
};

#endif	
