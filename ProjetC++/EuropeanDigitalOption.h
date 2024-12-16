#pragma once
#include <stdexcept>
#include "Option.h"
#include <iostream>

class BlackScholesPricer; // Forward declaration of the BlackScholesPricer class

class EuropeanDigitalOption : public Option
{
public:
	// Enum for the option type
	enum class optionType { call, put };

	//Constructor of EuropeanDigitalOption, that use the constructor of Option and initialize _strike as a double (K)
	EuropeanDigitalOption(double expiry, double strike);

	// Getter method for _strike  
	double getStrike() const;

	// Pure virtual method to get the option type
	virtual optionType GetOptionType() const = 0;

	// I declare BSP as a friend class of EVO to be able to access _strike in BSP
	friend class BlackScholesPricer;

	// Override of isAsianOption to return false for EVO - (Compilation issue if not)
	bool isAsianOption() const override;

private:

	double _strike; // Private member variable for the strike price
};
