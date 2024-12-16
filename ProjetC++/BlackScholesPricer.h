#pragma once
#include <cmath>
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"

class BlackScholesPricer 
{
	public:

		//Constructor of BlackScholesPricer - for EuropeanVanillaOptions
		BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility);
		
		//Constructor of BlackScholesPricer - for EuropeanDigitalOptions
		BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility); 

		//Operator () to price the option
		double operator()() const; 

		//Method to compute the delta of the option
		double delta() const; 

	private:

		EuropeanVanillaOption* vanilla_option_; // Pointer to the vanilla option we want to price
		EuropeanDigitalOption* digital_option_; // Pointer to the digital option we want to price
		double _asset_price; // Underlying asset price (S)
		double _interest_rate; // Risk-free interest rate (r)
		double _volatility; // Volatility (vol)
};
