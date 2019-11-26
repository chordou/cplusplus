#include "BinomialPrice.h"
#include <math.h>
#include <iostream>

using namespace std;

int leftcount=0;
int initnFromLeafNode = 0;
int timetoend = 0;

BinomialPrice::BinomialPrice(AsianOption* pOpt, int nSteps, 
		PathFunc pathFunc, PayOffFunc payF)
		: option(pOpt), steps(nSteps), pathF(pathFunc), payOffF(payF)
{
	tree = new Tree();
	dt = option->maturity / nSteps;
	u = exp(option->vol * sqrt(dt));
	d = 1/u;
	pu = (exp(option->rate * dt) - d) / (u - d);
	pd = 1.0 - pu;
	discount = exp(-option->rate * dt);
};

void
BinomialPrice::buildTree(TreeNode* t, int nFromLeafNode)
{
/*        Pseudo Code for buildTree              //making the tree smaller and smaller, to make it stop
        If tree is empty (t==0)
                Create root node
                Fill in data for root node
        EndIf
        If height of tree > 0 (nFromLeafNode > 0)
                Create leftChild node
                Fill in data for leftChild node
                build left sub-tree (Call buildTree recursively)
                Create rightChild node
                Fill in data for rightChild node
                build right sub-tree (Call buildTree recursively)
        EndIf
*/

//TODO
	if (timetoend == 1)
		return;
	if (t == 0) {
		initnFromLeafNode = nFromLeafNode;
		tree->root = new TreeNode(option->spotPrice);
		tree->root->level = 0;
		tree->root->data.pathData = (*pathF)(option->spotPrice, tree->root->level, option->spotPrice);
		

		leftcount = nFromLeafNode-1;
		buildTree(tree->root, steps);
		if (timetoend == 1)
			return;
		
	}

	else {
		if (nFromLeafNode > 0 & t->leftChild ==NULL) {
			double ls = 0;
			ls = u * t->data.sharePrice;

			t->leftChild = new TreeNode(ls);
			t->leftChild->parent = t;
			t->leftChild->level = t->level + 1;
		
			t->leftChild->data.pathData = (*pathF)(t->data.pathData, t->leftChild->level, t->leftChild->data.sharePrice);
			buildTree(t->leftChild, nFromLeafNode - 1);
			if (timetoend == 1)
				return;
		}
		t = t->parent;
		while (t->leftChild != NULL & t->rightChild != NULL) {
			if (t == tree->root)
			{
				timetoend = 1;
				return;
			}
			t = t->parent;
		}
		double rs = 0;
		rs = d * t->data.sharePrice;
		t->rightChild = new TreeNode(rs);
		t->rightChild->parent = t;
		t->rightChild->level = t->level + 1;
		t->rightChild->data.pathData = (*pathF)(t->data.pathData, t->rightChild->level, t->rightChild->data.sharePrice);
		buildTree(t->rightChild, initnFromLeafNode - t->level-1);
		if (timetoend == 1)
			return;
		//cout << 1 << endl;
	}


}

int ggleft = 0;
int ggright = 0;


void
BinomialPrice::backwardEval(TreeNode* t)
{
	if (t->leftChild != NULL && t->rightChild != NULL){
		backwardEval(t->leftChild);
		ggleft = t->leftChild->data.optionPrice;
		backwardEval(t->rightChild);
		ggright = t->rightChild->data.optionPrice;
		t->data.optionPrice = (t->leftChild->data.optionPrice * pu + t->rightChild->data.optionPrice * pd) * discount;
	}
	else {
		t->data.optionPrice = (*payOffF)(t->data.pathData, t->data.sharePrice, option->strikePrice, option->c_p);
	}
}

void BinomialPrice::printTree(TreeNode* node) {
//TODO    <10 lines
	if (node) {
		printTree(node->leftChild);
		for (int i = 0; i < node->level; ++i) {
			cout << "   ";
		}
		cout << node->data.sharePrice << "   " << node->data.pathData << "   " << node->data.optionPrice<<endl;
		printTree(node->rightChild);
	}
}