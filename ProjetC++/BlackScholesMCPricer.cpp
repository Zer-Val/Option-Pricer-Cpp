#include "BlackScholesMCPricer.h"
#include <iostream>
#include <cmath> // Pour std::sqrt
#include <stdexcept> // Pour std::runtime_error

//Implementation of the constructor of BlackScholesMCPricer
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : _option(option), _underlying_price(initial_price), _risk_free_rate(interest_rate), _volatility(volatility), _nb_paths_generated(0), _current_estimate(0.0), estimates_mean(0.0), estimates_variance(0.0) {}

// Méthode pour obtenir le nombre de chemins générés
int BlackScholesMCPricer::getNbPaths() const
{
    return _nb_paths_generated;
}

// Implémentation de la méthode pour générer des chemins
void BlackScholesMCPricer::generate(int nb_paths)
{
    if (nb_paths <= 0)
    {
        throw std::invalid_argument("nb_paths as to be strictly positive.");
    }

	std::vector<double> spot_paths; // Vector to store the spot prices at each time step
	double spot_t; // Spot price at time t
	double z; // Random variable with standard normal distribution
	double payoffs = 0.0; // Total payoffs 
	double new_price_estimate = 0.0; // New price estimate after generating new paths
	int m = 1; // Number of time steps, we set it to 1 by default for European options
	std::vector<double> timesteps; // Vector to store the time steps 

    
    
    if (_option->isAsianOption())
    {
		m = static_cast<AsianOption*>(_option)->getTimeSteps().size(); // For Asian options, we get the number of time steps. 
        // We use static_cast to convert the Option pointer to an AsianOption pointer
    }

	double T = _option->getExpiry(); // Expiry time of the option
    double deltaT = T / m; 


	if (_option->isAsianOption())
	{
		timesteps = static_cast<AsianOption*>(_option)->getTimeSteps(); // For Asian options, we get the time steps from the option object
	}
	else
	{
		// timesteps for European options
        for (int k = 1; k <= m; k++)
        {
            timesteps.push_back(k * deltaT);
        }
	}


    for (int i = 0; i < nb_paths; i++)
    {
		//std::cout << "Path number : " << i << std::endl;
        for (int k = 1; k <= m; k++)
        {
			//std::cout << "Time step : " << k << std::endl;
            z = MT::rand_norm(); // Variable aléatoire normale standard
            
            if (k == 1)
			{
				spot_paths.push_back(_underlying_price* exp((_risk_free_rate - 0.5 * _volatility * _volatility) * (timesteps[k-1]) + _volatility * std::sqrt(timesteps[k-1]) * z));
                continue;
			}
            
            else 
            { 
                spot_t = spot_paths.back() * exp((_risk_free_rate - 0.5 * _volatility * _volatility) * (deltaT) + _volatility * std::sqrt(deltaT) * z);
                //std::cout << " Spot price =" << spot_t << " exp :" << exp((_risk_free_rate - 0.5 * _volatility * _volatility) * (deltaT)+_volatility * std::sqrt(deltaT) * z) << std::endl;
				//std::cout << deltaT << std::endl;
                spot_paths.push_back(spot_t);
            }

			//std::cout << "k = " << k << " Z =" << z << " Spot_paths size :" << spot_paths.size() << std::endl;

        }

        double payoff = _option->payoffPath(spot_paths); // Calcul du payoff
        payoffs += payoff;
        estimates_mean += payoff;
        estimates_variance += payoff * payoff;

        spot_paths.clear();
    }

        // Mise à jour de l'estimation du prix
        new_price_estimate = exp(-_risk_free_rate * T) * (payoffs / nb_paths);
        _current_estimate = (_current_estimate * _nb_paths_generated + new_price_estimate * nb_paths) / (_nb_paths_generated + nb_paths);
        _nb_paths_generated += nb_paths;

    
}

// Opérateur () pour retourner l'estimation actuelle
double BlackScholesMCPricer::operator()() const
{
    if (_nb_paths_generated == 0)
    {
        throw std::runtime_error("Estimation non définie : aucun chemin généré.");
    }
    return _current_estimate;
}

// Méthode pour calculer l'intervalle de confiance à 95 %
std::vector<double> BlackScholesMCPricer::confidenceInterval() const
{
    if (_nb_paths_generated == 0)
    {
        throw std::runtime_error("Intervalle de confiance non défini : aucun chemin généré.");
    }

    double mean_payoff = estimates_mean / _nb_paths_generated;
    double variance = (estimates_variance / _nb_paths_generated - mean_payoff * mean_payoff) / _nb_paths_generated;
    double std_error = std::sqrt(variance);
    double margin_of_error = 1.96 * std_error;
    return { _current_estimate - margin_of_error, _current_estimate + margin_of_error };
}
