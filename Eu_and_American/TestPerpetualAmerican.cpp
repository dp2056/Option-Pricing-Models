/*
 * This program calculates and displays the prices of Perpetual American Call and Put options.
 * It also analyzes how changes in asset price and strike price affect option pricing.
 */

#include "Vector.h"

// Function to generate a mesh array from start to end with step h
std::vector<double> mesh(double start, double end, double h)
{
	std::vector<double> result;
	for (; start < end; start += h)
	{
		result.push_back(start);
	}
	return result;
}

// Function to print out the elements of a vector
void Print(std::vector<double> V)
{
	for (int i = 0; i < V.size(); i++)
	{
		std::cout << i + 1 << ". " << V.at(i) << " \n";

	}
	std::cout << "\n\n";
}

// Main program
int main()
{
	// Initialize option parameters.
	const double K1 = 100, sig1 = 0.1, r1 = 0.1, b1 = 0.02, S1 = 110;
	PerpetualAmerican Data;
	Data.K = K1;
	Data.sig = sig1;
	Data.r = r1;
	Data.b = b1;
	Data.optType = "C"; // Initialize Call option

	// Calculate and display Perpetual American Call and Put option prices.
	std::cout << "Perpetual American Call Option price is: ";
	std::cout << Data.Price(S1) << std::endl;
	// Switch to Put option
	Data.optType = "P";
	std::cout << "Perpetual American Put Option price is: ";
	std::cout << Data.Price(S1) << std::endl;

	// Calculate option price for a range of asset prices.
	Data.optType = "C"; // Revert to Call option for the following calculations
	std::cout << "\n\nCall option price for monotonically increasing asset price is : \n";
	std::vector<double> asstpr = mesh(S1, 130, 5);
	OptionCalculator callpvc;
	Print(callpvc.AmericanOption(Data, S1, asstpr, 'S'));
	
	// Calculate option price for a range of strike prices.
	std::cout << "\nCall Option price for monotonically increasing strike price is : \n";
	std::vector<double> strike = mesh(K1, 110, 2);
	OptionCalculator callstrvc;
	Print(callstrvc.AmericanOption(Data, S1, strike, 'K'));

	return 0;
}
