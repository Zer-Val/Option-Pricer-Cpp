#include "EuropeanVanillaOption.h"

//Implementation of the constructor of EuropeanVanillaOptions, that use the constructor of Option and initialize _strike as a double (K)
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option(expiry), _strike(strike) {}

// Impklementation of the getter method for _strike
double EuropeanVanillaOption::getStrike() const 
{
    return _strike;
}
