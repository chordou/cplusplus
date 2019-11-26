#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

class Tree  //similar like linked-list
{
public:
	TreeNode*	root;

	Tree():	root(0), nLevel(0) {};
	void setLevel(int n) { nLevel = n; }
	int getLevel() { return nLevel; }

private:
	int		nLevel;

};

#endif