#include "AsianOption.h"

//Implementation of the constructor of AsianOption, that use the constructor of Option and initialize _timeSteps as a vector (t_1, t_2, ... t_n)
AsianOption::AsianOption(const std::vector<double>& timeSteps) : Option(timeSteps.back()), _timeSteps(timeSteps) {}

// Getter method for _timeSteps
const std::vector<double>& AsianOption::getTimeSteps() const
{
    return _timeSteps;
}

// Override of the payoffPath method
double AsianOption::payoffPath(const std::vector<double>& prices) const 
{
    double sum = 0.0;
    for (double price : prices) 
    {
        sum += price;
    }
    double averagePrice = sum / prices.size();
    return payoff(averagePrice);
}

// Override of the isAsianOption method
bool AsianOption::isAsianOption() const 
{
    return true;
}
