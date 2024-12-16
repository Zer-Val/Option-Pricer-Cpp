#pragma once
#include <random>

class MT 
{
	public:
		// Method to get the unique instance of the class
		static MT& getInstance();

		// Method to generate a random number between 0 and 1
		static double rand_unif();

		// Method to generate a random number following a normal distribution
		static double rand_norm();

	private:
		// Private constructor to prevent instanciation
		MT();

		// Deleted copy constructor and assignment operator to prevent copies
		MT(const MT&) = delete;
		MT& operator=(const MT&) = delete;

		std::mt19937 mt; // Pseudo-random number generator
};
