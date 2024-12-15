#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption
{
	public:
		//Constructor of AmericanCallOption, that use the constructor of AmericanOption
		AmericanCallOption(double expiry, double strike);

		//Payoff method for an American Call option
		double payoff(double z) const override;

		//GetOptionType method for a(n) (American) Call option
		optionType GetOptionType() const override;
};
