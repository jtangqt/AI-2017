#ifndef MOVE_HPP_
#define MOVE_HPP_

using namespace std; 

class Move{
	int curr_row, curr_col, next_row, next_col;
	Move *next_move; 
	public:
		Move(int, int, int, int);
		void set_next(Move *); 
		int get_curr_row();
		int get_curr_col();
		int get_next_row();
		int get_next_col(); 
		Move *get_next();
		void clear_val();
};

#endif