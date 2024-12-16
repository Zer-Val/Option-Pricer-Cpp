#include "CRRPricer.h"
#include <stdexcept> // For invalid_argument exception handling
#include <iostream>

//Implementation of the constructor of CRRPricer that takes up (U), down (D) and interest rate (R)
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _computed(false) 
{
	if (_option -> isAsianOption()) 
	{
		throw std::invalid_argument("Asian options not supported.");
	}
    	check_arbitrage(); // Verify no arbitrage conditions
   	_q = (_interest_rate - _down) / (_up - _down); // Calculate risk-neutral probability
    	_price_tree.setDepth(_depth); // Initialize price tree
    	_value_tree.setDepth(_depth); // Initialize value tree
    	_exercise_tree.setDepth(_depth); // Initialize exercise tree
    	_price_tree.setNode(0, 0, _asset_price); // Set initial asset price
}

//Implementation of the constructor of CRRPricer that initialize up (U), down (D) and interest rate (R)
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) : _option(option), _depth(depth), _asset_price(asset_price), _computed(false) 
{
	if (_option -> isAsianOption()) 
	{
		throw std::invalid_argument("Asian options not supported.");
	}
	_up = std::exp((r + (volatility*volatility)/2)*(_option->getExpiry()/_depth)+volatility * std::sqrt(volatility)) - 1; // Calculate up factor
	_down = std::exp((r + (volatility * volatility) / 2) * (_option->getExpiry() / _depth) - volatility * std::sqrt(volatility)) - 1; // Calculate down factor
	_interest_rate = std::exp(r*(_option->getExpiry() / _depth)) - 1; // Calculate interest rate
	
	check_arbitrage(); // Verify no arbitrage conditions
	_q = (_interest_rate - _down) / (_up - _down); // Calculate risk-neutral probability
	_price_tree.setDepth(_depth); // Initialize price tree
	_value_tree.setDepth(_depth); // Initialize value tree
	_exercise_tree.setDepth(_depth); // Initialize exercise tree
	_price_tree.setNode(0, 0, _asset_price); // Set initial asset price
}

// Calculate option price using either closed-form or tree-based method
double CRRPricer::operator()(bool closed_form)
{
    if (closed_form) 
    {
        return closed_form_formula(); // Use closed-form formula
    }
    else 
    {
        if (!_computed)
        {
            compute(); // Compute tree values if not already done
        }
        return _value_tree.getNode(0, 0); // Return price at root of value tree
    }
}

// Check for arbitrage conditions in model parameters
void CRRPricer::check_arbitrage() 
{
	if (_down >= _interest_rate || _up <= _interest_rate) 
    	{
		throw std::invalid_argument("Arbitrage opportunity detected."); // Throw exception if arbitrage is possible (D < R < U in theory)
    	}
}

// Compute the price and value trees
void CRRPricer::compute() 
{
	if (_computed) return; // If already computed, don't recompute
    
    	// Build the price tree
    	for (int n = 1; n <= _depth; ++n)
    	{
        	for (int i = 0; i <= n; ++i)
        	{
            		double price;
            		if (i != n) // If the node is not the last one of the row, we take the down factor (down to left, up to right)
            		{
                		price = _price_tree.getNode(n - 1, i) * (1 + _down);
            		}
			else // If the node is the last one of the row, we take the up factor (up to right)
            		{
                		price = _price_tree.getNode(n - 1, i - 1) * (1 + _up); 
            		}
			_price_tree.setNode(n, i, price); // We add the price to the tree
        	}
    	}
    
	if (_option->isAmericanOption()) // for the american options
    	{
		// We want to populate the value tree at maturity
        	for (int i = 0; i <= _depth; ++i) 
        	{
            		_value_tree.setNode(_depth, i, _option->payoff(_price_tree.getNode(_depth, i))); 
			_exercise_tree.setNode(_depth, i, true); // Alway True at maturity, as for European options
        	}

		// Backpropagatin of the values to earlier nodes
		for (int n = _depth - 1; n >= 0; --n) // We start from the last row and go up
        	{
            		for (int i = 0; i <= n; ++i) 
            		{
				double continuation_value = (_q * _value_tree.getNode(n + 1, i + 1) + (1 - _q) * _value_tree.getNode(n + 1, i)) / (1 + _interest_rate); // Cf. formula in the subject, p11
				double intrinsic_value = _option->payoff(_price_tree.getNode(n, i)); // Cf. formula in the subject, p11
				
				// We chose the maximum between the intrinsic value and the continuation value
                		if (intrinsic_value >= continuation_value) 
                		{
                			_value_tree.setNode(n, i, intrinsic_value);
					_exercise_tree.setNode(n, i, true); // If the intrinsic value is greater than the continuation value, we can/should exercise the option
                		}
                		else 
                		{
                    			_value_tree.setNode(n, i, continuation_value);
                    			_exercise_tree.setNode(n, i, false);
                		}
            		}
        	}
    	}
    	else // for the european options
    	{ 
        	// Populate the value tree at maturity
        	for (int i = 0; i <= _depth; ++i)
        	{
            		_value_tree.setNode(_depth, i, _option->payoff(_price_tree.getNode(_depth, i)));
        	}

	        // Backpropagate values to earlier nodes
	        for (int n = _depth - 1; n >= 0; --n)
	        {
	            	for (int i = 0; i <= n; ++i)
	            	{ 
				double continuation_value = (_q * _value_tree.getNode(n + 1, i + 1) + (1 - _q) * _value_tree.getNode(n + 1, i)) / (1 + _interest_rate); // Cf. formula in the subject, p5
				_value_tree.setNode(n, i, continuation_value); // We add the continuation value to the value tree, to get the value of node (0,0)
	            	}
	        }
    	}
	_computed = true; // We change the flag to true, to indicate that the computation is done
}

// Get the value of a specific node in the value tree
double CRRPricer::get(int n, int i) const 
{
    return _value_tree.getNode(n, i);
}


// Compute binomial coefficient (n choose k)
double CRRPricer::binomialCoefficient(int n, int k) const
{
	if (k > n) //Property of bin. coefficients
    	{	 
        	return 0;
    	}
    	if (k == 0 || k == n) //Property of bin. coefficients
    	{
        	return 1;
    	}
    	int result = 1;
	for (int i = 1; i <= k; ++i)  //Formula to calculate binomial coefficients
    	{
        	result *= (n - (k - i));
        	result /= i;
    	}
    	return result;
}

// Calculate option price using closed-form formula
double CRRPricer::closed_form_formula() const // Cf. formula in the subject, p7
{
	double result = 0.0;
    	for (int i = 0; i <= _depth; ++i) 
	{
		int binomialCoeff = binomialCoefficient(_depth, i); // Binomial coefficient (n choose i)
        	double probability = binomialCoeff * std::pow(_q, i) * std::pow(1 - _q, _depth - i); // Probability of ending at node i
        	result += probability * _option->payoff(_price_tree.getNode(_depth, i)); // Weighted payoff
    	}
    	return result / std::pow(1 + _interest_rate, _depth); // Discount to present value
}

bool CRRPricer::getExercice(int n, int i)const // Get the exercise decision at a specific node, for american options
{
	return _exercise_tree.getNode(n, i);
}


