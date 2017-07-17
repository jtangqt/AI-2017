#ifndef MOVE_HPP_
#define MOVE_HPP_

class Move{
	int curr_row, curr_col, new_row, new_col;//which move number is it? (mostly for user to give input)
	Move *next_move; 
	public:
		Move(int, int, int, int);
		void clear_val();
		Move *get_next();
		int get_curr_row();
		int get_curr_col();
		int get_next_row();
		int get_next_col(); 
};

#endif