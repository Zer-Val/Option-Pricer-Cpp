#include "PutOption.h"

// Implementation of the constructor for PutOption, uses the one from EuropeanVanillaOption
PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

//Implementation of the Payoff method for an European Vanilla Put option
double PutOption::payoff(double z) const
{
	return (getStrike() >= z) ? (getStrike() - z) : 0.0; // ? is a ternary operator, I use it to write if-else conditions in a single line 

//Implementation of the GetOptionType method for an European Vanilla Put option
EuropeanVanillaOption::optionType PutOption::GetOptionType() const
{
	return optionType::put;
}
