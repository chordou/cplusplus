#ifndef BINOMIALPRICE_H
#define BINOMIALPRICE_H

#include "AsianOption.h"
#include "Tree.h"

typedef double (*PathFunc) (double, int, double); //pointer to function
typedef double (*PayOffFunc) (double, double, double, ExerciseType);

class BinomialPrice
{
public:
	AsianOption*	option;
	int				steps;
	Tree*			tree;

	
	BinomialPrice(AsianOption* pOpt, int nSteps, PathFunc pathFunc, PayOffFunc payF); //怎么用指针获取Asianoption的值，public

	void buildTree(TreeNode* node, int nFromLeafNode);
	void backwardEval(TreeNode*);
	void printTree(TreeNode* node);

private:
	double			dt;		// delta time
	double			u;		// up factor
	double			d;		// down factor = 1/u
	double			pu;		// up probability
	double			pd;		// down probability = 1 - pu
	double			discount;
	PathFunc		pathF;	// path dependent function
	PayOffFunc		payOffF;// payoff function
};

#endif