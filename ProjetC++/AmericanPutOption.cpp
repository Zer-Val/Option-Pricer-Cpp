#include "AmericanPutOption.h"

//Implementation of constructor of AmericanPutOption, that use the constructor of AmericanOption
AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {}

//Implementation of the Payoff method for an European Vanilla Call option
double AmericanPutOption::payoff(double z) const
{
	return (getStrike() >= z) ? (getStrike() - z) : 0.0;
}

//Implementation of the GetOptionType method for a Call option
AmericanPutOption::optionType AmericanPutOption::GetOptionType() const
{
	return optionType::put;
}
