#include <iostream>
#include <deleted.hpp>

Deleted::Deleted(int row, int col){
	this -> row = row;
	this -> col = col; 
}

int Deleted::get_row(){ return row; }
int Deleted::get_col(){ return col; }