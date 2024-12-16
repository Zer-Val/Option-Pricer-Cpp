#include "EuropeanDigitalOption.h"

//Implementation of the constructor of EuropeanDigitalOption, that use the constructor of Option and initialize _strike as a double (K)
EuropeanDigitalOption::EuropeanDigitalOption(double K, double expiry) : Option(expiry), strike(K) 
{
    if (expiry < 0 || strike < 0) 
    {
        throw std::invalid_argument("Expiry and strike must be non-negative");
    }
}

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
