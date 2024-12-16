#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption
{
public:
    //Constructor of (EuropeanVanilla)CallOption, that use the constructor of EuropeanVanillaOption
    CallOption(double expiry, double strike);

    //Override of the payoff method for an European Vanilla Call option
    double payoff(double z) const override;

    //GetOptionType method for an European Vanilla Call option
    optionType GetOptionType() const override;
};
