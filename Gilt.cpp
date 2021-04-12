#include "Gilt.h"
#include "Function.h"
#include <iostream>
using namespace std;



double BisectionSolver(const Function* f, double c, double left, double right, double acc)
{
	double fl = f->eval(left);
	double fr = f->eval(right);

	while (true)
	{
		const double mid = (left + right) / 2.0;
		if (right - left <= acc)
			return mid;
		const double fm = f->eval(mid);
		if (fl <= c && c <= fm || fm <= c && c <= fl)
		{
			right = mid;
			fr = fm;
		}
		else
		{
			left = mid;
			fl = fm;
		}
	}

	return 0.0;
}
Gilt::Gilt(const Date& maturityDate, double coupon):m_maturityDate(maturityDate), m_coupon(coupon){} //use the member initialization list
//to initialize const variables


double Gilt::cleanPrice(const Date& settlementDate, double yield) const
{
	bool done1 = false;
	bool done2 = false;
	Date prevCoupon = settlementDate;
	Date nextCoupon = settlementDate;
	unsigned int md, mm, my, ad, am, ay, sd, sm, sy;
	m_maturityDate.getDMY(md, mm, my);
	Date semiannualDate = m_maturityDate;
	semiannualDate.addMonths(-6);
	semiannualDate.getDMY(ad, am, ay);
	int r = 0;
	int m = 0;
	while (not done1) //loop backwards until the days and months match the coupon date (i.e. the day/month of the maturity or semiannual)
	{
		prevCoupon.addDays(-1);
		r += 1;
		prevCoupon.getDMY(sd, sm, sy);
		if ((sd == md && sm == mm) || (sd == ad && sm == am))
		{
			done1 = true;
		}
	}
	while (not done2) //loop forwards until the days and months match the coupon date
	{
		nextCoupon.addDays(1);
		m += 1;
		nextCoupon.getDMY(sd, sm, sy);
		if ((sd == md && sm == mm) || (sd == ad && sm == am))
		{
			done2 = true;
		}
	}
	const int s = nextCoupon - prevCoupon;
	const int n = ((m_maturityDate - nextCoupon) / 365) * 2;//find out how many years between the dates, then multiply by 2 to get coupon periods
	const double A = ((double)r / s) * ((m_coupon) / 2.0);
	const double f = 2.0;
	double sum = 0;
	const double adj_yield = yield / 100.0;
	for (int i = 0; i <= n; i++)
	{
		sum += ((m_coupon) / f) / pow((1.0 + (adj_yield / f)), i);
	}
	sum += 100.0 / pow((1.0 + (adj_yield / f)), n);
	//cout << (sum / pow((1 + (adj_yield / 2)), ((double)m / s))) - A << endl;
	return (sum / pow(1 + (adj_yield / 2), ((double)m / s))) - A;

}

double Gilt::calculateYield(const Date& settlementDate, double clean_price) const
{
	const Adapter adapter(this, settlementDate);
	return BisectionSolver(&adapter, clean_price, -100,100, 1e-12);
}
