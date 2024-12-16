#include "EuropeanDigitalCallOption.h"

//Implementation of the constructor of EuropeanDigitalCallOption, that use the constructor of EuropeanDigitalOption
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {}

// Implementation of the payoff method for a digital Call option
double EuropeanDigitalCallOption::payoff(double z) const 
{
    return z >= getStrike() ? 1.0 : 0.0; 
}

// Implementation of the GetOptionType method for a Call option
EuropeanDigitalOption::optionType EuropeanDigitalCallOption::GetOptionType() const 
{
	return optionType::call;
}
