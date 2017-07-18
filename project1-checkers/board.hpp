#ifndef BOARD_HPP_
#define BOARD_HPP_

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
	 	void update_board(); 
};

#endif	