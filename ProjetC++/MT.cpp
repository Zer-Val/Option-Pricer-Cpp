#include "MT.h"

// Implementation of the method to get the unique instance of the class
MT& MT::getInstance()
{
	static MT instance; // Create a unique instance of the class
	return instance; // return this unique instance
}

// Implementation of the method to generate a random number between 0 and 1
double MT::rand_unif()
{
	std::uniform_real_distribution<double> dist(0.0, 1.0); // Create a random number generator for a uniform distribution between 0 and 1
	return dist(getInstance().mt); // Return a random number following a uniform distribution
}

// Implementation of the method to generate a random number following a normal distribution
double MT::rand_norm()
{
	std::normal_distribution<double> dist(0.0, 1.0); // Create a random number generator for a normal distribution with mean 0 and std 1
	return dist(getInstance().mt); // Return a random number following a normal distribution
}

// Implementation of the private constructor to prevent instanciation
MT::MT() : mt(std::random_device{}()) {}
