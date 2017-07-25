#include <iostream>
#include <deleted.hpp>

Deleted::Deleted(int row, int col){
	this -> row = row;
	this -> col = col; 
	next_deleted = NULL; 
}

void Deleted::set_next(Deleted *next_deleted){
	this -> next_deleted = next_deleted;
}