#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Binomial/CRR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Binomial_UnitTest
{		
	TEST_CLASS(Binomial)
	{

	public:
		AMER_EURO A_E;
		CALL_PUT C_P;
		double spotPrice, strikePrice, maturity, vol, rate, crr;
		int nStep, err;

		TEST_METHOD(EC1)
		{
			A_E = European; C_P = Call;	spotPrice = 100.0; strikePrice = 100.0; maturity = 1; vol = 0.2; rate = 0.05; nStep = 10;
			Assert::AreEqual(SUCCESS, CRRBinomialTree(C_P, A_E, spotPrice, strikePrice, maturity, vol, rate, nStep, &crr));
			Assert::AreEqual(10.2534, crr, 0.0001);
		}

		TEST_METHOD(EC2)
		{
			A_E = European; C_P = Call;	spotPrice = 100.0; strikePrice = 100.0; maturity = 1; vol = 0.2; rate = 0.05; nStep = 1000;
			Assert::AreEqual(SUCCESS, CRRBinomialTree(C_P, A_E, spotPrice, strikePrice, maturity, vol, rate, nStep, &crr));
			Assert::AreEqual(10.4486, crr, 0.0001);
		}

		TEST_METHOD(EC3)
		{
			A_E = European; C_P = Call;	spotPrice = 100.0; strikePrice = 100.0; maturity = 1; vol = 0.4; rate = 0.05; nStep = 1000;
			Assert::AreEqual(SUCCESS, CRRBinomialTree(C_P, A_E, spotPrice, strikePrice, maturity, vol, rate, nStep, &crr));
			Assert::AreEqual(18.0191, crr, 0.0001);
		}

		TEST_METHOD(EP)
		{
			A_E = European; C_P = Put;	spotPrice = 100.0; strikePrice = 100.0; maturity = 1; vol = 0.2; rate = 0.05; nStep = 1000;
			Assert::AreEqual(SUCCESS, CRRBinomialTree(C_P, A_E, spotPrice, strikePrice, maturity, vol, rate, nStep, &crr));
			Assert::AreEqual(5.57153, crr, 0.00001);
		}

		TEST_METHOD(AP)
		{
			A_E = American; C_P = Put;	spotPrice = 100.0; strikePrice = 100.0; maturity = 1; vol = 0.2; rate = 0.05; nStep = 1000;
			Assert::AreEqual(SUCCESS, CRRBinomialTree(C_P, A_E, spotPrice, strikePrice, maturity, vol, rate, nStep, &crr));
			Assert::AreEqual(6.0896, crr, 0.0001);
		}
	};
}