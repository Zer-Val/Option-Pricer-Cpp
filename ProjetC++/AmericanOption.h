#pragma once
#include "Option.h"

class AmericanOption : public Option
{
	public:
		//Enum for the option type
		enum class optionType { call, put };

		//Constructor of AmericanOption, that use the constructor of Option and initialize _strike as a double (K)
		AmericanOption(double expiry, double strike); 
	
		// Getter method for _strike
		double getStrike() const;

		// Pure virtual method to get the option type
		virtual optionType GetOptionType() const = 0;

		// Override of the isAmericanOption method to return true for American Options
		bool isAmericanOption() const override;

		// override of the isAsianOption method to return false for American Options
		bool isAsianOption() const override;

	private:
		double _strike; //Private member variable for the strike price
};

