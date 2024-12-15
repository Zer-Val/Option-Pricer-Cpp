#pragma once
#include "Option.h"
#include <vector>

class AsianOption : public Option 
{
    public:
        //Constructor of AsianOption, that use the constructor of Option and initialize _timeSteps as a vector (t_1, t_2, ... t_n)
        AsianOption(const std::vector<double>& timeSteps);

        // Getter method for _timeSteps
        const std::vector<double>& getTimeSteps() const;

        // Override of the payoffPath method
        double payoffPath(const std::vector<double>& prices) const override;

        // Override of the isAsianOption method
        bool isAsianOption() const override;

    private:
	    std::vector<double> _timeSteps; // Private member variable that stores the time steps
};
