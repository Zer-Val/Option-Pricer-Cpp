#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption 
{
	public:
		//Constructor of AsianPutOption, that use the constructor of AsianOption and initialize _strike as a double (K)
        	AsianPutOption(const std::vector<double>& timeSteps, double strike);

        	// Implementation of the payoff method for the Put option
        	double payoff(double underlyingPrice) const override;

    	private:
        	double _strike; //Private member to store the strike price of the option
};
