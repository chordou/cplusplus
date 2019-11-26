#include "CRR.h"
#include <iostream>
#include <math.h>

using namespace std;

int CRRBinomialTree(
	CALL_PUT	callOrPut,				/* (I) put or call flag (use Call or Put) */
	AMER_EURO	amerOrEuro,				/* (I) option type (use European, American) */
	double		spotPrice,				/* (I) spot price of underlying */
	double		strike,					/* (I) strike price of option */
	double		maturity,				/* (I) maturity of option in years */
	double		vol,					/* (I) annual volatility of underlying */
	double		rate,					/* (I) annual continuous compounded discount rate */
	int			nStep,					/* (I) number of steps in tree */
	double		*value)					/* (O) option value */
/*-----------------------------------------------------------------------------
** FUNCTION:	CRRBinomialTree.
**
** DESCRIPTION:	Calculates the price of an option using the Cox, Ross and Rubinstein
**				binomial tree model.
**
** RETURNS:		SUCCESS and the premium, otherwise FAILURE.                                  
**
**---------------------------------------------------------------------------*/
{

	if (nStep <= 0)
	{
		cout << "CRRBinomialTree: Negative number of steps." << endl;
		return FAILURE;
	}            
	
	if (spotPrice <= 0.0 || strike <= 0.0 || maturity < 0.0 || vol < 0.0 || rate < 0.0)
	{
		cout << "CRRBinomialTree: Invalid input detected." << endl;
		return FAILURE;
	}

	// TO-BE-COMPLETED
	double deltaT, discount, u, d, p;
	deltaT = maturity / nStep;
	discount = exp(-rate * deltaT);
	u = exp(vol * sqrt(deltaT));
	d = 1 / u;
	p = (exp(rate * deltaT) - d) / (u - d);

	double* FPn = new double[nStep + 1];
	double* payoff = new double[nStep + 1];


	for (int i = 0; i < nStep; ++i) {
		FPn[i] = 0;
		payoff[i] = 0;
	}

	if (nStep > 0) {
		for (int i = 0; i < nStep + 1; ++i) {
			FPn[i] = spotPrice * pow(u, nStep - i) * pow(d, i);
		}

		for (int i = 0; i < nStep + 1; ++i) {
			if (callOrPut == Call) {
				payoff[i] = FPn[i] - 100;
			}
			else {
				payoff[i] = -(FPn[i] - 100);
			}

			if (payoff[i] <= 0) {
				payoff[i] = 0;
			}
		}

		/*	for (int i = 0; i < nStep + 1; ++i) { cout << FPn[i] << endl; }
			for (int i = 0; i < nStep + 1; ++i) { cout << payoff[i] << endl; }*/

		for (int j = 0; j < nStep; ++j) {
			for (int i = 0; i < nStep; ++i) {
				payoff[i] = (payoff[i] * p + payoff[i + 1] * (1 - p)) * discount;
				if (amerOrEuro == American && callOrPut == Put) {
					double earlyExercise = 0, fp = 0;
					fp = 100 * pow(u, nStep - 1 - j - i) * pow(d, i);
					earlyExercise = strike - fp; //
					payoff[i] = MAX(earlyExercise, payoff[i]);
					
				}
			}
		}

		*value = payoff[0];
		//cout << *value << endl;
	}
	delete[] FPn;
	delete[] payoff;
	
	return SUCCESS;
}



