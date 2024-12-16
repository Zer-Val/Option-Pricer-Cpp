#pragma once
#include "Option.h"
#include <vector>

class AsianOption : public Option 
{
    public:

        //Enum for the option type
        enum class optionType { call, put };
        
        // Constructor that initialize _timeSteps
        AsianOption(const std::vector<double>& timeSteps);

        // Getter method for _timeSteps
        const std::vector<double>& getTimeSteps() const;

        // Pure virtual method to get the option type
        virtual optionType GetOptionType() const = 0;

        // Override of the payoffPath method
        double payoffPath(const std::vector<double>& prices) const override;

        // Override of the isAsianOption method
        bool isAsianOption() const override;

    private:
	    std::vector<double> _timeSteps; // Private member variable that stores the time steps
};
