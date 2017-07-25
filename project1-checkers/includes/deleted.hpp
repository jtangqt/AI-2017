#ifndef DELETED_HPP_
#define DELETED_HPP_

class Deleted{
	private:
		int row, col;  
		Deleted *next_deleted; 
	public: 
		Deleted(int, int);
		void set_next(Deleted *); 
};

#endif		