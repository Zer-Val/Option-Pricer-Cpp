#include "PutOption.h"

//Implementation of the constructor of (EuropeanVanilla)PutOption, that use the constructor of EuropeanVanillaOption
PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

//Implementation of the Payoff method for an European Vanilla Put option
double PutOption::payoff(double z) const
{
	return (getStrike() >= z) ? (getStrike() - z) : 0.0; 	// ? is a ternary operator, which I use to write if-else conditions in a single line. 
								// Here, (z >= getStrike()) ? (z - getStrike()) : 0.0 <=> if (z >= getStrike()) { return z - getStrike(); } else { return 0.0; }
}

//Implementation of the GetOptionType method for an European Vanilla Put option
EuropeanVanillaOption::optionType PutOption::GetOptionType() const
{
	return optionType::put;
}
