#include "BlackScholesPricer.h"
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

//Constructor of the BSP class for a European Vanilla Option
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility) : _vanilla_option(option), _digital_option(nullptr), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {} 

//Constructor of the BSP class for a European Digital Option
BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility) : _vanilla_option(nullptr), _digital_option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {} 

double BlackScholesPricer::operator()() const // Operator () to price the option
{
    double T, K, S = _asset_price, r = _interest_rate, sigma = _volatility, d1, d2, price;

    if (_vanilla_option) 
    {
		T = _vanilla_option->getExpiry(); // Option maturity
		K = _vanilla_option->getStrike(); // Strike price of the option

        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        d2 = d1 - sigma * std::sqrt(T);

        if (_vanilla_option->GetOptionType() == EuropeanVanillaOption::optionType::call) 
        {
            price = S * 0.5 * erfc(-d1 / sqrt(2)) - K * exp(-r * T) * 0.5 * erfc(-d2 / sqrt(2));
        }
        else 
        {
            price= -S * 0.5 * erfc(d1 / sqrt(2)) + K * exp(-r * T) * 0.5 * erfc(d2 / sqrt(2));
        }
    }
    else if (_digital_option) 
    {
        T = _digital_option->getExpiry(); // Option maturity
        K = _digital_option->getStrike(); // Strike price of the option

        d2 = (log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));

        if (_digital_option->GetOptionType() == EuropeanDigitalOption::optionType::call) 
        {
            price = exp(-r * T) * 0.5 * erfc(-d2 / sqrt(2));
        }
        else 
        {
            price = exp(-r * T) * 0.5 * erfc(d2 / sqrt(2));
        }
    }

	return price;
}

// Méthode pour retourner le Delta de l'option
double BlackScholesPricer::delta() const 
{
    double T, K, S = _asset_price, sigma = _volatility, r = _interest_rate, d1, delta;

    if (_vanilla_option) 
    {
        T = _vanilla_option->getExpiry();  // Maturity of the option
        K = _vanilla_option->getStrike(); // Strike price of the option
        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        if (_vanilla_option->GetOptionType() == EuropeanVanillaOption::optionType::call) 
        {
            delta =  0.5 * std::erfc(-d1 / std::sqrt(2));
        }
        else 
        {
            delta = 0.5 * std::erfc(-d1 / std::sqrt(2)) - 1;
        }
    }
    else if (_digital_option) 
    {
        T = _digital_option->getExpiry(); // Maturity of the option
        K = _digital_option->getStrike(); // Strike price of the option
        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        if (_digital_option->GetOptionType() == EuropeanDigitalOption::optionType::call) 
        {
            delta = exp(-r*T) / (S * sigma * sqrt(T) * std::sqrt(2 * M_PI));
        }
        else 
        {
            delta = - exp(-0.5 * d1 * d1) / (S * sigma * sqrt(T) * std::sqrt(2 * M_PI));
        }
    }
	return delta;
}
