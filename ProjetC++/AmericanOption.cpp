#include "AmericanOption.h"

//Implementation of constructor of AmericanOption, that use the constructor of Option and initialize _strike as a double (K)
AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {}

// Getter method for _strike
double AmericanOption::getStrike() const
{
	return _strike;
}

// Override of the isAmericanOption method to return true for American Options
bool AmericanOption::isAmericanOption() const
{
    return true;
}

// override of the isAsianOption method to return false for American Options
bool AmericanOption::isAsianOption() const
{
	return false;
}
