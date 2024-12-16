#pragma once
#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption
{
	public:
		//Constructor of AmericanPutOption, that use the constructor of AmericanOption
		AmericanPutOption(double expiry, double strike);

		//Payoff method for an Ameican Put option
		double payoff(double z) const override;

		//GetOptionType method for a Call option
		optionType GetOptionType() const override;		
};
