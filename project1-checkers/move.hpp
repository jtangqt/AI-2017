#ifndef MOVE_HPP_
#define MOVE_HPP_

class Move{
	int curr_x, curr_y, new_x, new_y, num;//num = where it is on the list
	Move *next_move; 
	public:
		void set_curr_x, set_curr_y, set_new_x, set_new_y, set_num;
};

#endif