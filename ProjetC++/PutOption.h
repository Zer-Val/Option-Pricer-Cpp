#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption
{
public:
    //Constructor of (EuropeanVanilla)PutOption, that use the constructor of EuropeanVanillaOption
    PutOption(double expiry, double strike);

    //Payoff method for an European Vanilla Put option
    double payoff(double z) const override;

    //GetOptionType method for an European Vanilla Put option
    optionType GetOptionType() const override;
};
