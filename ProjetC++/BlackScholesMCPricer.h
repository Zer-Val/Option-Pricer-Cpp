#pragma once
#include "Option.h"
#include "AsianOption.h"
#include "MT.h"
#include <vector>
#include <cmath>
#include <stdexcept>

class BlackScholesMCPricer 
{
	public:
		// Constructor of the BlackScholesMCPricer class
        	BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

		// Method to get the number of paths generated sicne the beginning of the program
		int getNbPaths() const;

		// Method to generate paths
        	void generate(int nb_paths);

		// Operator () to price the option
        	double operator()() const;

		// Method to compute the 95% confidence interval of theprice
        	std::vector<double> confidenceInterval() const;

   	 private:

        	Option* _option; 
		double _underlying_price; // Underlying asset price (S0)
		double _risk_free_rate; // Risk-free interest rate (r)
		double _volatility; // Volatility (sigma)
        	int _nb_paths_generated; // Number of paths already generated since the beginning of the program (Nb)
		double _current_estimate; // Current estimate of the option price
		double estimates_mean; //
        	double estimates_variance; //
        	std::vector<double> estimated_prices; // Store estimated option prices
};
