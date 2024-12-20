#include "CallOption.h"

//Implementation of the constructor of CallOption, that uses the constructor of EuropeanVanillaOption
CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

//Implementation of the payoff method for an European Vanilla Call option
double CallOption::payoff(double z) const
{
	return (z >= getStrike()) ? (z - getStrike()) : 0.0;	// ? is a ternary operator, which I use to write if-else conditions in a single line. 

}

//Implementation of the GetOptionType method for an European Vanilla Call option
EuropeanVanillaOption::optionType CallOption::GetOptionType() const
{
	return optionType::call;
}
