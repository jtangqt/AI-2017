#ifndef MOVE_HPP_
#define MOVE_HPP_

class Move{
	int curr_x, curr_y, new_x, new_y, num;//num = where it is on the list
	Move *next_move; 
	public:
		Move(int, int, int, int, int);
};

#endif