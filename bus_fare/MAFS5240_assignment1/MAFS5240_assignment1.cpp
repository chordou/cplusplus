// MAFS5240_assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main() {
	int		n1Dollar, n2Dollar, n5Dollar, n10Dollar, busFare;

	// Original number of coins in pocket
	cout << "Original number of coins in pocket:" << endl;
	cout << "Number of One-Dollar coins: "; cin >> n1Dollar;
	cout << "Number of Two-Dollar coins: "; cin >> n2Dollar;
	cout << "Number of Five-Dollar coins: "; cin >> n5Dollar;
	cout << "Number of Ten-Dollar coins: "; cin >> n10Dollar;
	cout << endl;

	// Bus Fare to tender.
	// Assume Bus Fare is a whole integer
	cout << "Bus Fare : "; cin >> busFare;
	cout << endl;

	int minn = 0;
	minn = n10Dollar + n5Dollar + n2Dollar + n1Dollar;
	int use10 = 0, use5 = 0, use2 = 0, use1 = 0, remain = 0;
	int n = 0, moneysum = 0;
	int min = 1000000;
	int result = 0;

	for (int n10 = 0; n10 <= n10Dollar; n10++) {
		for (int n5 = 0; n5 <= n5Dollar; n5++) {
			for (int n2 = 0; n2 <= n2Dollar; n2++) {
				for (int n1 = 0; n1 <= n1Dollar; n1++) {
					moneysum = n10 * 10 + n5 * 5 + n2 * 2 + n1 * 1;

					if (moneysum >= busFare) {
						n = n10 + n5 + n2 + n1;
						if (moneysum <= min) {
							min = moneysum;
							if (n < minn) {
								minn = n;
								remain = n10Dollar + n5Dollar + n2Dollar + n1Dollar - minn;
								use10 = n10;
								use5 = n5;
								use2 = n2;
								use1 = n1;
								result = 1;

							}
						}
					}
				}
			}
		}
	}



	switch (result) {
	case 1:
		cout << "Actual Bus Fare should be paid: " << min << endl;
		cout << "Coins remaining: " << remain << endl;
		cout << "Number of One-Dollar coins: " << n1Dollar - use1 << endl;
		cout << "Number of Two-Dollar coins: " << n2Dollar - use2 << endl;
		cout << "Number of Five-Dollar coins: " << n5Dollar - use5 << endl;
		cout << "Number of Ten-Dollar coins: " << n10Dollar - use10 << endl;
		break;

	case 0:
		cout << "not enough money, cannot board the bus" << endl;
		cout << "Coins remaining: " << n10Dollar + n5Dollar + n2Dollar + n1Dollar << endl;
		cout << "Number of One-Dollar coins: " << n1Dollar << endl;
		cout << "Number of Two-Dollar coins: " << n2Dollar << endl;
		cout << "Number of Five-Dollar coins: " << n5Dollar << endl;
		cout << "Number of Ten-Dollar coins: " << n10Dollar << endl;
		break;
	}
}

// Fill in the code to calculate the number of coins remaining.
// If not enough money, cannot board the bus, then coins remaining should be the same as before.
// Since you are supposed to tender the exact fare, if you do not have the exact change,
// you should tender the minimum above the bus fare.
// In any case, the number of coins remaining should be a maximum.

