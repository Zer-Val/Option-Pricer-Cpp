#include "EuropeanDigitalOption.h"

//Implementation of the constructor of EuropeanDigitalOption, that use the constructor of Option and initialize _strike as a double (K)
EuropeanDigitalOption::EuropeanDigitalOption(double K, double expiry) : Option(expiry), _strike(K) {}

// Getter method for _strikedouble EuropeanDigitalOption::getStrike() const
double EuropeanDigitalOption::getStrike() const 
{
    return _strike;
}

// Override of isAsianOption to return false for EVDO - (Compilation issue if not)
bool EuropeanDigitalOption::isAsianOption() const 
{
	return false;
}
