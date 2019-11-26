#include "BinomialPrice.h"
#include "PayOff.h"
#include <iostream>

using namespace std;

int main()
{
	AsianOption opt(100.0, 100.0, 0.05, 0.30, 1, European, Call);
	// For an Asian (European Call) option, the payoff is the amount by which
	// the average stock price during the life time of the option exceeds the strike price.
	BinomialPrice p(&opt, 3, avgF, AsianPayOff);
	p.buildTree(0, p.steps);
	p.backwardEval(p.tree->root);
    cout << "European Call; 3-Step, avgF, AsianPayOff: " << p.tree->root->data.optionPrice << endl;
	cout << endl;
	p.printTree(p.tree->root);
	cout << endl;

	opt.c_p = Put;
	// For an Asian (European Put) option, the payoff is the amount by which
	// the strike price exceeds the average stock price during the life time of the option.
	p.buildTree(0, p.steps);
	p.backwardEval(p.tree->root);
	cout << "European Put; 3-Step, avgF, AsianPayOff: " << p.tree->root->data.optionPrice << endl;
	cout << endl;
	p.printTree(p.tree->root);
	cout << endl;

	opt.e_a = American;
	opt.c_p = Call;
	// For an Asian (American Call) option, if exercised at time t, the payoff is the amount by which
	// the average stock price between time 0 and t exceeds the strike price.
	p.buildTree(0, p.steps);
	p.backwardEval(p.tree->root);
	cout << "American Call; 3-Step, avgF, AsianPayOff: " << p.tree->root->data.optionPrice << endl;
	cout << endl;
	p.printTree(p.tree->root);
	cout << endl;

	//opt.c_p = Put;
	//// For an Asian (American Put) option, if exercised at time t, the payoff is the amount by which
	//// the strike price exceeds the average stock price between time 0 and t.
	//p.buildTree(0, p.steps);
	//p.backwardEval(p.tree->root);
	//cout << "American Put; 3-Step, avgF, AsianPayOff: " << p.tree->root->data.optionPrice << endl;
	//cout << endl;
	//p.printTree(p.tree->root);
	//cout << endl;

	//AsianOption optLB(50, 50, 0.1, 0.4, 0.25, American, Put);
	//// For an American lookback put option, if exercised at time t, the payoff is the amount by which
	//// the maximum stock price between time 0 and t exceeds the current stock price.
	//BinomialPrice pLB(&optLB, 3, maxF, LookbackPayOffPut);
	//pLB.buildTree(0, pLB.steps);
	//pLB.backwardEval(pLB.tree->root);
	//cout << "American Put; 3-Step, maxF, LookbackPayOffPut: " << pLB.tree->root->data.optionPrice << endl;
	//cout << endl;
	//pLB.printTree(pLB.tree->root);
	//cout << endl;
	return 0;
}