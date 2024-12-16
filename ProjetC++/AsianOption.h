#pragma once
#include "Option.h"
#include <vector>

class AsianOption : public Option 
{
    public:
        // Constructor that initialize _timeSteps
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
