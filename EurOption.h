#pragma once
class EurOption
{
	public:
		EurOption(double T, double K) :m_T(T), m_K(K){};
		virtual double PriceByBinomial(double S0, double sigma, double r, int N) const;
		virtual double PriceByTrinomial(double S0, double sigma, double r, int N) const;
	private:
		virtual double payoff(double S) const = 0;
		const double m_T;
		const double m_K;
};

class EurCall :public EurOption
{
	public:
		EurCall(double T, double K) :EurOption(T, K) {};
	private:
		double payoff(double S) const
		{
			return S> m_K ? S - m_K : 0.0;
		}
};