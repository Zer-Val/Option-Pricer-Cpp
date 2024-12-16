#include "AsianPutOption.h"
#include <algorithm> 

//Implementation of the constructor of AsianPutOption, that use the constructor of AsianOption and initialize _strike as a double (K)
AsianPutOption::AsianPutOption(const std::vector<double>& timeSteps, double strike) : AsianOption(timeSteps), _strike(strike) {}

// Implémentation de la méthode payoff pour l'option Put
double AsianPutOption::payoff(double underlyingPrice) const
{
    return std::max(_strike - underlyingPrice, 0.0);
}
