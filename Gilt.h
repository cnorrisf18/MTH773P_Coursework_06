#include "Date.h"
#pragma once

class Gilt
{
	public:
		Gilt(const Date& maturityDate, double coupon);
		double cleanPrice(const Date& settlementDate, double yield) const;
		double calculateYield(const Date& settlementDate, double clean_price) const;
	private:
		const Date m_maturityDate;
		const double m_coupon;
};