#pragma once
#include <vector>

class Option 
{
	public:
		//Constructor of Option, that initialize _expiry (in years) as a double (T)
        	Option(double expiry);

	    	// Getter method for _expiry
        	double getExpiry() const;

	   	// Virtual method to calculate the payoff of the option
        	virtual double payoff(double underlyingPrice) const = 0;

	    	// Virtual method to calculate the payoff of the option with a path of prices (used for Asian Options)
        	virtual double payoffPath(const std::vector<double>& prices) const;

	    	// Virtual method to check if the option is an Asian Option
        	virtual bool isAsianOption() const;

	    	// Virtual method to check if the option is an American Option
        	virtual bool isAmericanOption() const;

    	private:

	    	double _expiry; //Private attribute that stores the expiry date of the option in years (T)
};
