#include <iostream>
#include "Date.h"
#include "Gilt.h"

using namespace std;

int main()
{
	const Date maturity(7,9,2039);
	const double c = 4.25;
	const Gilt myGilt(maturity, c);
	const Date settlement(12,12,2013);
	const double y = 3.1432;
	const double clean = myGilt.cleanPrice(settlement, y);
	cout << clean << endl;
	cout << myGilt.calculateYield(settlement, 111.95) << endl;
	unsigned int mday, mmonth, myear, sday, smonth, syear;
	cout << "Testing Question 1." << endl;
	cout << "Please enter gilt contract values: " << endl << "\t";
	cout << "Maturity day: ";
	cin >> mday;
	cout << "\t" << "Maturity month: ";
	cin >> mmonth;
	cout << "\t" << "Maturity year: ";
	cin >> myear;
	double coupon;
	cout << "\t" << "Coupon (as a percentage): ";
	cin >> coupon; 
	if (mday <= 0 || mmonth <= 0 || myear < 0 || coupon < 0)
	{
		cout << "Invalid contract values (there was a negative or 0 input), please try again.";
		return 0;
	}
	cout << "Please enter market data: " << endl << "\t";
	cout << "Settlement day: ";
	cin >> sday;
	cout << "\t" << "Settlement month: ";
	cin >> smonth;
	cout << "\t" << "Settlement year: ";
	cin >> syear;
	double clean_price;
	cout << "\t" << "Clean price: ";
	cin >> clean_price;
	if (sday <= 0 || smonth <= 0 || syear <= 0 || clean_price <= 0)
	{
		cout << "Invalid market data (negative or 0 value), please try again.";
		return 0;
	}
	Date user_maturity(mday, mmonth, myear);
	Date user_settlement(sday, smonth, syear);
	const Gilt user_gilt(user_maturity, coupon);
	cout << "The calculated yield to maturity with given inputs is " << user_gilt.calculateYield(user_settlement, clean_price);


	return 0;
}