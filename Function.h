#pragma once
#include "Gilt.h"
#include "Date.h"
class Function
{
	public:
		virtual double eval(double x) const = 0;
};

class Adapter : public Function
{
	public:
		Adapter(const Gilt* gilt, const Date& settlementDate) : m_gilt(gilt), m_settlementDate(settlementDate) {}
		double eval(double x) const
		{
			return m_gilt->cleanPrice(m_settlementDate, x);
		}
	private:
		const Gilt* const m_gilt;
		const Date& m_settlementDate;

};