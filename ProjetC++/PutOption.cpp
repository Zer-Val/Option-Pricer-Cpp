#include "PutOption.h"

//Implementation of the constructor of (EuropeanVanilla)PutOption, that use the constructor of EuropeanVanillaOption
PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

//Implementation of the Payoff method for an European Vanilla Put option
double PutOption::payoff(double z) const
{
	return (getStrike() >= z) ? (getStrike() - z) : 0.0; // ? est un opérateur ternaire, je m'en sers pour écrire des conditions if-else en une seule ligne ici (getStrike() >= z) ? (getStrike() - z) : 0.0 <=> if (getStrike() >= z) { return getStrike() - z; } else { return 0.0; }
}

//Implementation of the GetOptionType method for an European Vanilla Put option
EuropeanVanillaOption::optionType PutOption::GetOptionType() const
{
	return optionType::put;
}
