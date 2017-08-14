#ifndef DEPTH_HPP_
#define DEPTH_HPP_

#include <iostream>
#include "tree.hpp"

class Depth{
	private:
		int depth, alpha, beta; 
		list<Tree> branches;
		Depth *next_depth; 
		int p_num; //indicates whose move it is
	public:
		Depth(int, list<Tree>);
		Depth *get_next();
		void set_next(Depth *);
		list<Tree> share_branches(); 
		Depth *delete_branch(Tree &, Depth);
		void iterative_deepening(list<Tree>, int, int);
}

Depth::Depth(int depth, list<Tree> branches){
	this -> depth = depth;
	this -> branches = branches; 
}

void Depth::set_next(Depth *next_depth){
	this -> next_depth = next_depth;
}

list<Tree> Depth::share_branches(){ return branches; }
int Depth::share_p_num(){ return p_num; }

Depth *Depth::delete_branch(Tree &leaf){//these branches indicate the  move that goes to the leaf (so previous node)
	int i = 1; 
	list<Tree> new_branches, branches, delete_branches;
	branches = this -> share_branches() //TODO returns list of branches of that depth
	Depth *updated_depth; 

	while(depth){
		if (i == 1){//TODO
			new_branches.push_back(leaf);
		}
		new_branches = get_all_branches(new_branches);
		Depth *new_depth = new depth(i, new_branches);
		updated_depth -> set_next(new_depth);//TODO

		branches = depth.share_branches(); //TODO
		delete_branches.splice(delete_branches.begin(), branches); 
		depth -> get_next(); //TODO
		i++;
	}
	delete_branches.clear(); 

	return updated_depth;
}

void Depth::iterative_deepening(list<Tree> branches, int p_num, int depth){ //the first branch has only one leaf (this belongs to player1)
	list<Tree>::iterator it; 
	list<Tree> new_branches, leaves; 
	Depth *entire_depth; 
	int new_p_num; 

	this -> depth = depth; 

	if(p_num == 1){
		new_p_num = 2; 
	}
	if(p_num == 2){
		new_p_num = 1; 
	}

	for(it = branches.begin(); it != branches.end(); it++){
		leaves = find_all_leaves(p_num);
		new_branches.splice(new_branches.begin(), leaves);
	}
	Depth *new_depth = new depth(depth, new_branches); 
	branches.set_next(new_depth);
	iterative_deepening(new_branches, new_p_num, depth+1);
}

#endif