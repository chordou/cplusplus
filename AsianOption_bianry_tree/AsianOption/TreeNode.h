#ifndef TREENODE_H
#define TREENODE_H

#include "TDATA.h"

class TreeNode
{
public:
	TDATA		data;
	TreeNode*	leftChild;
	TreeNode*	rightChild;
	TreeNode*	parent;
	int			level;

	TreeNode(double price)
		: leftChild(0), rightChild(0), parent(0) { data.sharePrice = price; }
};

#endif