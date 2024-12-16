#include "EuropeanDigitalPutOption.h"

//Implementation of the constructor of EuropeanDigitalPutOption, that use the constructor of EuropeanDigitalOption
EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {}

// Implementation of the payoff method for a digitalPput option
double EuropeanDigitalPutOption::payoff(double z) const
{
	return z <= getStrike() ? 1.0 : 0.0;
}

// Implementation of the GetOptionType method for a Put
EuropeanDigitalOption::optionType EuropeanDigitalPutOption::GetOptionType() const
{
	return optionType::put;
}
