#include "AsianCallOption.h"
#include <algorithm>

//Implementation of the constructor of AsianCallOption, that use the constructor of AsianOption and initialize _strike as a double (K)
AsianCallOption::AsianCallOption(const std::vector<double>& timeSteps, double strikePrice) : AsianOption(timeSteps), _strike(strikePrice) {}

// Implementation of the payoff method for the Call option
double AsianCallOption::payoff(double underlyingPrice) const
{
    return std::max(underlyingPrice - _strike, 0.0);
}

//Implementation of the GetOptionType method for an Asian Call option
AsianOption::optionType AsianCallOption::GetOptionType() const
{
	return optionType::call;
}
