#include "AmericanCallOption.h"

//Implementation of the constructor of AmericanCallOption, that use the constructor of AmericanOption
AmericanCallOption::AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {}

//Payoff method for an American Call option
double AmericanCallOption::payoff(double z) const
{
	return (z >= getStrike()) ? (z - getStrike()) : 0.0;
}

//GetOptionType method for an American Call option
AmericanCallOption::optionType AmericanCallOption::GetOptionType() const
{
	return optionType::call;
}
